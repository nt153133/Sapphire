#ifndef _ZONE_H
#define _ZONE_H

#include <unordered_map>
#include <common/Common.h>

#include "Cell.h"
#include "CellHandler.h"
#include "Actor/EventObject.h"

#include "Forwards.h"

#include <set>
#include <boost/enable_shared_from_this.hpp>

#include <stdio.h>
#include <string.h>
#include <common/Exd/ExdDataGenerated.h>
namespace Core {

class Session;

class ZonePosition;

using SessionSet = std::set< SessionPtr >;

class Zone : public CellHandler< Cell >, public boost::enable_shared_from_this< Zone >
{
protected:
   uint32_t	m_territoryId;
   uint32_t	m_guId;

   std::string m_placeName;
   std::string m_internalName;

   std::unordered_map< int32_t, Entity::PlayerPtr > m_playerMap;
   std::unordered_map< int32_t, Entity::EventObjectPtr > m_eventObjects;

   SessionSet m_sessionSet;

   Common::Weather m_currentWeather;
   Common::Weather m_weatherOverride;

   uint64_t m_lastMobUpdate;

   uint16_t m_currentFestivalId;
   boost::shared_ptr< Data::TerritoryType > m_territoryTypeInfo;

   std::map< uint8_t, int32_t> m_weatherRateMap;

public:
   Zone();

   Zone( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName );
   virtual ~Zone();

   bool init();

   /*! overrides the zone's weather, set to 0 to unlock */
   void setWeatherOverride( Common::Weather weather );

   Common::Weather getCurrentWeather() const;

   uint16_t getCurrentFestival() const;
   void setCurrentFestival( uint16_t festivalId );

   virtual void loadCellCache();
   virtual uint32_t getTerritoryId() const;
   virtual void onEnterTerritory( Entity::Player& player );
   virtual void onFinishLoading( Entity::Player& player );
   virtual void onInitDirector( Entity::Player& player );
   virtual void onLeaveTerritory( Entity::Player& player );
   virtual void onUpdate( uint32_t currTime );

   Common::Weather getNextWeather();

   void pushActor( Entity::CharaPtr pActor );

   void removeActor( Entity::CharaPtr pActor );

   void updateActorPosition( Entity::Actor &pActor );

   bool isCellActive( uint32_t x, uint32_t y );

   void updateCellActivity( uint32_t x, uint32_t y, int32_t radius );

   void updateInRangeSet( Entity::CharaPtr pActor, Cell* pCell );

   void queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, Network::Packets::GamePacketPtr pPacketEntry );

   uint32_t getGuId() const;

   const std::string& getName() const;
   const std::string& getInternalName() const;

   std::size_t getPopCount() const;
   void loadWeatherRates();
   bool checkWeather();
   //void updateBnpcs( int64_t tickCount );

   bool update( uint32_t currTime );

   void updateSessions( bool changedWeather );

   void registerEObj( Entity::EventObjectPtr object );
   Entity::EventObjectPtr getEObj( uint32_t objId );
   void updateEObj( Entity::EventObjectPtr object );

   InstanceContentPtr getAsInstanceContent();

};

}

#endif
