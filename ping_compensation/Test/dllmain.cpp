#include "dllmain.h"

HMODULE myhInst;
FILE *mylog = 0;
ATrPlayerController *pPC = NULL;


BOOL APIENTRY DllMain (HMODULE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
		    myhInst = hInst;
			DisableThreadLibraryCalls ( hInst );
			CreateThread ( NULL, 0, ( LPTHREAD_START_ROUTINE ) onAttach, NULL, 0, NULL );
        break;

      case DLL_PROCESS_DETACH:
			  onDLL_PROCESS_DETACH();
        break;

      case DLL_THREAD_ATTACH:
        break;

	  case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}

bool Function_TribesGame_TrGameViewportClient_PostRender(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
		static int noswap = 0;
		APlayerController *pPC = Eng->GamePlayers.Data[0]->Actor;
		if (pPC) {
            if(pPC->Pawn && pPC->Pawn->Health > 0)
            {
				if(pPC->Pawn->PlayerReplicationInfo) {
					
					//Projectile Optimizing test
					/*ATrDevice *pTrDevice = reinterpret_cast< ATrDevice * >( pPC->Pawn->Weapon );
					if(pPC->Pawn->IsFiring() && pTrDevice->DBWeaponId == 7438 || pTrDevice->DBWeaponId == 8256 || pTrDevice->DBWeaponId == 7418 || pTrDevice->DBWeaponId == 8404 ) {
						for ( int i = GOBJECTS_MAX; i < UObject::GObjObjects()->Count; ++i )
						{
							if ( UObject::GObjObjects()->Data[i] )
							{
								if ( UObject::GObjObjects()->Data[i]->IsA( ATrProj_Tracer::StaticClass() ) ) 
								{
									ATrProj_Tracer* Proj = (ATrProj_Tracer*)UObject::GObjObjects()->Data[i];
									if(Proj && !Proj->bPendingDelete) {
										pPC->Pawn->PlayerReplicationInfo->UpdatePing(pPC->CurrentTimeStamp);
										float exacttping = pPC->Pawn->PlayerReplicationInfo->ExactPing;
										Proj->m_TracerPSC->Template->Delay = exacttping;
										//Proj->Speed *= 10;
										//Proj->Damage = 100;
									}
								}
							}
						}
					}*/
					//Fixing Rate of Fire
					if(!pPC->Pawn->bPathfindsAsVehicle) {
						if(pPC->Pawn->Weapon) {
							if(pPC->Pawn->Weapon->FireInterval(0)) { //Add weapon ID checks here.
								ATrDevice *pTrDevice = reinterpret_cast< ATrDevice * >( pPC->Pawn->Weapon );
								if(pTrDevice) {
									if(pPC->Pawn->Weapon->EquipTime == 0.01) {
										noswap = 1;
									} else {
										noswap = 0;
									}
									if(!pTrDevice->HasAmmo(0,0)) {
										ATrPlayerController *pTrPawn = reinterpret_cast< ATrPlayerController * >( pPC );
										pTrPawn->ReloadWeapon();
									}
									if(pPC->Pawn->Weapon->EquipTime != 0.01 && !noswap) {
										pPC->Pawn->PlayerReplicationInfo->UpdatePing(pPC->CurrentTimeStamp);
										float exacttping = pPC->Pawn->PlayerReplicationInfo->ExactPing;
										//pPC->Pawn->Weapon->EquipTime = 0.85 - (exacttping);
									}
									switch(pTrDevice->DBWeaponId) {
										case 7388: pPC->Pawn->Weapon->FireInterval(0) = 0.14; break; //Eagle Pistol
										case 7394: //swag blaster should be 0.4
											pPC->Pawn->Weapon->FireInterval(0) = 0.4; 
											break;
										case 8256:	//throwing knives should be 0.43
											pPC->Pawn->Weapon->FireInterval(0) = 0.001; 
											break;
										case 8403:	//swag blaster mx should be 0.3
											pPC->Pawn->Weapon->FireInterval(0) = 0.3; 
											break;
										default: break;
									}
								}
							}
						}
					}
					
				}
			}
		}

	return false;
}

/*
void hookUObject(UObject* obj, int objectindex)
{
    //fprintf(mylog, "Hooking object: %s\n", obj->GetFullName()); fflush(mylog);

    hooks[objectindex] = new toolkit::VMTHook(obj); // hook the object
    pProcessEvent = hooks[objectindex]->GetMethod<tProcessEvent>(65);
    hooks[objectindex]->HookMethod(&ProxyFunction, 65); //replace the original function with the hooked function

    //fprintf(mylog, "ProcEvent: %x, New: %x\n", pProcessEvent, &ProxyFunction); fflush(mylog);
}

void unhookUObjects() {
	for (int c = 0; c < (sizeof(hookedobjects) / sizeof(char *)) && hookedobjects[c]; c++) {
		hooks[c]->UnhookMethod(65);
	}
	
}

*/

/*
void hookUObject2(UObject* obj)
{
	//fprintf(mylog, "Hooking object: %s to [%x]\n", obj->GetFullName(), &ProxyFunction); fflush(mylog);

	DWORD *VMT = (DWORD *) *((DWORD *) obj);
	DWORD dwOld;
	if ( VirtualProtect( VMT + 65, sizeof(void*), PAGE_EXECUTE_READWRITE, &dwOld ) )
	{
		//fprintf(mylog, "Hooking.., old = [%x]\n", VMT[65]); fflush(mylog);
		VMT[65] = (DWORD) (DWORD *) &ProxyFunction;
		//fprintf(mylog, "Hooking.., new = [%x]\n", VMT[65]); fflush(mylog);
		VirtualProtect( VMT + 65, sizeof(void*), dwOld, &dwOld );
		//fprintf(mylog, "Hooking.., done.\n"); fflush(mylog);
	}

    //fprintf(mylog, "ProcEvent New: %x\n",  &ProxyFunction); fflush(mylog);
}
*/


//OnAttach.cpp
#include "Globals.h"


bool closefile = false;

// ProcessEvent Sig
#define ProcessEvent_Pattern	"\x74\x00\x83\xC0\x07\x83\xE0\xF8\xE8\x00\x00\x00\x00\x8B\xC4"
#define ProcessEvent_Mask		"x?xxxxxxx????xx"

// UE3 Tables Sigs
//A1 ?? ?? ?? ?? 8B ?? ?? 8B ?? ?? 25 00 02 00 00
#define GObjects_Pattern		"\xA1\x00\x00\x00\x00\x8B\x00\x00\x8B\x00\x00\x25\x00\x02\x00\x00"
#define GObjects_Mask			"x????x??x??xxxxx"
#define GObjects_Offset			0x1


#define GNames_Pattern			"\x8b\x0d\x00\x00\x00\x00\x83\x3c\x81\x00\x74"
#define GNames_Mask				"xx????xxxxx"
#define GNames_Offset			0x2

void onAttach() { 
	mylog = fopen("C:\\_Main_Log.txt", "w+" );


	MODULEINFO miGame = TFLHACKT00LS::GetModuleInfo ( NULL );
	
	// get GObjects
	//GObjects = *(unsigned long*) ( TFLHACKT00LS::FindPattern( (unsigned long) miGame.lpBaseOfDll, miGame.SizeOfImage, (unsigned char*) GObjects_Pattern, (char*) GObjects_Mask ) + GObjects_Offset );
	
	// log
	//fprintf ( mylog, "GObjects: 0x%X\n", GObjects );

	// get GNames
	//GNames = *(unsigned long*) ( TFLHACKT00LS::FindPattern( (unsigned long) miGame.lpBaseOfDll, miGame.SizeOfImage, (unsigned char*) GNames_Pattern, (char*) GNames_Mask ) + GNames_Offset );
	
	// log
	//fprintf ( mylog, "GNames:   0x%X\n", GNames );

	UObject *Object = UObject::GObjObjects()->Data[ 1 ];
	unsigned long *cObject = (unsigned long *) Object;
	unsigned long *ProcessEventsAddress = (unsigned long *) (*(cObject) + 65*sizeof(unsigned long));

	//fprintf ( mylog, "ProcessEventsAddress:   0x%X @ 0x%X @ 0x%X\n", Object, ProcessEventsAddress, *ProcessEventsAddress);


	hooks_init();
	{
		SetupHook(a, &Function_TribesGame_TrGameViewportClient_PostRender, "Function TribesGame.TrGameViewportClient.PostRender", 0);
		SetupHook(HOOK_Function_TribesGame_TrPlayerController_PlayerTick_Global, &Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets, "Function TribesGame.TrPlayerController.StartFire", 0);
		SetupHook(HOOK_Function_TribesGame_TrGameViewportClient_PostRender, &Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets, "Function TribesGame.TrPlayerController.PlayerTick", 0);
		SetupHook(HOOK_Function_TribesGame_TrPlayerController_PlayerTick_JetPack, &Function_TribesGame_TrPlayerController_PlayerTick_MagicBullets, "Function TribesGame.TrPlayerController.PlayerTick", 0);
		SetupHook(b, &COLTTIME, "Function TribesGame.TrPlayerController.StartFire", 0);
		SetupHook(c, &COLTTIME, "Function TribesGame.TrPlayerController.PlayerTick", 0);
	}
	hook_startprocessevents(*ProcessEventsAddress);

}


void onDLL_PROCESS_DETACH() {
			 if (mylog){
				//fprintf(mylog, "DLL_PROCESS_DETACH\n"); 
				fclose(mylog); mylog = 0;
			 }
}


//Magic Chain
int MagicBullets_mode = 1;
 
DelayedProjectile MyDelayedProjectiles[50] = { 0 };
 
 
//"Function TrDevice_ConstantFire.WeaponConstantFiring.BeginState"
//"Function TrDevice_ConstantFire.WeaponConstantFiring.RefireCheckTimer"
bool Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	static DWORD ROFtimer = GetTickCount();
	static char LARcounter = 0;
	//if(ROFtimer + 105 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); }
	//MessageBoxA(0,"Under 800HP","Under 800HP", 0);
    if (MagicBullets_mode == 0) return false;
 
    //spawn a projectile and get extact ping
	APlayerController *pPC = Eng->GamePlayers.Data[0]->Actor;
	if(pPC) {
		if(pPC->Pawn && pPC->Pawn->Health > 0)
		{
			if(pPC->Pawn->PlayerReplicationInfo) {
				if(!pPC->Pawn->bPathfindsAsVehicle) {
					if(pPC->Pawn->Weapon) {
						ATrDevice *mydevice = reinterpret_cast< ATrDevice * >( pPC->Pawn->Weapon );
						if (mydevice) {
							//f_out << mydevice->DBWeaponId << "\n";
							switch(mydevice->DBWeaponId) {
								case 7458:	if(ROFtimer + 110 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //X1
								case 7385: case 8406:	if(ROFtimer + 110 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Gast=8406 Assault=7385
								case 7438:
								if(LARcounter < 2) {
									if(ROFtimer + 72 > GetTickCount()) 
										{ return false; } 
											else 
												{ ROFtimer = GetTickCount(); ++LARcounter;} break; //LAR
								} else {
									if(ROFtimer + 218 > GetTickCount()) //Delay between 3bullet burst
										{ return false; } 
											else 
												{ ROFtimer = GetTickCount(); LARcounter=0;} break;
								}
								break;
								case 7419:	if(ROFtimer + 100 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break;  //SEN falcon
								//case 7394:	if(ROFtimer + 105 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //novablaster
								//case 8403:	if(ROFtimer + 105 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //novablaster mx
								//case 7418:	if(ROFtimer + 180 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Artic SN7=8404 and SN7=7418
								//case 8404:	if(ROFtimer + 180 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Artic SN7=8404 and SN7=7418
								//case 8256:	if(ROFtimer + 430 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //knives
								case 7397:	if(ROFtimer + 100 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Rhino
								case 8409:	if(ROFtimer + 110 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Artic Rhino
								case 7441:	if(ROFtimer + 110 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //NJ4=7441 Desert NJ4= 8408
								case 8408:	if(ROFtimer + 100 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //NJ4=7441 Desert NJ4= 8408
								case 8249:	if(ROFtimer + 200 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //NJ5
								case 7443:	if(ROFtimer + 100 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //TCN4
								case 8410:	if(ROFtimer + 150 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //Rockwind
								case 7386:	if(ROFtimer + 110 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //DMB chaingun
								case 8392:	if(ROFtimer + 140 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); } break; //dmb chaincannon
								default:
								LARcounter=0;
								ROFtimer = GetTickCount();
								return false; //Not a weapon supported by Magic Chain
							}
							//MessageBoxA(0,"Under 800HP","Under 800HP", 0);
							//add a switch here to check device ID
							mydevice->WeaponFireTypes(0) = 0;
							if( pPC->Pawn->IsFiring() ) {
							//if (mydevice->ShouldRefire()) {
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
									if (pingtime && pPC->Pawn->Health > 0) {
										for (int i = 0; i < 50; i++) { //find a open spot
											////fprintf(mylog, "nMyDelayedProjectiles[%d].delaytime(%f) <= 0.0 ? %sn", i, MyDelayedProjectiles[i].delaytime, MyDelayedProjectiles[i].delaytime <= 0.0 ? "Yes" : "No"); fflush(mylog);
											if (MyDelayedProjectiles[i].delaytime <= 0.0) {
												////fprintf(mylog, "nDelayed a proj(%d) by %fn", i, pingtime); fflush(mylog);
												MyDelayedProjectiles[i].delaytime = pingtime;

												//Add a switch here to spawn right type of bullet based on weapon ID
												switch(mydevice->DBWeaponId) {
													case 7458:	MyDelayedProjectiles[i].SpawnClass = ATrProj_X1Rifle::StaticClass(); break; //X1 
													case 7385: case 8406:	MyDelayedProjectiles[i].SpawnClass = ATrProj_AssaultRifle::StaticClass(); break; //Gast=8406 Assault=7385
													case 7438:		MyDelayedProjectiles[i].SpawnClass = ATrProj_LightAssaultRifle::StaticClass(); break; //LAR changed to assault rifle for misty.
													case 7419:	MyDelayedProjectiles[i].SpawnClass = ATrProj_Falcon::StaticClass(); break;  //SEN falcon
													//case 7394:	MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); break; //novablaster
													//case 8403:	MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); break; //novablaster mx
													//case 7418:	MyDelayedProjectiles[i].SpawnClass = ATrProj_SN7::StaticClass(); break; //Artic SN7=8404 and SN7=7418 
													//case 8404:	MyDelayedProjectiles[i].SpawnClass = ATrProj_SN7::StaticClass(); break; //Artic SN7=8404 and SN7=7418
													//case 8256:	MyDelayedProjectiles[i].SpawnClass = ATrProj_ThrowingKnives::StaticClass(); break; //knives
													case 7397:	MyDelayedProjectiles[i].SpawnClass = ATrProj_RhinoSMG::StaticClass(); break; //Rhino
													case 8409:	MyDelayedProjectiles[i].SpawnClass = ATrProj_RhinoSMG::StaticClass(); break; //Artic Rhino
													case 7441:	MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); break; //NJ4=7441 Desert NJ4= 8408
													case 8408:	MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); break; //NJ4=7441 Desert NJ4= 8408
													case 8249:	MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ5SMG::StaticClass(); break; //NJ5
													case 7443:	MyDelayedProjectiles[i].SpawnClass = ATrProj_TCN4SMG::StaticClass(); break; //TCN4
													case 8410:	MyDelayedProjectiles[i].SpawnClass = ATrProj_TCN4SMG::StaticClass(); break; //Rockwind
													case 7386:	MyDelayedProjectiles[i].SpawnClass = ATrProj_Chaingun::StaticClass(); break; //DMB chaingun
													case 8392:	MyDelayedProjectiles[i].SpawnClass = ATrProj_Chaingun::StaticClass(); break; //dmb chaincannon
													default:
													break;
												}
												//MyDelayedProjectiles[i].SpawnClass = ATrProj_NJ4SMG::StaticClass(); //mydevice->WeaponProjectiles.Data[0];
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
							//}
						}
					}
				}
			}
		} 
	} else {LARcounter=0; ROFtimer = GetTickCount();}
					return false;
}
//"Function TribesGame.TrPlayerController.PlayerTick"
bool Function_TribesGame_TrPlayerController_PlayerTick_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
    if (MagicBullets_mode == 0) return false;
	APlayerController *pPC = Eng->GamePlayers.Data[0]->Actor;
	if(pPC) {
		if(pPC->Pawn && pPC->Pawn->Health > 0)
		{
			if(pPC->Pawn->PlayerReplicationInfo) {
				if(!pPC->Pawn->bPathfindsAsVehicle) {
					if(pPC->Pawn->Weapon) { 
						static int t = 0;
						ATrPlayerController_eventPlayerTick_Parms Tick_Params;
						memcpy(&Tick_Params, pParams, sizeof(ATrPlayerController_eventPlayerTick_Parms));
						int f = 0;
 
						for (int i = 0; i < 50; i++) {
							if (MyDelayedProjectiles[i].delaytime > 0.0) {
								if (!f) {
									f = 1;
								   // //fprintf(mylog, "Tick(%f)", Tick_Params.DeltaTime);
									if (++t == 20) { t = 0; 
									//fprintf(mylog, "n"); fflush(mylog); 
									}
								}
            
								MyDelayedProjectiles[i].delaytime -= Tick_Params.DeltaTime;
								if (MyDelayedProjectiles[i].delaytime <= 0.0) {
										MyDelayedProjectiles[i].delaytime = 0;
 
 
										//ATrDevice *mydevice = (ATrDevice *) MyDelayedProjectiles[i].device;
										ATrDevice *mydevice = reinterpret_cast< ATrDevice * >( pPC->Pawn->Weapon );
										ATrPlayerController *pTrPawn = reinterpret_cast< ATrPlayerController * >( pPC );
										if(mydevice) {
											ATrProjectile *myproj = (ATrProjectile *) mydevice->Spawn(MyDelayedProjectiles[i].SpawnClass, MyDelayedProjectiles[i].SpawnOwner, MyDelayedProjectiles[i].SpawnTag, MyDelayedProjectiles[i].SpawnLocation, MyDelayedProjectiles[i].SpawnRotation, 0, 0);
											ATrPlayerController *pTrPC = reinterpret_cast< ATrPlayerController * >( pPC );
											if (myproj && pPC->Pawn->Health > 0 && mydevice) {
												//MyDelayedProjectiles[i].proj->InitProjectile(MyDelayedProjectiles[i].direction, MyDelayedProjectiles[i].projclass);
												myproj->m_bTether = 0;
												myproj->InitProjectile(MyDelayedProjectiles[i].direction, 0);
											   // //fprintf(mylog, "nProjectile(%d) initiliziedn", i); fflush(mylog);
											}
										}
 
								}
							}
						}
						return false;
					}
				}
			}
		}
	}
	return false;
}
bool COLTTIME(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	static DWORD ROFtimer = GetTickCount();
	//if(ROFtimer + 105 > GetTickCount()) { return false; } else { ROFtimer = GetTickCount(); }
	//MessageBoxA(0,"Under 800HP","Under 800HP", 0);
    //spawn a projectile and get extact ping
	APlayerController *pPC = Eng->GamePlayers.Data[0]->Actor;
	if(pPC) {
			if(pPC->Pawn && pPC->Pawn->Health > 0)
			{
				if(pPC->Pawn->PlayerReplicationInfo) {
					/*if(canusecolt == 0) {
						if(wcscmp(pPC->Pawn->PlayerReplicationInfo->PlayerName.Data, L"[BANG] lcedWinds") == 0) 
							{canusecolt = 1;}
					} else {
						canusecolt == 0;
					}
					if(canusecolt==0) return false;
					*/
					if(!pPC->Pawn->bPathfindsAsVehicle) {
						if(pPC->Pawn->Weapon) {
							ATrDevice *mydevice = reinterpret_cast< ATrDevice * >( pPC->Pawn->Weapon );
							if(mydevice->DBWeaponId != 7431) {
								ROFtimer = GetTickCount();
								return false;
							 } else {
								 mydevice->ForceEndFire( );
								 mydevice->ServerStopFire(0);
								 mydevice->StopFire(0);
								 pPC->Pawn->Weapon->WeaponFireTypes(0) = 3;
							 }
							ATrDevice_NovaSlug *pTrrDevice = reinterpret_cast< ATrDevice_NovaSlug * >( pPC->Pawn->Weapon );
							ATrPlayerController *pTrPawn = reinterpret_cast< ATrPlayerController * >( pPC );
							if(pTrrDevice->r_bIsReloading || pTrrDevice->IsReloading() && !pTrrDevice->m_bPendingReload)	{
								return false;
							}
							if(!pTrrDevice->HasAmmo(0,0)) {
								pTrPawn->ReloadWeapon();
								return false;
							}
							pTrrDevice->ToggleActivate();
							if( ((GetKeyState(VK_LBUTTON) & 0x80) != 0) && !pTrrDevice->r_bIsReloading && !pTrrDevice->IsReloading() && !pTrrDevice->m_bPendingReload) {
							if (mydevice) {
								//f_out << mydevice->DBWeaponId << "\n";
								//FName *newbind;
								//newbind->Index = 'a';
								switch(mydevice->DBWeaponId) {
									case 7431:
											//Must change bind
											//pPC->PlayerInput->SetBind(L"GBA_Fire", newkeybind);
											if(ROFtimer + 240 > GetTickCount()) { return false; } 
												else {
													ROFtimer = GetTickCount();
												} break; //Nova Colt
									default:
									ROFtimer = GetTickCount();
									return false; //Not a weapon supported by Magic Chain
								}
									if( !pTrrDevice->IsReloading() && pTrrDevice->HasAmmo(0,0) && !pTrrDevice->r_bIsReloading && !pTrrDevice->GetZoomedState()) {
										if(pTrrDevice->r_bReadyToFire) {
											pPC->Pawn->Weapon->WeaponFireTypes(0) = 0;
											pTrrDevice->ForceEndFire();
											pTrrDevice->StopFire(0);
											pTrrDevice->StartFire(0);
											pTrrDevice->ToggleActivate();
											pTrrDevice->ForceEndFire();
											pTrrDevice->StopFire(0);
											pPC->Pawn->Weapon->WeaponFireTypes(0) = 3;
											//ROFtimer += 70;
											return false;
										} else {
											pPC->Pawn->Weapon->WeaponFireTypes(0) = 0;
											pTrrDevice->ForceEndFire();
											pTrrDevice->StopFire(0);
											pTrrDevice->FireAmmunition();
											pTrrDevice->ToggleActivate();
											pTrrDevice->ForceEndFire();
											pTrrDevice->StopFire(0);
											pPC->Pawn->Weapon->WeaponFireTypes(0) = 3;
											return false;
										}
									}
							}
						}
					}
				}
			} 
		}
	} else {ROFtimer = GetTickCount();}
					return false;
}