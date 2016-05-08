#include "JetPack.h"



	/*
	static FVector lastspeed = { 0, 0, 0 };
	static FVector myspeed = { 0, 0, 0 };
	static float mytime = 0;
	static FVector Drag = { 0, 0, 0 };
	static float myacc, myacc_x, myacc_y, myacc_z;
	static int  k = 0;
	if (k++ == 5) {
		k = 0;
		myspeed = me->Velocity;
		Drag.X = ((myspeed.X * myspeed.X) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics);
		Drag.Y = ((myspeed.Y * myspeed.Y) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics);
		Drag.Z = ((myspeed.Z * myspeed.Z) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics);
		if (myspeed.X < 0) Drag.X = -Drag.X;
		if (myspeed.Y < 0) Drag.Y = -Drag.Y;
		if (myspeed.Z < 0) Drag.Z = -Drag.Z;

		myacc = (((VSize(myspeed) - VSize(lastspeed))  / mytime)) / UUToSanics;
		myacc_x = (((myspeed.X - lastspeed.X)  / mytime)) / UUToSanics;
		myacc_y = (((myspeed.Y - lastspeed.Y)  / mytime)) / UUToSanics;
		myacc_z = (((myspeed.Z - lastspeed.Z)  / mytime)) / UUToSanics;

		mytime = 0;
		lastspeed = myspeed;
	}

	pCanvas->CurY += 30; pCanvas->CurX = 10;
	clr.A = 255; clr.B = 0; clr.G = 0; clr.R = 255; pCanvas->DrawColor = clr;
	DrawPrintf(pCanvas, 2.5, 2.5, L"Speed: %7.2f [X: %7.2f, Y: %7.2f, Z: %7.2f]  (Sanics/S)", (float) VSize(myspeed) / UUToSanics, myspeed.X / UUToSanics, myspeed.Y / UUToSanics, myspeed.Z / UUToSanics); 
	pCanvas->CurY += 30; pCanvas->CurX = 10;
	DrawPrintf(pCanvas, 2.5, 2.5, L"Drag - X: %7.2f, Y: %7.2f, Z: %7.2f (Sanics/S^2)", (float) Drag.X / UUToSanics, (float) Drag.Y / UUToSanics, (float) Drag.Z / UUToSanics); 
	pCanvas->CurY += 30; pCanvas->CurX = 10;
	DrawPrintf(pCanvas, 2.5, 2.5, L"TotalAvrageAcceleration: %7.2f [X: %7.2f, Y: %7.2f, Z: %7.2f] (Sanics/S^2)", myacc, myacc_x, myacc_y, myacc_z); 
	mytime += pPC->Pawn->WorldInfo->DeltaSeconds;

	bool issking = me->r_bIsSkiing;
	bool directional = ((KeyBoard_A || KeyBoard_D || KeyBoard_S || KeyBoard_W) && issking)? true : false;

	clr.A = 255; clr.B = 0; clr.G = 255; clr.R = 255; pCanvas->DrawColor = clr;
	pCanvas->CurY += 30; pCanvas->CurX = 10;
	DrawPrintf(pCanvas, 2.5, 2.5, L"Mode: %s + %s air control", pPC->m_bPressingJetpack? L"Jetting" : L"Falling", directional? L"Strong" : L"Weak  ");
	pCanvas->CurY += 30; pCanvas->CurX = 10;
	DrawPrintf(pCanvas, 2.5, 2.5, L"     %s            %s      %s", KeyBoard_W? L"W" : L" ", KeyBoard_RBUTTON? L"RBUTTON" : L"       ", KeyBoard_SPACE? L"SPACE" : L"     "); 
	pCanvas->CurY += 30; pCanvas->CurX = 10;
	DrawPrintf(pCanvas, 2.5, 2.5, L"%s   %s    %s", KeyBoard_A? L"A" : L" ", KeyBoard_S? L"S" : L" ", KeyBoard_D? L"D" : L" " );  

	*/



void WalkingStateProcessMove (ATrPlayerController *MyPPc, float DeltaTime, struct FVector newAccel, unsigned char DoubleClickMove, struct FRotator DeltaRot )
{

	{
		MyPPc->Pawn->Velocity = Add(MyPPc->Pawn->Velocity, Scale(newAccel, DeltaTime)); //Pawn.Velocity += newAccel*DeltaTime;
		return;
	}

	static UFunction* pFnProcessMove = NULL;

	if ( ! pFnProcessMove )
		pFnProcessMove = (UFunction*) UObject::GObjObjects()->Data[ 76201 ]; //normal: 7773, hirez: 76201

	APlayerController_execProcessMove_Parms ProcessMove_Parms;
	ProcessMove_Parms.DeltaTime = DeltaTime;
	memcpy ( &ProcessMove_Parms.newAccel, &newAccel, 0xC );
	ProcessMove_Parms.DoubleClickMove = DoubleClickMove;
	memcpy ( &ProcessMove_Parms.DeltaRot, &DeltaRot, 0xC );

	MyPPc->ProcessEvent ( pFnProcessMove, &ProcessMove_Parms, NULL );
};


bool MyPlayerMove(float DeltaTime, ATrPlayerController *MyPPc) {
	FVector X, Y, Z, newAccel;
	unsigned char DoubleClickMove;
	FRotator OldRotation;
	bool bSaveJump;
	float MaxAccel;
	FVector Velocity2D;
	float groundSpeedThrottle, pawnGroundSpeed, AccelSpeed;
	ATrPawn *TRP;
	ATrDevice_Blink *BlinkPack;
	MyPPc->m_CurrentDecelerationFactor = 0;
	MyPPc->m_bAirSpeedBoundToGroundSpeed = false;
	TRP = (ATrPawn *) MyPPc->Pawn;
	// End:0x54 Loop:False
	if(!TRP)
	{
		//MyPPc->GotoState('Dead');
		return false;
	}
	// End:0xbf6
	else
	{
		// End:0x158 Loop:False
		if(TRP)
		{
			// End:0xd6 Loop:False
			if(MyPPc->m_bPressingJetpackButton && (!MyPPc->m_bPressingJetpack) && (TRP->GetPowerPoolPercent() >= 0.10) && (!MyPPc->eventIsMoveInputIgnored()))
			{
				MyPPc->EnableJetpack(true, MyPPc->m_bJumpJet, 0);
			}
			// End:0x158
			else
			{
				// End:0x12d Loop:False
				if(MyPPc->m_bPressingJetpack && (TRP->GetPowerPoolPercent() <= 0.00 || (MyPPc->eventIsMoveInputIgnored())))
				{
					MyPPc->EnableJetpack(false, true, 0);
				}
				// End:0x158
				else
				{
					// End:0x158 Loop:False
					if(!MyPPc->m_bPressingJetpackButton && (MyPPc->m_bPressingJetpack))
					{
						MyPPc->EnableJetpack(false, true, 0);
					}
				}
			}
		}
		// End:0x245 Loop:False
		if(MyPPc->m_bBlink)
		{
			BlinkPack = (ATrDevice_Blink *) (MyPPc->GetDeviceByEquipPoint(4));
			// End:0x236 Loop:False
			if(BlinkPack)
			{
				OldRotation = MyPPc->Rotation;
				MyPPc->UpdateRotation(DeltaTime);
				// End:0x203 Loop:False

				WalkingStateProcessMove(MyPPc, DeltaTime, newAccel, 0, Sub(OldRotation, MyPPc->Rotation));
			}
			MyPPc->m_bBlink = false;
		}
		//fprintf(mylog, "1555_5 end\n"); fflush(mylog);
		// End:0xbf6
		else
		{
			// End:0x661 Loop:False
			if(MyPPc->m_bPressingJetpack)
			{
				MyPPc->GetAxes(MyPPc->Pawn->Rotation, &X, &Y, &Z);
				newAccel = Add(Scale(X, MyPPc->PlayerInput->aForward), Scale(Y, MyPPc->PlayerInput->aStrafe));
				newAccel = Scale(Normal(newAccel), MyPPc->Pawn->AirSpeed);
				newAccel = TRP->GetJetpackAirControl(newAccel, Z);

				OldRotation = MyPPc->Rotation;
				MyPPc->UpdateRotation(DeltaTime);
				// End:0x482 Loop:False
				if(MyPPc->PlayerInput->aForward > 0.00)
				{
					AccelSpeed = VSize(newAccel);
					//newAccel = newAccel << MyPPc->Pawn->Rotation;

					FVector CamX, CamY, CamZ, Result;
					MyPPc->GetAxes(MyPPc->Pawn->Rotation, &CamX, &CamY, &CamZ);
					newAccel = Add(Add(Scale(CamX, newAccel.X), Scale(CamY, newAccel.Y)), Scale(CamZ, newAccel.Z));

					newAccel.X = newAccel.X * TRP->m_fForwardJettingPct;

					//newAccel = newAccel >> MyPPc->Pawn->Rotation;
					MyPPc->GetUnAxes(MyPPc->Pawn->Rotation, &CamX, &CamY, &CamZ);
					newAccel = Add(Add(Scale(CamX, newAccel.X), Scale(CamY, newAccel.Y)), Scale(CamZ, newAccel.Z));
					newAccel = Scale(Normal(newAccel), AccelSpeed);
				}
				
				TRP->eventUpdateJetpackEffects();
				// End:0x5e1 Loop:False
				if(MyPPc->m_fRemainingInitiatingJettingTime > 0.00)
				{
					pawnGroundSpeed = VSize(TRP->Velocity);
					groundSpeedThrottle = 1.00;
					// End:0x58e Loop:False
					if(pawnGroundSpeed > TRP->GroundSpeed && 0) //disabled!
					{
						groundSpeedThrottle = 0.00;
						// End:0x58e Loop:False
						if(pawnGroundSpeed < TRP->m_fMaxJetpackBoostGroundspeed)
						{
							groundSpeedThrottle = 1.00 - pawnGroundSpeed / TRP->m_fMaxJetpackBoostGroundspeed;
						}
					}
					MyPPc->m_fRemainingInitiatingJettingTime = FMax(0.00, MyPPc->m_fRemainingInitiatingJettingTime - DeltaTime);
					newAccel = Add(newAccel, Scale(Normal(Add(Normal(newAccel),Z)), groundSpeedThrottle));
				}
				WalkingStateProcessMove(MyPPc, DeltaTime, newAccel, 0, Sub(OldRotation, MyPPc->Rotation));
			}
			// End:0xbf6
			else
			{
				MyPPc->GetAxes(MyPPc->Pawn->Rotation, &X, &Y, &Z);
				newAccel = Add(Scale(X, MyPPc->PlayerInput->aForward), Scale(Y, MyPPc->PlayerInput->aStrafe));
				newAccel.Z = 0.00;
				newAccel = Scale(Normal(newAccel), MyPPc->Pawn->AccelRate);
				DoubleClickMove = MyPPc->PlayerInput->CheckForDoubleClickMove(DeltaTime / MyPPc->WorldInfo->TimeDilation);
				OldRotation = MyPPc->Rotation;
				MyPPc->UpdateRotation(DeltaTime);
				MyPPc->bDoubleJump = false;
				// End:0x821 Loop:False
				if(MyPPc->bPressedJump && (MyPPc->Pawn->CannotJumpNow()))
				{
					bSaveJump = true;
					MyPPc->bPressedJump = false;
				}
				// End:0x82d
				else
				{
					bSaveJump = false;
				}
				// End:0x988 Loop:False
				if(MyPPc->Pawn->Physics == 2) //PHYS_Falling
				{
					MaxAccel = MyPPc->Pawn->AccelRate * MyPPc->Pawn->AirControl;
					// End:0x8eb Loop:False
					if(MyPPc->VSizeSq(newAccel) > MaxAccel * MaxAccel)
					{
						newAccel = Normal(newAccel);
						newAccel = Scale(newAccel, MaxAccel);
					}
					Velocity2D = MyPPc->Pawn->Velocity;
					Velocity2D.Z = 0.00;
					// End:0x988 Loop:False
					if(VSize2D(Velocity2D) < MyPPc->Pawn->GroundSpeed && (!MyPPc->m_bEjectedFromVehicle))
					{
						MyPPc->m_bAirSpeedBoundToGroundSpeed = true;
					}
				}
				// End:0xb56 Loop:False
				if(MyPPc->VSizeSq(TRP->Velocity) > TRP->GroundSpeed * TRP->GroundSpeed * 1.10)
				{
					// End:0xa48 Loop:False
					if(TRP->m_fStoppingDistance < TRP->m_fMaxStoppingDistance / float(4))
					{
						MyPPc->m_CurrentDecelerationFactor = 1;
					}
					// End:0xb56
					else
					{
						// End:0xa9e Loop:False
						if(TRP->m_fStoppingDistance < TRP->m_fMaxStoppingDistance / float(2))
						{
							MyPPc->m_CurrentDecelerationFactor = 2;
						}
						// End:0xb56
						else
						{
							// End:0xafa Loop:False
							if(TRP->m_fStoppingDistance < float(3) * TRP->m_fMaxStoppingDistance / float(4))
							{
								MyPPc->m_CurrentDecelerationFactor = 3;
							}
							// End:0xb56
							else
							{
								// End:0xb4a Loop:False
								if(TRP->m_fStoppingDistance < TRP->m_fMaxStoppingDistance)
								{
									MyPPc->m_CurrentDecelerationFactor = 4; //
								}
								// End:0xb56
								else
								{
									MyPPc->m_CurrentDecelerationFactor = 5;
								}
							}
						}
					}
				}

				WalkingStateProcessMove(MyPPc, DeltaTime, newAccel, DoubleClickMove, Sub(OldRotation, MyPPc->Rotation));
				MyPPc->bPressedJump = bSaveJump;
			}
		}
	}
	return true;
}


void ProcessAcceleration (ATrPlayerController *MyPPc, float DeltaTime, struct FVector newAccel)
{
	FVector myvel = { 0, 0, 0 }, Drag; 
	myvel = MyPPc->Pawn->Velocity; //local myvel = Pawn->Velcoity;
		Drag.X = ((myvel.X * myvel.X) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics); 
		Drag.Y = ((myvel.Y * myvel.Y) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics);
		Drag.Z = ((myvel.Z * myvel.Z) / (UUToSanics*MaxDragSpeed*UUToSanics*MaxDragSpeed)) * (DragDeAcceleration*UUToSanics);
		if (myvel.X < 0) Drag.X = -Drag.X; //because the power of two is always possitive
		if (myvel.Y < 0) Drag.Y = -Drag.Y;
		if (myvel.Z < 0) Drag.Z = -Drag.Z;
	newAccel = Add(newAccel, Drag);									//newAccel += Drag;
	MyPPc->Pawn->Velocity = Add(myvel, Scale(newAccel, DeltaTime)); //Pawn.Velocity = myvel + newAccel * DeltaTime;
	MyPPc->Pawn->Physics = PHYS_Flying;								//So UE3 won't mess with us
	MyPPc->Pawn->WorldInfo->DefaultGravityZ = 0;					//So UE3 won't mess with us
	return;
};


void CheckJetPackButton(ATrPlayerController *MyPPc, ATrPawn *TRP) {
		if(MyPPc->m_bPressingJetpackButton && (!MyPPc->m_bPressingJetpack) && (TRP->GetPowerPoolPercent() >= 0.10) && (!MyPPc->eventIsMoveInputIgnored()))
		{
			MyPPc->EnableJetpack(true, MyPPc->m_bJumpJet, 0);
			MyPPc->m_fRemainingInitiatingJettingTime = ((UTrFamilyInfo *) TRP->GetCurrCharClassInfo())->m_fJetpackInitTotalTime;
		}
		else
		{
			if(MyPPc->m_bPressingJetpack && (TRP->GetPowerPoolPercent() <= 0.01 || (MyPPc->eventIsMoveInputIgnored()))) MyPPc->EnableJetpack(false, true, 0);
			else
			{
				if(!MyPPc->m_bPressingJetpackButton && (MyPPc->m_bPressingJetpack)) MyPPc->EnableJetpack(false, true, 0);
			}
		}
}

bool ModMyPlayerMove(float DeltaTime, ATrPlayerController *MyPPc) {
	FVector X, Y, Z, newAccel = { 0, 0, 0 };
	ATrPawn *TRP;
	MyPPc->m_CurrentDecelerationFactor = 0;       //??
	MyPPc->m_bAirSpeedBoundToGroundSpeed = false; //??
	TRP = (ATrPawn *) MyPPc->Pawn;
	if(!TRP) { return false; } //Means I'm dead
	static float CurrentPowerPool = 0;


	CurrentPowerPool = FMin(TRP->r_fMaxPowerPool, CurrentPowerPool + (DeltaTime * EnergyRegenRate));   //Regening
	float CostofJetup = (DeltaTime * UpwardEnergyCostRate);
	float CostOfDirectional = (DeltaTime * DirectionalEnergyCostRate);
	float ExtraCostOfDirectional_And_Jetup = (DeltaTime * DirectionalAndUpwardsExtraCostRate);


	//CheckJetPackButton(MyPPc, TRP);
	bool issking = ((ATrPlayerPawn *) MyPPc->Pawn)->r_bIsSkiing; //Space key pressed?
	MyPPc->GetAxes(MyPPc->Pawn->Rotation, &X, &Y, &Z);             
	if(MyPPc->m_bPressingJetpackButton && CurrentPowerPool >= CostofJetup)                                  //is player pressing jet button? does he have enough energy?
	{
		if ((MyPPc->PlayerInput->aStrafe || MyPPc->PlayerInput->aForward)) { //does he want to starfe?
			newAccel = Add(Scale(X, MyPPc->PlayerInput->aForward), Scale(Y, MyPPc->PlayerInput->aStrafe)); //newAccel = PlayerInput.aForward * X + PlayerInput.aStrafe * Y;
			if (issking && CurrentPowerPool >= (CostOfDirectional + CostofJetup + ExtraCostOfDirectional_And_Jetup)) { //if space key pressed he wants strong directional jets too, does he have energy for both?
				newAccel = Scale(Normal(newAccel), +(UUToSanics*DirectionalJetAcc)); //newAccel = Normal(newAccel) * (UUToSanics*DirectionalJetAcc);   //Directional jets

				CurrentPowerPool -= CostOfDirectional;                //Cost of jetting up and directional
				CurrentPowerPool -= ExtraCostOfDirectional_And_Jetup; //extra cost if needed to run both
			}
			else newAccel = Scale(Normal(newAccel), +(UUToSanics*AirControlAcc)); //newAccel = Normal(newAccel) * (UUToSanics*AirControlAcc);			 //Weak and free directional jets
		}
		CurrentPowerPool= FMax(0.00, CurrentPowerPool - CostofJetup); //Cost of jetting up 
		newAccel.Z += (UUToSanics*UpwardsAcc); //Upwards jet
		TRP->eventUpdateJetpackEffects();
	}
	else
	{
		if ((MyPPc->PlayerInput->aStrafe || MyPPc->PlayerInput->aForward)) { //does he want to starfe?
			newAccel = Add(Scale(X, MyPPc->PlayerInput->aForward), Scale(Y, MyPPc->PlayerInput->aStrafe)); ; //newAccel = PlayerInput.aForward * X + PlayerInput.aStrafe * Y;
			if (issking && CurrentPowerPool >= CostOfDirectional) { //if space key pressed he wants strong directional jets, does he have energy for it?
				newAccel = Scale(Normal(newAccel), +(UUToSanics*DirectionalJetAcc));  //newAccel = Normal(newAccel) * (UUToSanics*DirectionalJetAcc);   //Directional jets
				TRP->eventUpdateJetpackEffects();
				CurrentPowerPool = FMax(0.00, CurrentPowerPool - CostOfDirectional);  //Cost of just directional jets
			}
			else {
				newAccel = Scale(Normal(newAccel), +(UUToSanics*AirControlAcc));  //newAccel = Normal(newAccel) * (UUToSanics*AirControlAcc);			 //Weak and free directional jets
			}
		}
	}

	TRP->m_fCurrentPowerPool = CurrentPowerPool;                  //I overide it with my own because while physics is set to Flying it automaticly drains it
	newAccel.Z += (UUToSanics*GravityAcc);                        //Gravity
	MyPPc->UpdateRotation(DeltaTime);
	ProcessAcceleration(MyPPc, DeltaTime, newAccel);
	
	return true;
}

bool Function_TribesGame_TrPlayerController_PlayerTick_JetPack(hooknum ID, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	//fprintf(mylog, "Function_TribesGame_TrPlayerController_PlayerTick_JetPack\n"); fflush(mylog);
	ATrPlayerController_eventPlayerTick_Parms Tick_Params;
	memcpy(&Tick_Params, pParams, sizeof(ATrPlayerController_eventPlayerTick_Parms));
	float DeltaTime = Tick_Params.DeltaTime;
	ATrPlayerController *MyPPc = (ATrPlayerController *) dwCallingObject;
	if (!MyPPc) return false;

	fprintf(mylog, "Function_TribesGame_TrPlayerController_PlayerTick_JetPack\n"); fflush(mylog);


	// End:0x25 Loop:False
	if(!MyPPc->bShortConnectTimeOut)
	{
		MyPPc->bShortConnectTimeOut = true;
		fprintf(mylog, "1\n"); fflush(mylog);
		MyPPc->ServerShortTimeout();
		fprintf(mylog, "1 end\n"); fflush(mylog);
	}
	// End:0xb8 Loop:False
	if(MyPPc->Pawn != MyPPc->AcknowledgedPawn)
	{
		// End:0xa5 Loop:False
		if(MyPPc->Role < 3)
		{
			// End:0xa5 Loop:False
			if(MyPPc->AcknowledgedPawn && (MyPPc->AcknowledgedPawn->Controller == MyPPc))
			{
				MyPPc->AcknowledgedPawn->Controller = 0;
			}
		}
		fprintf(mylog, "2 \n"); fflush(mylog);
		MyPPc->AcknowledgePossession(MyPPc->Pawn);
		fprintf(mylog, "2 end\n"); fflush(mylog);
	}
	fprintf(mylog, "3 \n"); fflush(mylog);
	MyPPc->PlayerInput->eventPlayerInput(DeltaTime);
	fprintf(mylog, "3 end\n"); fflush(mylog);
	// End:0xf7 Loop:False
	if(MyPPc->bUpdatePosition)
	{
		fprintf(mylog, "4 \n"); fflush(mylog);
		MyPPc->ClientUpdatePosition();
		fprintf(mylog, "4 end\n"); fflush(mylog);
	}
	if (!MyPlayerMove(DeltaTime, MyPPc)) {
		fprintf(mylog, "6 end\n"); fflush(mylog);
		return false;
	}
	fprintf(mylog, "7 \n"); fflush(mylog);
	MyPPc->AdjustFOV(DeltaTime);
	fprintf(mylog, "7 end\n"); fflush(mylog);
	return true; //overide orignal!
}