#ifndef EXPORTMGR_H
#define EXPORTMGR_H

#include "exporter.h"
#include "navmesh_exporter.h"
#include "obj_exporter.h"
#include "threadpool.h"

class ExportMgr
{
public:
  ExportMgr(unsigned int maxThreads = 0)  : m_threadpool(maxThreads)
  {
  }

  ~ExportMgr()
  {
    cancel();
  }

  void exportZone(const ExportedZone& zone, ExportFileType exportFileTypes)
  {
    m_threadpool.enqueue([zone, exportFileTypes]()
    {
      if( exportFileTypes & ExportFileType::WavefrontObj )
        ObjExporter::exportZone( zone );

      if( exportFileTypes & ExportFileType::Navmesh )
        NavmeshExporter::exportZone( zone );
    });
  }

  void runToCompletion()
  {
    m_threadpool.runToCompletion();
  }

  void cancel()
  {
    m_threadpool.cancel();
  }

private:
  ThreadPool m_threadpool;
};

#endif
