#include "Globals.h"
#include "Utils.h"
bool Function_TribesGame_TrPlayerController_PlayerTick_JetPack(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);


#define PHYS_Walking       1
#define PHYS_Falling       2
#define PHYS_Flying        4
#define PHYS_Projectile    6
#define PHYS_None          0

#define GravityAcc -75
#define AirControlAcc 30
#define DirectionalJetAcc 50
#define UpwardsAcc (50+(-(GravityAcc))) //To counter gravity and add 50


#define MaxDragSpeed 300
#define DragDeAcceleration -50


#define EnergyRegenRate 20
#define DirectionalEnergyCostRate 60
#define UpwardEnergyCostRate      60
#define DirectionalAndUpwardsExtraCostRate     0

#define UUToSanics 13.88
