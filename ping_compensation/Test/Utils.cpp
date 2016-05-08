#include "Globals.h"




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
