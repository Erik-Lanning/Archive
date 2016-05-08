#include "MiniMap.h"



void DrawMiniMap(UCanvas *pCanvas, int scale) {
	ATrPawn *me = (ATrPawn *) pPC->Pawn;

	float fscale = 0;

	switch (scale) {
		case 0:
			fscale = 4000.0f;
			break;

		case 1:
			fscale = 8000.0f;
			break;

		case 2:
			fscale = 16000.0f;
			break;

		case 3:
			fscale = 32000.0f;
			break;

		default:
			fscale = 4000.0f;
	}
	FVector Loc;
    FVector AxisX, AxisY, AxisZ, Delta, Transformed;
    FRotator Rot = me->eventGetViewRotation();
	//pPC->
	FVector Origin; Origin.X = 100.0f; Origin.Y = 100.0f; Origin.Z = 0;

	FVector TargetLocation2D = Origin;
	FColor myCOLOR; myCOLOR.A = 200;  myCOLOR.R = 80; myCOLOR.G = 80; myCOLOR.B = 200;
	pCanvas->Draw2DLine(TargetLocation2D.X - 2, TargetLocation2D.Y - 2,  TargetLocation2D.X + 2,  TargetLocation2D.Y + 2, myCOLOR);
	pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y - 2,  TargetLocation2D.X - 2,  TargetLocation2D.Y + 2, myCOLOR);
	pCanvas->Draw2DLine(TargetLocation2D.X, TargetLocation2D.Y - 2,  TargetLocation2D.X,  TargetLocation2D.Y + 2, myCOLOR);
	pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y,  TargetLocation2D.X - 2,  TargetLocation2D.Y, myCOLOR);
	pCanvas->Draw2DLine(TargetLocation2D.X-1, TargetLocation2D.Y - 2,  TargetLocation2D.X-1,  TargetLocation2D.Y + 2, myCOLOR);
	pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y+1,  TargetLocation2D.X - 2,  TargetLocation2D.Y+1, myCOLOR);


	float StartPosY = 0;
	float StartPosX = 73.0f;
	float LastX = Origin.X + StartPosX;
	float LastY = Origin.Y;
	 myCOLOR.A = 255;  myCOLOR.R = 0; myCOLOR.G = 0; myCOLOR.B = 255;
	
	for (float i = 0; i < 360.0f; i += 1.0f) {
		float tetha = i / 180.0f * UCONST_Pi;
		TargetLocation2D.X = (cos(tetha) * StartPosX) - (sin(tetha) * StartPosY);
		TargetLocation2D.Y = (sin(tetha) * StartPosX) + (cos(tetha) * StartPosY);
		TargetLocation2D.Z = 0;
		TargetLocation2D = Add(Origin, TargetLocation2D);

		
		pCanvas->Draw2DLine(TargetLocation2D.X,TargetLocation2D.Y, LastX, LastY, myCOLOR);

		LastX = TargetLocation2D.X;
		LastY = TargetLocation2D.Y;
	}


	for (APawn *p = me->WorldInfo->PawnList; p; p = p->NextPawn) { 
		if (!p->PlayerReplicationInfo) continue;
		if (!p->PlayerReplicationInfo->Team) continue;
		if(p->bDeleteMe || p == me || p->bHidden || p->Health <= 0 || !p->PlayerReplicationInfo->Team || p->PlayerReplicationInfo->Team == me->PlayerReplicationInfo->Team) continue;
		if (!p->IsA(ATrPlayerPawn::StaticClass())) continue; // || p->IsA(ATrBotPawn::StaticClass()) - for training exculsion

		FVector MyLoc =  me->Location;  MyLoc.Z = 0; 
		FVector HisLoc =  p->Location;  HisLoc.Z = 0; 
		FVector HisDirection = Sub(HisLoc, MyLoc);





		fprintf(mylog, "MiniMap, [Me x: %f, y: %f], [His x: %f, y: %f]\n", MyLoc.X, MyLoc.Y, HisLoc.X, HisLoc.Y); fflush(mylog);
		float size = VSize(HisDirection);
		fprintf(mylog, "HidDirection, size: %f, X: %f, Y: %f\n",  VSize(HisDirection), HisDirection.X, HisDirection.Y); fflush(mylog);
		if (size > fscale) HisDirection = Scale(HisDirection, (fscale / size));
		fprintf(mylog, "HidDirection, size: %f, X: %f, Y: %f\n",  VSize(HisDirection), HisDirection.X, HisDirection.Y); fflush(mylog);
		
		HisDirection = Scale(HisDirection, (70.0f / fscale));
		fprintf(mylog, "HidDirection, size: %f, X: %f, Y: %f\n",  VSize(HisDirection), HisDirection.X, HisDirection.Y); fflush(mylog);


		FVector NewRotatedDirection;
		float tetha = (Rot.Yaw * URotationToRadians) - ((90.0f + 180.0f) / 180.0f * UCONST_Pi);
		NewRotatedDirection.X = (cos(-tetha) * HisDirection.X) - (sin(-tetha) * HisDirection.Y);
		NewRotatedDirection.Y = (sin(-tetha) * HisDirection.X) + (cos(-tetha) * HisDirection.Y);
		NewRotatedDirection.Z = 0;
		HisDirection = NewRotatedDirection;
		fprintf(mylog, "Rotation: Radians: %f @ Degrees: %d\n", (Rot.Yaw * URotationToRadians), (int) ((Rot.Yaw * URotationToRadians) * 180.0f / UCONST_Pi) % 360); fflush(mylog);
		fprintf(mylog, "HidDirection, size: %f, X: %f, Y: %f\n",  VSize(HisDirection), HisDirection.X, HisDirection.Y); fflush(mylog);


		FVector TargetLocation2D = Add(Origin, HisDirection); //Scale(57.14)
		fprintf(mylog, "TargetLocation2D: %f %f\n", TargetLocation2D.X, TargetLocation2D.Y); fflush(mylog);
		FColor myCOLOR; myCOLOR.A = 255;  myCOLOR.R = 79; myCOLOR.G = 255; myCOLOR.B = 79;

		pCanvas->Draw2DLine(TargetLocation2D.X - 2, TargetLocation2D.Y - 2,  TargetLocation2D.X + 2,  TargetLocation2D.Y + 2, myCOLOR);
		pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y - 2,  TargetLocation2D.X - 2,  TargetLocation2D.Y + 2, myCOLOR);
		myCOLOR.A = 255;  myCOLOR.R = 255; myCOLOR.G = 0; myCOLOR.B = 0;
		pCanvas->Draw2DLine(TargetLocation2D.X, TargetLocation2D.Y - 2,  TargetLocation2D.X,  TargetLocation2D.Y + 2, myCOLOR);
		pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y,  TargetLocation2D.X - 2,  TargetLocation2D.Y, myCOLOR);
		pCanvas->Draw2DLine(TargetLocation2D.X-1, TargetLocation2D.Y - 2,  TargetLocation2D.X-1,  TargetLocation2D.Y + 2, myCOLOR);
		pCanvas->Draw2DLine(TargetLocation2D.X + 2, TargetLocation2D.Y+1,  TargetLocation2D.X - 2,  TargetLocation2D.Y+1, myCOLOR);

		

	}
	//fprintf(mylog, "%s ESP\n", dwCallingObject->GetFullName());
}
