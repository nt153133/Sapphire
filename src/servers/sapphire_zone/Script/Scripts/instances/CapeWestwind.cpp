#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class CapeWestwind : public InstanceContentScript
{
public:
   CapeWestwind() : InstanceContentScript( 20007 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000604, 4262798, 4, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};