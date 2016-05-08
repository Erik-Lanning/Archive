#include "Globals.h"
#include "Utils.h"



//"Function TrDevice_ConstantFire.WeaponConstantFiring.BeginState"
//"Function TrDevice_ConstantFire.WeaponConstantFiring.RefireCheckTimer"
bool Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);

//"Function TribesGame.TrPlayerController.PlayerTick"
bool Function_TribesGame_TrPlayerController_PlayerTick_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);

struct DelayedProjectile {
	ATrDevice *device;
	float delaytime;
	FVector direction;

	//UClass *projclass;

	UClass* SpawnClass;
	AActor* SpawnOwner; 
	FName SpawnTag;
	FVector SpawnLocation;
	FRotator SpawnRotation;

};

extern DelayedProjectile MyDelayedProjectiles[50];
extern int MagicBullets_mode; //0 none, 1 - only new, 2 - both