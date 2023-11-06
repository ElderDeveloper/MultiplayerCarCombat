// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCGSGameplay.h"
#include "MCCPSGameplay.h"


void AMCCGSGameplay::ReceiveKill(APlayerState* Killer, APlayerState* Victim)
{
	UE_LOG(LogTemp , Log , TEXT("AMCCGSGameplay::ReceiveKill %s killed %s") , *Killer->GetPlayerName() , *Victim->GetPlayerName());
	
	if (Killer == nullptr)
	{
		UE_LOG(LogTemp , Error , TEXT("AMCCGSGameplay::ReceiveKill Killer is nullptr"));
	}

	if (Victim == nullptr)
	{
		UE_LOG(LogTemp , Error , TEXT("AMCCGSGameplay::ReceiveKill Victim is nullptr"));
	}

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
	ForceNetUpdate();
	Multi_BroadcastKill(Killer , Victim);
}


void AMCCGSGameplay::Multi_BroadcastKill_Implementation(APlayerState* Killer, APlayerState* Victim)
{
	OnReceiveKill.Broadcast( Killer , Victim);
}
