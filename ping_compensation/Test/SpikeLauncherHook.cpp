#include "SpikeLauncherHook.h"

int state = 0;
ATrProj_SpikeLauncher *myprj = 0;


void ExplodeIt() 
{
	FVector z; z.X = z.Y = z.Z = 0;
	if (state == 2 && myprj) { myprj->Timer(); myprj = 0; state = 0;  }
}


//Function TribesGame.TrProj_SpikeLauncher.PreBeginPlay
bool Function_TrProj_SpikeLauncher_PreBeginPlay(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	state = 0;
	myprj = 0;
	return false;
}

//"Function TribesGame.TrProj_StickyGrenade.PostBeginPlay", only ATrProj_SpikeLauncher::StaticClass()
bool SpikeLauncher_Function_TribesGame_TrProj_StickyGrenade_PostBeginPlay(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{

	state = 2;
	myprj = (ATrProj_SpikeLauncher *) dwCallingObject;
	return false;
}



//[57adbc00] TrProj_SpikeLauncher TheWorld.PersistentLevel.TrProj_SpikeLauncher Calling  Function UTGame.UTProjectile.Destroyed [9f1a5c0]
//HOOK_SpikeLauncher_Function_UTGame_UTProjectile_Destroyed
bool SpikeLauncher_Function_UTGame_UTProjectile_Destroyed(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	
	state = 0;
	myprj = 0;
	return false;
}

//Function TribesGame.TrProjectile.Touch, only ATrProj_SpikeLauncher::StaticClass()
bool SpikeLauncher_Function_TribesGame_TrProjectile_Touch(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	if (state == 2) {
		ATrProj_SpikeLauncher *a = (ATrProj_SpikeLauncher *) dwCallingObject;
		fprintf(mylog, "**** Hit something :D\n");
		//fprintf(mylog, "        3*********** STATE: %d\n", state); 

		AProjectile_eventTouch_Parms Touch_Parms;
		memcpy(&Touch_Parms, pParams, sizeof(AProjectile_eventTouch_Parms));
		if (!Touch_Parms.Other) { fprintf(mylog, "**** No a other\n"); fflush(mylog); }
		else {
			fprintf(mylog, "**** Hit details, Other Name: %s\n", Touch_Parms.Other->GetFullName()); fflush(mylog);
			fprintf(mylog, "**** Hit details, StopsProjectile: %d\n", Touch_Parms.Other->StopsProjectile(a) ? 1 : 0); fflush(mylog);
					
		}
		fprintf(mylog, "**** Role %d\n", a->Role); fflush(mylog);
		if (!Touch_Parms.Other->StopsProjectile(a)) return false;

		if (a->m_bHasStuckToTarget) 
		{
		}
		else {
			if(!a->m_bHasStuckToTarget)
			{
				fprintf(mylog, "**XXX** Role %d\n", a->Role); fflush(mylog);
				a->StickToTarget(Touch_Parms.Other, Touch_Parms.HitLocation, Touch_Parms.HitNormal); //StickToTarget(Other, HitLocation, HitNormal);
				fprintf(mylog, "*XX XX*** Role %d\n\n", a->Role); fflush(mylog);
				return true;
			}
		}
	}
	return false;
}


