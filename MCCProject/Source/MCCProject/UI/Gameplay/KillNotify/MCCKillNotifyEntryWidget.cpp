// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCKillNotifyEntryWidget.h"
#include "Components/TextBlock.h"
#include "MCCProject/Core/MCCPSGameplay.h"


void UMCCKillNotifyEntryWidget::SetupWidget(APlayerState* Killer, APlayerState* Victim)
{
	if (TextKiller && TextVictim && Killer && Victim)
	{
		StoredVictim = Victim;
		if (const auto PSKiller = Cast<AMCCPSGameplay>(Killer))
		{
			TextKiller->SetText(FText::FromString(Killer->GetPlayerName()));
		}
		if (const auto PSVictim = Cast<AMCCPSGameplay>(Victim))
		{
			TextVictim->SetText(FText::FromString(Victim->GetPlayerName()));
		}
		
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle,this,&UMCCKillNotifyEntryWidget::DestroyKillEntry,LifeTime,false);
	}
	else
	{
		RemoveFromParent();
	}
}
