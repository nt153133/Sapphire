#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheStrikingTreeHard : public InstanceContentScript
{
public:
   TheStrikingTreeHard() : InstanceContentScript( 20022 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 4712008, 5, { 5.026201f, 74.994751f, 16.039301f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 75.000000f, -7.671923f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};