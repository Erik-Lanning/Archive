#include "Globals.h"




struct Hooks {
	UFunction *UFunctionToHook;
	HookedProccessEvents HookedpProcessEvent;
	UClass *CallingClass;
};
Hooks myhooks[MY_HOOKS_SIZE] = { 0 };
tProcessEvent pProcessEvent = 0;
VOID __stdcall NakedFunction(UFunction*, PVOID, PVOID) { }
tProcessEvent pNakedProcessEvent = &NakedFunction;

bool DispatchF(UObject *pCallObject, UFunction *pFunction, void *pParams, void *pResult)
{
	//fprintf(mylog, "DispatchF: %x @ %x \n", pCallObject, pFunction); fflush(mylog);
    if(pFunction && pCallObject) {
		static char FunctionName[128];
		static char CallingName[128];
		//
		strcpy(FunctionName, pFunction->GetFullName());
		strcpy(CallingName, pCallObject->GetFullName());

		//int found = 0;
		//char *abc[] = { "Tick", "UpdateCamera", "LayoutPlayers", "PreRender", "Reset", "GetFOVAngle", "PostRender", "GetPlayerViewPoint", "GetSubtitleRegion" };
		//for (int i = 0; i < sizeof(abc) / sizeof(char *); i++) if (strstr(FunctionName, abc[i])) { found = 1; break; } 
		//if (!found) fprintf(mylog, "[%x] %s Calling  %s [%x]\n", pCallObject, CallingName, FunctionName, pFunction); fflush(mylog);
		
		for (int i =  0; i < MY_HOOKS_SIZE; i++)  {
			if (myhooks[i].UFunctionToHook == pFunction) {
					if (myhooks[i].CallingClass) {
						if (!pCallObject->IsA(myhooks[i].CallingClass)) continue;
					}
					if (myhooks[i].HookedpProcessEvent((hooknum) i, pCallObject, pFunction, pParams, pResult)) { //true = don't call orignal
						return true;
					}
			}
		}
    }
	return false;
}


UObject *pCallObject;
void __stdcall ProxyFunction(UFunction *pFunction, void *pParms, void *pResult)
{
    __asm pushad;
    __asm mov pCallObject, ecx;

    if(pFunction)
    {
		if (DispatchF(pCallObject, pFunction, pParms, pResult)) {
			__asm mov ecx, pCallObject;
			__asm popad;
			NakedFunction(pFunction, pParms, pResult);
		}
		else {
			__asm mov ecx, pCallObject;
			__asm popad;
			pProcessEvent(pFunction, pParms, pResult);
		}
    } 
	else {
		__asm mov ecx, pCallObject;
		__asm popad;
		pProcessEvent(pFunction, pParms, pResult);
	}
}

//SetupHook(HOOK_Function_TribesGame_TrPlayerController_PlayerTick_Global, &Function_TribesGame_TrPlayerController_PlayerTick_Global, "Function TribesGame.TrPlayerController.PlayerTick", 0);
bool SetupHook( hooknum ID, HookedProccessEvents PE, char *strFunction, UClass *thisclassonly)
{
	UFunction *myfunc = (UFunction *) UObject::FindObject<UFunction>( strFunction );
	if (!myfunc) return false;
	myhooks[ ID ].HookedpProcessEvent = PE;
	myhooks[ ID ].UFunctionToHook = myfunc;
	myhooks[ ID ].CallingClass = thisclassonly;
	return true;
}



void hooks_init() {
		for (int i = 0; i < MY_HOOKS_SIZE; i++) { myhooks[i].UFunctionToHook = 0; myhooks[i].HookedpProcessEvent = 0; }
}

void hook_startprocessevents(unsigned long ProcessEventsAddress) {
	pProcessEvent = ( tProcessEvent )DetourFunction( ( PBYTE ) ProcessEventsAddress, ( PBYTE ) &ProxyFunction ); //0x00458B30
}
void hook_remove_processevents() {
    if (hook_isloaded()) DetourRemove((PBYTE) pProcessEvent, (PBYTE) &ProxyFunction); pProcessEvent = 0;
	pProcessEvent = 0;
}

bool hook_isloaded() {
	if (pProcessEvent) return true;
	return false;
}