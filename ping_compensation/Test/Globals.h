#include <Windows.h>
#include <math.h>
#include <stdio.h>

#pragma once
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
//#define sprintf_s sprintf
//#define strcpy_s strcpy
//#define strcat_s strcat
#include "../SdkHeaders.h"
#include "../VMT/Toolkit.h"
#include "../VMT/vmthooks.h"
#include "detours.h"
#include "Hooks.h"		
#include "TFL_HT.h"
#include <iostream>
#include <fstream>
std::ofstream f_out("C:\\Users\\Tyler\\Desktop\\log.txt");
#define EQP_NONE       0
#define EQP_Melee      1
#define EQP_Primary    2
#define EQP_Secondary  3
#define EQP_Pack       4

#define ROLE_None             0
#define ROLE_SimulatedProxy   1
#define ROLE_AutonomousProxy  2
#define ROLE_Authority        3
#define ROLE_MAX              4
#define GOBJECTS_MAX	167471
#define GOBJECTS_ENGINE 164042

extern HMODULE myhInst;
extern FILE *mylog;
extern ATrPlayerController *pPC;

enum hooknum {
	HOOK_Function_TribesGame_TrPlayerController_PlayerTick_Global,
	HOOK_Function_TribesGame_TrGameViewportClient_PostRender,
	HOOK_Function_TribesGame_TrPlayerController_PlayerTick_JetPack,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p
};
void onAttach();
void onDLL_PROCESS_DETACH();

#define UCONST_Pi 3.1415926
#define URotation180  32768 
#define URotationToRadians  UCONST_Pi / URotation180  //0.000095873797607421875

float Dot(FVector vec1, FVector vec2);
float Scalar(FVector vec1, FVector vec2);
FVector Add(FVector vec1, FVector vec2);
FVector Sub(FVector vec1, FVector vec2);
FRotator Sub(FRotator rot1, FRotator rot2);
FVector Scale(FVector vec1, float s);
float Distance3D(FVector vec1, FVector vec2);
float VSize (FVector &v);
float VSize2D (FVector &v);
void Normalize (FVector &v);
FVector Normal (FVector v);
FVector RotationToVector(FRotator R);
void inline GetAxes (FRotator R, FVector &X, FVector &Y, FVector &Z);
FVector WorldToScreen(UCanvas* pCanvas, FVector Location );
float FMin(float f1, float f2);
float FMax(float f1, float f2);
float GetSpeed(FVector projdirection, FVector PawnVelocity);
void DrawX(UCanvas *pCanvas, FVector Location, FColor myCOLOR, float Scale);
void DrawPrintf(UCanvas *pCanvas, float scalex, float scaley, wchar_t *format, ...);
FColor makecolor(float r, float g, float b, float alpha);
FVector makevector(float x, float y, float z);

typedef VOID (__stdcall * tProcessEvent)(UFunction*, PVOID, PVOID);
typedef bool (* HookedProccessEvents)(hooknum id, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);

#define MY_HOOKS_SIZE 20
bool SetupHook( hooknum ID, HookedProccessEvents PE, char *strFunction, UClass *thisclassonly);
extern  tProcessEvent pProcessEvent;

void hook_startprocessevents(unsigned long ProcessEventsAddress);
void hook_remove_processevents();
bool hook_isloaded();
void hooks_init();



//utils
FVector makevector(float x, float y, float z) {
	FVector a;
	a.X = x; a.Y = y; a.Z = z;
	return a;
}


FColor makecolor(float r, float g, float b, float alpha) {
	FColor a;
	a.R = r; a.G = g; a.B = b; a.A = alpha;
	return a;
}

FVector Scale(FVector vec1, float s) {
	FVector result;
	result.X = vec1.X * s;
	result.Y = vec1.Y * s;
	result.Z = vec1.Z * s;
	return result;
}

FRotator Sub(FRotator rot1, FRotator rot2) {
	FRotator result;
	result.Pitch = rot1.Pitch - rot2.Pitch;
	result.Yaw =   rot1.Yaw -   rot2.Yaw;
	result.Roll =  rot1.Roll -  rot2.Roll;
	return result;
}

FVector Sub(FVector vec1, FVector vec2) {
	FVector result;
	result.X = vec1.X - vec2.X;
	result.Y = vec1.Y - vec2.Y;
	result.Z = vec1.Z - vec2.Z;
	return result;
}


FVector Add(FVector vec1, FVector vec2) {
	FVector result;
	result.X = vec1.X + vec2.X;
	result.Y = vec1.Y + vec2.Y;
	result.Z = vec1.Z + vec2.Z;
	return result;
}

float Dot(FVector vec1, FVector vec2) {
	return (vec1.X * vec2.X) + (vec1.Y * vec2.Y) + (vec1.Z * vec2.Z);
}

float Scalar(FVector vec1, FVector vec2) {
	return (vec1.X * vec2.X) + (vec1.Y * vec2.Y) + (vec1.Z * vec2.Z);
}

float Distance3D(FVector vec1, FVector vec2){
        float distance = sqrt( ((vec1.X - vec2.X )*(vec1.X - vec2.X) + (vec1.Y - vec2.Y)*(vec1.Y - vec2.Y)+ (vec1.Z - vec2.Z)*(vec1.Z - vec2.Z)) );
        return distance;
}

float VSize (FVector &v)
{
        return sqrt(v.X*v.X + v.Y*v.Y + v.Z*v.Z);
}
float VSize2D (FVector &v)
{
        return sqrt(v.X*v.X + v.Y*v.Y);
}



void Normalize (FVector &v)
{
        float size = VSize(v);
 
        if ( !size )
        {
                v.X = v.Y = v.Z = 0;
        }
        else
        {
                v.X /= size;
                v.Y /= size;
                v.Z /= size;
        }
}

FVector Normal (FVector v)
{
       FVector Ret; 
	   Ret.X = v.X;
	   Ret.Y = v.Y;
	   Ret.Z = v.Z;
	   fprintf(mylog, "Normal Ret %f %f %f\n", Ret.X, Ret.Y, Ret.Z);
	   Normalize(Ret);
	   fprintf(mylog, "Normal Ret2 %f %f %f\n", Ret.X, Ret.Y, Ret.Z);
	   return Ret;
}


FVector RotationToVector(FRotator R)
{
	FVector Vec;
	float fYaw =  R.Yaw * URotationToRadians; //* 0.00009587371826171875
	float fPitch = R.Pitch * URotationToRadians;
	float CosPitch = cos(fPitch);
	Vec.X = cos(fYaw) * CosPitch;
	Vec.Y = sin(fYaw) * CosPitch;
	Vec.Z = sin(fPitch);

	return Vec;
}

void inline GetAxes (FRotator R, FVector &X, FVector &Y, FVector &Z)
{
        X = RotationToVector(R);
        Normalize(X);
        R.Yaw += 16384;
        FRotator R2 = R;
        R2.Pitch = 0.f;
        Y = RotationToVector(R2);
        Normalize(Y);
        Y.Z = 0.f;
        R.Yaw -= 16384;
        R.Pitch += 16384;
        Z = RotationToVector(R);
        Normalize(Z);
}


FVector WorldToScreen(UCanvas* pCanvas, FVector Location )
{
    FVector Return;
	FVector Loc;
    FVector AxisX, AxisY, AxisZ, Delta, Transformed;
    FRotator Rot;
    
	if (!pPC) {
		return Return;
	}
    if( !pPC->Pawn->IsA( AVehicle::StaticClass()) )
    {
        pPC->Pawn->eventGetActorEyesViewPoint( &Loc, &Rot );
    }
    else if( pPC->Pawn->IsA( ASVehicle::StaticClass()) )
    {
        ASVehicle* Vehicle = (ASVehicle*)pPC->Pawn;
        char* VehicleName = Vehicle->GetFullName();

        
        if( !strcmp( VehicleName, "TrVehicle_GravCycle TheWorld.PersistentLevel.TrVehicle_GravCycle" ) 
        || !strcmp( VehicleName, "TrVehicle_Beowulf TheWorld.PersistentLevel.TrVehicle_Beowulf") )
        {
            float FOV, DeltaTime;
            Vehicle->CalcCamera( DeltaTime, &Loc, &Rot, &FOV );
        }
        
        else if( !strcmp( VehicleName, "TrVehicle_Shrike TheWorld.PersistentLevel.TrVehicle_Shrike" ) )
        {
            pPC->eventGetPlayerViewPoint( &Loc, &Rot );
        }
        
    }

    GetAxes( Rot , AxisX, AxisY, AxisZ );
    
    Delta = pPC->Subtract_VectorVector( Location, Loc );
    Transformed.X = pPC->Dot_VectorVector( Delta, AxisY );
    Transformed.Y = pPC->Dot_VectorVector( Delta, AxisZ );
    Transformed.Z = pPC->Dot_VectorVector( Delta, AxisX );

    if( Transformed.Z < 1.00f )
        Transformed.Z = 1.00f;

    float FOVAngle = pPC->FOVAngle;

    Return.X = ( pCanvas->ClipX / 2.0f ) + Transformed.X * ( ( pCanvas->ClipX / 2.0f ) / pPC->Tan( FOVAngle * CONST_Pi / 360.0f ) ) / Transformed.Z;
    Return.Y = ( pCanvas->ClipY / 2.0f ) + -Transformed.Y * ( ( pCanvas->ClipX / 2.0f ) / pPC->Tan( FOVAngle * CONST_Pi / 360.0f ) ) / Transformed.Z;
    Return.Z = 0;

    return Return;
}


float FMin(float f1, float f2) {
	return (f1 < f2 ? f1 : f2);
}
float FMax(float f1, float f2) {
	return (f1 > f2 ? f1 : f2);
}

float GetSpeed(FVector projdirection, FVector PawnVelocity)
{
	FVector projvelocity = Scale(Normal(projdirection), 3920.0);
	projvelocity.Z += 0;

	float ForwardPct = FMin(Dot(Normal(PawnVelocity), Normal(projdirection)), 0.5);
	float InheritPct = FMax(0.5, ForwardPct);

	projvelocity.X += InheritPct * PawnVelocity.X;
	projvelocity.Y += InheritPct * PawnVelocity.Y;
	projvelocity.Z += 0.5 * PawnVelocity.Z;

	return VSize(projvelocity);
}



void DrawX(UCanvas *pCanvas, FVector Location, FColor myCOLOR, float Scale) {
	if (!pPC) return;
	FVector TargetLocation2D = WorldToScreen(pCanvas, Location);
	pCanvas->Draw2DLine(TargetLocation2D.X - (8 * Scale), TargetLocation2D.Y - (8 * Scale),  TargetLocation2D.X + (8 * Scale),  TargetLocation2D.Y + (8 * Scale), myCOLOR);							
	pCanvas->Draw2DLine(TargetLocation2D.X + (8 * Scale), TargetLocation2D.Y - (8 * Scale),  TargetLocation2D.X - (8 * Scale),  TargetLocation2D.Y + (8 * Scale), myCOLOR);
}



void DrawPrintf(UCanvas *pCanvas, float scalex, float scaley, wchar_t *format, ...)
{
		static wchar_t buff[256];
		va_list v1;
		va_start(v1, format);
		vswprintf(buff,format, v1);
		pCanvas->DrawText(buff, NULL, scalex, scaley, NULL);
		va_end(v1);
}





void NameDump()
{
	// log file
	FILE* Log = NULL;	
	fopen_s ( &Log, "C:\\NameDump.txt", "w+" );
	fprintf ( Log, "NameDump()\n");
	for ( int i = 0x0; i < FName::Names()->Count; i++ )
	{
		if ( ! FName::Names()->Data[ i ] ) { continue; }
		fprintf ( Log, "Name[%06i] %s\n", i, FName::Names()->Data[ i ]->Name );
	}
	fprintf ( Log, "~NameDump()\n");
	fclose ( Log );
}
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


//Magic Chain
    //"Function TrDevice_ConstantFire.WeaponConstantFiring.BeginState"
    //"Function TrDevice_ConstantFire.WeaponConstantFiring.RefireCheckTimer"
    bool Function_TrDevice_ConstantFire_WeaponConstantFiring_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
    //"Function TribesGame.TrPlayerController.PlayerTick"
    bool Function_TribesGame_TrPlayerController_PlayerTick_MagicBullets(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);
	bool COLTTIME(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult);   
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

	static UEngine *Eng = (UEngine*)( *UObject::GObjObjects() )( 164042 );