#include "Globals.h"

bool Function_TrProj_SpikeLauncher_PreBeginPlay(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
bool SpikeLauncher_Function_TribesGame_TrProj_StickyGrenade_PostBeginPlay(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
bool SpikeLauncher_Function_TribesGame_TrProjectile_Touch(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
bool SpikeLauncher_Function_UTGame_UTProjectile_Destroyed(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
bool SpikeLauncher_Function_TribesGame_TrProj_Grenade_Timer(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
void ExplodeIt();