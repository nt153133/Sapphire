#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <algorithm>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
  ThreadPool(unsigned int maxJobs = 0)
  {
    if(maxJobs == 0)
    {
      // Auto-scale to available CPU threads
      maxJobs = std::max(1, (int)std::thread::hardware_concurrency() - 1);
    }

    // Populate thread pool and watch for jobs to execute
    {
      std::unique_lock<std::mutex> lock(m_poolMutex);
      m_threadPool.reserve(maxJobs);
      for(unsigned int i = 0; i < maxJobs; i++)
      {
        m_threadPool.emplace_back([this] { this->runPendingJob(); });
      }
    }
  }

  ~ThreadPool()
  {
    // Make sure jobs are cancelled during destruction
    if(!m_stopped)
    {
      cancel();
    }
  }

  // Adds a job to the queue
  void enqueue(std::function<void(void)> func)
  {
    std::unique_lock<std::mutex> lock(m_poolMutex);
    m_pendingJobs.push(func);

    m_jobStatus.notify_one();
  }

  // Blocks until all jobs are processed
  void runToCompletion()
  {
    std::unique_lock<std::mutex> lock(m_poolMutex);
    m_doneStatus.wait(lock, [this](){ return m_pendingJobs.empty() && !m_activeJobs; });
  }

  // Cancels pending and current jobs
  void cancel()
  {
    // Remove pending jobs
    std::unique_lock<std::mutex> lock(m_poolMutex);
    m_pendingJobs = {};

    // Cancel currently running jobs
    m_cancelling = true;
    m_jobStatus.notify_all();
    lock.unlock();

    for(auto &t : m_threadPool)
    {
      t.join();  // Finish remaining threads
    }

    m_threadPool.clear();

    m_stopped = true;
  }

private:
  bool m_cancelling = false;
  bool m_stopped = false;

  std::queue<std::function<void(void)>> m_pendingJobs;

  std::mutex m_poolMutex;
  std::vector<std::thread> m_threadPool;
  std::condition_variable m_jobStatus;
  std::condition_variable m_doneStatus;
  unsigned int m_activeJobs = 0;

  // Function run per thread to find and execute jobs
  void runPendingJob()
  {
    while(!m_cancelling)
    {
      std::unique_lock<std::mutex> lock(m_poolMutex);

      // Wait for notification unless no more jobs or canceled
      m_jobStatus.wait(lock, [this]{ return m_cancelling || !m_pendingJobs.empty(); });

      // Retrieve pending job
      if(!m_cancelling && !m_pendingJobs.empty())
      {
        auto job = m_pendingJobs.front();
        m_pendingJobs.pop();

        if(job)
        {
          m_activeJobs++;
          lock.unlock();

          job(); // Execute job on this thread, in parallel with others

          lock.lock();
          m_activeJobs--;

          m_doneStatus.notify_one();
        }
      }
    }
  }
};

#endif
