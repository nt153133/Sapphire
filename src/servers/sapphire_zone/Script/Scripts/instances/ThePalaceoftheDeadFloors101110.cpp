#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors101110 : public InstanceContentScript
{
public:
   ThePalaceoftheDeadFloors101110() : InstanceContentScript( 60011 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000608, 6527847, 4, { -300.000000f, 0.000026f, -237.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000608, 6544382, 4, { 301.149902f, -0.045413f, 285.247589f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};