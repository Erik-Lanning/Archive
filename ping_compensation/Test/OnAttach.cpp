#include "Globals.h"


int radarscale = 0;
bool closefile = false;
bool KeyBoard_A = false, KeyBoard_S = false, KeyBoard_D = false, KeyBoard_W =  false;
bool KeyBoard_SPACE = false, KeyBoard_RBUTTON =  false;

void ObjectDump(UObject *Object) {
	if (false) { return; }

	//* //Havoc patch (play with havoc)
	else if (Object->IsA(UTrFamilyInfo_Light::StaticClass()) || Object->IsA(UTrFamilyInfo_Heavy::StaticClass())) {

		TArray< class UClass* > myVehicleSelectionList;
		myVehicleSelectionList.Add(ATrVehicle_Havoc::StaticClass());
		myVehicleSelectionList.Add(ATrVehicle_HERC::StaticClass());
		myVehicleSelectionList.Add(ATrVehicle_GravCycle::StaticClass());
		myVehicleSelectionList.Add(ATrVehicle_Beowulf::StaticClass());
		myVehicleSelectionList.Add(ATrVehicle_Shrike::StaticClass());
		fprintf( mylog, "patching familyinfo for vehicles: %s...\n", Object->GetFullName()); fflush(mylog);
		UTrFamilyInfo *a = (UTrFamilyInfo *) Object;
		a->VehicleSelectionList = myVehicleSelectionList;
		a->PassengerSelectionList = myVehicleSelectionList;
		fprintf( mylog, "Done.\n"); fflush(mylog);
	}
	else if (!strcmp(Object->GetFullName(), "TrServerSettingsInfo TheWorld.PersistentLevel.TrServerSettingsInfo")) {
		ATrServerSettingsInfo *myservsettings = (ATrServerSettingsInfo *) Object;
		fprintf(mylog, "patching server vehicle settings  on %s\n", Object->GetFullName()); fflush(mylog);
		if (myservsettings) {
			myservsettings->VehicleLimits[0] = 100; myservsettings->VehicleLimits[1] = 100; myservsettings->VehicleLimits[2] = 100; myservsettings->VehicleLimits[3] = 100; myservsettings->VehicleLimits[4] = 100;
			myservsettings->VehiclePrices[0] = 10; myservsettings->VehiclePrices[1] = 10; myservsettings->VehiclePrices[2] = 10; myservsettings->VehiclePrices[3] = 10; myservsettings->VehiclePrices[4] = 10;
			myservsettings->CallinPrices[0] = 10; myservsettings->CallinPrices[1] = 10; myservsettings->CallinPrices[2] = 10;
			myservsettings->CallinCooldowns[0] = 3; myservsettings->CallinCooldowns[1] = 3; myservsettings->CallinCooldowns[2] = 3;
			myservsettings->CallinBuildups[0] = 3; myservsettings->CallinBuildups[1] = 3; myservsettings->CallinBuildups[2] = 3;

		}
	}
	else if (Object->IsA(ATrVehicleStation::StaticClass())) {
		ATrVehicleStation *mystation = (ATrVehicleStation *) Object;
		if (mystation) {
			fprintf( mylog, "patchiing TrVehicleStation\n"); fflush(mylog);
			mystation->m_SpawnList[0].m_VehicleClass = mystation->m_SpawnList[3].m_VehicleClass; //Gravcycle
			mystation->m_SpawnList[0].m_rSpawnRotOffset = mystation->m_SpawnList[3].m_rSpawnRotOffset;
			mystation->m_SpawnList[0].m_vSpawnLocOffset = mystation->m_SpawnList[3].m_vSpawnLocOffset;
			mystation->m_SpawnList[0].m_nMaxCount = mystation->m_SpawnList[3].m_nMaxCount = 10;


			mystation->m_SpawnList[1].m_VehicleClass = ATrVehicle_Havoc::StaticClass(); //shrike
			mystation->m_SpawnList[1].m_nMaxCount = 10;
		}
	}
	else if (!strcmp(Object->GetFullName(), "TrProj_StealthSpinfusor TribesGame.Default__TrProj_StealthSpinfusor")) {
		ATrProj_StealthSpinfusor *myssf = (ATrProj_StealthSpinfusor *) Object;
		if (myssf) {
				fprintf(mylog, "inf projectile on %s buff\n", Object->GetFullName()); fflush(mylog);
				myssf->Speed = 5300.0; // 120% Buff
				myssf->m_fProjInheritVelocityPct=1.0;
				myssf->m_fProjInheritVelocityPctZ=1.0;
				myssf->m_fMaxProjInheritPct=1.0;
				myssf->CheckRadius = 50.0;
		}
	}

	if (strstr(Object->GetName(), "Default__TrProj") && (strstr(Object->GetName(), "Tracer") || strstr(Object->GetName(), "Spinfusor") || strstr(Object->GetName(), "TrProj_AssaultRifle") || strstr(Object->GetName(), "Plasma"))) {
		ATrProjectile *proj = (ATrProjectile *) Object;
		if (proj) {
			fprintf(mylog, "debug projectile on %s\n", Object->GetFullName()); fflush(mylog);
			proj->m_bDebugProjectileRadius = 1;
			proj->Speed = 600.0;
			proj->LifeSpan = 60;
			//proj->bCollideActors = 0;
			proj->CustomGravityScaling = 0;
			proj->TossZ = 0;
			proj->m_bSimulateAutonomousProjectiles = 0;
			proj->m_bTether = 1;

			proj->m_fProjInheritVelocityPct=0.0;
			proj->m_fProjInheritVelocityPctZ=0.0;
			proj->m_fMaxProjInheritPct=0.0;
		}
	}
}



bool Function_TribesGame_TrPlayerController_PlayerTick_Global(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	static int f = 0;
	if (++f > 3) { f = 0; }
	else return false;

	if (closefile) {
		closefile = false;
		fclose(mylog);
		mylog = fopen("C:\\Log.txt", "w+" );
	}

	ATrPlayerController_eventPlayerTick_Parms Tick_Params;
	memcpy(&Tick_Params, pParams, sizeof(ATrPlayerController_eventPlayerTick_Parms));

	ATrPlayerController *MyTrPlayerController = (ATrPlayerController *) dwCallingObject;
	pPC = MyTrPlayerController;
	if (!pPC) return false;

	return false;
}


void OnCanvasPostRender(UCanvas *pCanvas) {
	ATrPawn *me = (ATrPawn *) pPC->Pawn;
	if (!me) return;
	FColor clr; clr.A = 255; clr.B = 255; clr.G = 180; clr.R = 180; pCanvas->DrawColor = clr;
	pCanvas->CurY = 200; pCanvas->CurX = 10;

	//*
	static bool a = false;
	if (!a) { //changes name for video recorind
		a = true;
		pPC->Pawn->PlayerReplicationInfo->PlayerName = FString(L"Scoobydo");
		for (APawn *p = pPC->Pawn->WorldInfo->PawnList; p; p = p->NextPawn) { 
				if (!p->PlayerReplicationInfo) continue;
				if (p == pPC->Pawn) {
					p->PlayerReplicationInfo->PlayerName = FString(L"Scoobydo");
					break;
				}
		}
	}



	wchar_t WideCharBuffer[256];
	if (me->Weapon && me->Weapon->Name.Index) {
		pCanvas->CurY += 50; pCanvas->CurX = 10;
		MultiByteToWideChar(CP_ACP, 0, me->Weapon->GetName()+9, -1,  WideCharBuffer, 150); 
		DrawPrintf(pCanvas, 2.0, 2.0, L"Weapon: %s",  WideCharBuffer);
	}

	/* Radar, Minimap
	DrawMiniMap(pCanvas, radarscale);
	DrawPrintf(pCanvas, 2.0, 2.0, L"Radar Scale: %s", radarscale == 0? L"1x" : (radarscale == 1? L"2x" : (radarscale == 2? L"4x" : L"8x")));
	//*/
	

	

	DrawPrintf(pCanvas, 2.0, 2.0, L"Bloom?");

	return;
}


bool Function_TribesGame_TrGameViewportClient_PostRender(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	UTrGameViewportClient_eventPostRender_Parms renderparams;
	memcpy(&renderparams, pParams, sizeof(UTrGameViewportClient_eventPostRender_Parms));
	UCanvas *pCanvas = renderparams.Canvas;
	if(pCanvas != NULL)
	{
		if (!pPC) return false;
		if (!pPC->Pawn) return false;
		if (!pPC->Pawn->WorldInfo) return false;
		if (!pPC->Pawn->WorldInfo->PawnList) return false;
		if (!pPC->Pawn->PlayerReplicationInfo) return false;
		if (!pPC->Pawn->PlayerReplicationInfo->Team) return false;

		OnCanvasPostRender(pCanvas);
	}
	return false;
}

void ConsoleCommand(wchar_t *command) {
		pPC->ConsoleCommand(command, 0);
}


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
	fprintf ( mylog, "GObjects: 0x%X\n", GObjects );

	// get GNames
	//GNames = *(unsigned long*) ( TFLHACKT00LS::FindPattern( (unsigned long) miGame.lpBaseOfDll, miGame.SizeOfImage, (unsigned char*) GNames_Pattern, (char*) GNames_Mask ) + GNames_Offset );
	
	// log
	fprintf ( mylog, "GNames:   0x%X\n", GNames );

	UObject *Object = UObject::GObjObjects()->Data[ 1 ];
	unsigned long *cObject = (unsigned long *) Object;
	unsigned long *ProcessEventsAddress = (unsigned long *) (*(cObject) + 65*sizeof(unsigned long));

	fprintf ( mylog, "ProcessEventsAddress:   0x%X @ 0x%X @ 0x%X\n", Object, ProcessEventsAddress, *ProcessEventsAddress);


	hooks_init();
	{
		SetupHook(HOOK_Function_TribesGame_TrPlayerController_PlayerTick_Global, &Function_TribesGame_TrPlayerController_PlayerTick_Global, "Function TribesGame.TrPlayerController.PlayerTick", 0);
		//SetupHook(HOOK_Function_TribesGame_TrGameViewportClient_PostRender, &Function_TribesGame_TrGameViewportClient_PostRender, "Function TribesGame.TrGameViewportClient.PostRender", 0);
	//	SetupHook(HOOK_Function_TribesGame_TrPlayerController_PlayerTick_JetPack, &Function_TribesGame_TrPlayerController_PlayerTick_JetPack, "Function TribesGame.TrPlayerController.PlayerTick", 0);
	}
	hook_startprocessevents(*ProcessEventsAddress);


}


void onDLL_PROCESS_DETACH() {
			 if (mylog){
				fprintf(mylog, "DLL_PROCESS_DETACH\n"); 
				fclose(mylog); mylog = 0;
			 }
}
