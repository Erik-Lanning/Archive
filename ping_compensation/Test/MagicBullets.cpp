#include "MagicBullets.h"



int MagicBullets_mode = 0;

DelayedProjectile MyDelayedProjectiles[50] = { 0 };


//"Function TrDevice_ConstantFire.WeaponConstantFiring.BeginState"
//"Function TrDevice_ConstantFire.WeaponConstantFiring.RefireCheckTimer"
bool Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	if (MagicBullets_mode == 0) return false;

	//spawn a projectile and get extact ping
	ATrDevice *mydevice = (ATrDevice *) dwCallingObject;
	if (mydevice) {
		if (mydevice->ShouldRefire()) {
			if (mydevice->MaxAmmoCount > 10) {
				FVector a; a.X = 0; a.Y = 0; a.Z = 0;
				FVector StartLoc = mydevice->GetClientSideProjectileFireStartLoc(a);
				FRotator adjusted = mydevice->GetAdjustedAim(StartLoc);
				APawn *myinstigator = mydevice->Instigator;
				//ATrProjectile *myproj = (ATrProjectile *) mydevice->Spawn(mydevice->WeaponProjectiles.Data[0], myinstigator, mydevice->Name, StartLoc, adjusted, 0, 0);
				//ATrProjectile *myproj = (ATrProjectile *) mydevice->Spawn(ATrProj_Spinfusor::StaticClass(), myinstigator, mydevice->Name, StartLoc, adjusted, 0, 0);
				
				float pingtime = myinstigator->PlayerReplicationInfo->ExactPing;
				if (pingtime <= 0.0) pingtime = (float) 0.001; //for training mode
				//UClass *projclass = mydevice->WeaponProjectiles.Data[0];
				FVector Mydir = RotationToVector(adjusted);
				if (pingtime) {
					for (int i = 0; i < 50; i++) { //find a open spot
						//fprintf(mylog, "\nMyDelayedProjectiles[%d].delaytime(%f) <= 0.0 ? %s\n", i, MyDelayedProjectiles[i].delaytime, MyDelayedProjectiles[i].delaytime <= 0.0 ? "Yes" : "No"); fflush(mylog);
						if (MyDelayedProjectiles[i].delaytime <= 0.0) {
							fprintf(mylog, "\nDelayed a proj(%d) by %f\n", i, pingtime); fflush(mylog);
							MyDelayedProjectiles[i].delaytime = pingtime;
							MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); //mydevice->WeaponProjectiles.Data[0];
							MyDelayedProjectiles[i].direction = Mydir;
							MyDelayedProjectiles[i].SpawnLocation = StartLoc;
							MyDelayedProjectiles[i].SpawnOwner = myinstigator;
							MyDelayedProjectiles[i].SpawnRotation = adjusted;
							MyDelayedProjectiles[i].SpawnTag = mydevice->Name;

							MyDelayedProjectiles[i].device = mydevice;
							
							return false;
							/*
							//MyDelayedProjectiles[i].proj = myproj;
							//MyDelayedProjectiles[i].projclass = projclass;
							//MyDelayedProjectiles[i].projclass = ATrProj_NJ4SMG::StaticClass();
							if (ID == HOOK_Function_TrDevice_ConstantFire_WeaponConstantFiring_Check) {
								if (mode == 2) return false;
								else {
									mydevice->PlayFireAnimation(0);
									CauseMuzzleFlash();
									ShakeView();
									PayAccuracyForShot();
									UpdateShotsFired();
									return true;
								}
							}
							else return false;
							*/
						}
					}
				}
			}
		}
	}
	return false;
}

//"Function TribesGame.TrPlayerController.PlayerTick"
bool Function_TribesGame_TrPlayerController_PlayerTick_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	if (MagicBullets_mode == 0) return false;

	static int t = 0;
	ATrPlayerController_eventPlayerTick_Parms Tick_Params;
	memcpy(&Tick_Params, pParams, sizeof(ATrPlayerController_eventPlayerTick_Parms));
	int f = 0;

	for (int i = 0; i < 50; i++) {
		if (MyDelayedProjectiles[i].delaytime > 0.0) {
			if (!f) {
				f = 1;
				fprintf(mylog, "Tick(%f)", Tick_Params.DeltaTime); 
				if (++t == 20) { t = 0; fprintf(mylog, "\n"); fflush(mylog); }
			}
			
			MyDelayedProjectiles[i].delaytime -= Tick_Params.DeltaTime;
			if (MyDelayedProjectiles[i].delaytime <= 0.0) {
					MyDelayedProjectiles[i].delaytime = 0;


					ATrDevice *mydevice = (ATrDevice *) MyDelayedProjectiles[i].device;
					ATrProjectile *myproj = (ATrProjectile *) mydevice->Spawn(MyDelayedProjectiles[i].SpawnClass, MyDelayedProjectiles[i].SpawnOwner, MyDelayedProjectiles[i].SpawnTag, MyDelayedProjectiles[i].SpawnLocation, MyDelayedProjectiles[i].SpawnRotation, 0, 0);
					if (myproj) {
						//MyDelayedProjectiles[i].proj->InitProjectile(MyDelayedProjectiles[i].direction, MyDelayedProjectiles[i].projclass);
						myproj->m_bTether = 0;
						myproj->InitProjectile(MyDelayedProjectiles[i].direction, 0);
						fprintf(mylog, "\nProjectile(%d) initilizied\n", i); fflush(mylog);
					}

			}
		}
	}
	return false;
}
