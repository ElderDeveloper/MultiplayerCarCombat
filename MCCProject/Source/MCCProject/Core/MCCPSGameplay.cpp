// Fill out your copyright notice in the Description page of Project Settings.


#include "MCCPSGameplay.h"

#include "Net/UnrealNetwork.h"

AMCCPSGameplay::AMCCPSGameplay()
{
	PlayerKillScore = 0;
	PlayerDeathScore = 0;
}

void AMCCPSGameplay::AddPlayerKillScore(int32 ScorePoint)
{
	PlayerKillScore += ScorePoint;
	ForceNetUpdate();
}

void AMCCPSGameplay::AddPlayerDeathScore(int32 ScorePoint)
{
	PlayerDeathScore += ScorePoint;
	ForceNetUpdate();
}


void AMCCPSGameplay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMCCPSGameplay, PlayerKillScore);
	DOREPLIFETIME(AMCCPSGameplay , PlayerDeathScore);
}
