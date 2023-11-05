// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCGSGameplay.h"
#include "MCCPSGameplay.h"


void AMCCGSGameplay::ReceiveKill(APlayerState* Killer, APlayerState* Victim)
{
	for(const auto PlayerStates : PlayerArray)
	{
		if (const auto PSGameplay = Cast<AMCCPSGameplay>(PlayerStates))
		{
			if (Killer && Victim)
			{
				if (Killer != Victim)
				{
					if (PSGameplay ==  Victim)
					{
						PSGameplay->AddPlayerDeathScore(1);
					}
					if (PSGameplay == Killer)
					{
						PSGameplay->AddPlayerKillScore(1);
					}
				}	
			}
		}
	}
	OnReceiveKill.Broadcast( Killer , Victim);
	ForceNetUpdate();
}
