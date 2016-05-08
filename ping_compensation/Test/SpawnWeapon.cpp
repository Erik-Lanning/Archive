#include "SpawnWeapon.h"



ATrDevice *GetWeapon() {
	if (!pPC) return 0;
	if (!pPC->Pawn) return 0;

	static bool weaponsloaded = false;
	static UClass *weapons_classes[50] = {
		ATrDevice_AccurizedShotgun::StaticClass(),
		ATrDevice_SAP20::StaticClass(),
		ATrDevice_H1::StaticClass(),
		ATrDevice_LR1Mortar::StaticClass(),
		ATrDevice_Spinfusor_100X::StaticClass(),
		ATrDevice_LightSpinfusor_100X::StaticClass(),
		ATrDevice_ArxShotgun::StaticClass(),
		ATrDevice_HeavyImpactNitron::StaticClass(),
		ATrDevice_AVMine::StaticClass(),
		ATrDevice_WallTurretDeployable::StaticClass(),
		ATrDevice_BackupGeneratorDeployable::StaticClass(),
		ATrDevice_FlareGrenade::StaticClass(),
		ATrDevice_DualRhinos::StaticClass(),
		ATrDevice_S22Rifle::StaticClass(),
		ATrDevice_OmniSensorDeployable::StaticClass(),
		ATrDevice_TargetingBeacon::StaticClass(),
		ATrDevice_ArmoredClaymore::StaticClass(),
		0
	};
	//ATrDevice_TargetingBeacon *a; a->SuggestTossVelocity

	static ATrDevice *weapons_devices[50];
	static unsigned int currentweapon = 0;

	if (!weaponsloaded) {
		weaponsloaded = true;

		unsigned int w = 0;
		while (weapons_classes[w] && w < 50) {

			weapons_devices[w] = (ATrDevice *) pPC->Spawn(weapons_classes[w], pPC->Pawn, pPC->Pawn->Name, pPC->Pawn->Location, pPC->Pawn->Rotation, 0, 0);
			if (weapons_devices[w]) fprintf( mylog, "[%d] spawned [%s]\n", w, weapons_devices[w]->GetFullName()); fflush(mylog); 
			w++;
		}
		return 0;
	}


	fprintf( mylog, "currentweapon[%d]\n", currentweapon); fflush(mylog); 
	ATrDevice *ret = weapons_devices[currentweapon++];
	if (weapons_devices[currentweapon] == 0) currentweapon = 0;
	return ret;
}


void SpawnWeapon() {
		fprintf( mylog, "SpawnWeapon...\n"); fflush(mylog); 
		if (!pPC) return;
		fprintf( mylog, "pc ok...\n"); fflush(mylog); 
		ATrPawn *me = (ATrPawn *) pPC->Pawn;
		if (!me) return;
		fprintf( mylog, "me ok...\n"); fflush(mylog); 
		if (!me->InvManager) return;
		fprintf( mylog, "InvManager ok...\n"); fflush(mylog); 
		if (!me->Weapon) return;
		fprintf( mylog, "me->Weapon ok...\n"); fflush(mylog); 

		fprintf( mylog, "Spawning!!!...\n"); fflush(mylog); 
		unsigned char CurrentEquipPoint;
		UClass *WeaponClass;
		ATrInventoryManager *TrInvManager = (ATrInventoryManager *) me->InvManager;
		if (!TrInvManager) return;
		fprintf( mylog, "TrInvManager!!!...\n"); fflush(mylog); 

		CurrentEquipPoint = EQP_Primary;
		ATrDevice *CurrentDevice = (ATrDevice *) me->Weapon;
		/*
		if( CurrentDevice && CurrentDevice->r_eEquipAt == EQP_Secondary )
		{
			CurrentEquipPoint = EQP_Secondary;
		}
		fprintf( mylog, "has it already CurrentEquipPoint = %d\n", CurrentEquipPoint); fflush(mylog);
		*/

		// Remove the current secondary weapon.
		ATrDevice *DeviceToSwap = TrInvManager->GetDeviceByEquipPoint(CurrentEquipPoint);
		if (DeviceToSwap)
		{
			TrInvManager->RemoveFromInventory(DeviceToSwap);

			if (TrInvManager->Role == ROLE_Authority)
			{
				//DeviceToSwap->Destroy();
				fprintf( mylog, "hkilled old wepaont = %d\n", CurrentEquipPoint); fflush(mylog);
			}
		}

		ATrDevice *SpawnedDevice = GetWeapon();
		//WeaponClass = (UClass *) pPC->DynamicLoadObject(*abc, UClass::StaticClass(), 1);
		if (SpawnedDevice) {

			fprintf( mylog, "setting %s\n", SpawnedDevice->GetFullName()); fflush(mylog);
			//DeviceToSwap = (ATrDevice *) pPC->Spawn(WeaponClass, me, me->Name, me->Location, me->Rotation, 0, 0);
			DeviceToSwap = SpawnedDevice;
			if (DeviceToSwap)
			{
				fprintf( mylog, "spawned %s\n", DeviceToSwap->GetFullName()); fflush(mylog);
				// Add the repair gun to inventory, and switch to it.
				TrInvManager->AddInventory((AInventory *) DeviceToSwap, 0);
				fprintf( mylog, "switched tXXXX1\n"); fflush(mylog);
				//me->Weapon = DeviceToSwap;
				DeviceToSwap->r_eEquipAt = CurrentEquipPoint;
				DeviceToSwap->m_RemainingAmmoInClip = 10;
				DeviceToSwap->AddCarriedAmmo(100);
				fprintf( mylog, "switched tXXXX2\n"); fflush(mylog);
				me->bNetDirty = true;
				fprintf( mylog, "switched tXXXX3\n"); fflush(mylog);
				TrInvManager->SwitchWeaponByEquipPoint(CurrentEquipPoint);
				fprintf( mylog, "switched tXXXX4\n"); fflush(mylog);
				fprintf( mylog, "switched to %s\n", DeviceToSwap->GetName()); fflush(mylog);
				// Pulse the HUD just like a pickup does.
				pPC->ClientPulseHUD(1);
				fprintf( mylog, "pulksed hud\n"); fflush(mylog);
			}

			//else fprintf( mylog, "has it already\n"); fflush(mylog);
			fprintf( mylog, "end of spawnweapon hud\n"); fflush(mylog);

			fprintf( mylog, "XX Spawning...\n"); fflush(mylog); //need to check TrInvManager->HasInventoryOfClass
			while (1) {
				Sleep(100);
			}
		}
		else fprintf( mylog, "settingX \n"); fflush(mylog);
		while (1) {
			Sleep(100);
		}


}