// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MCCPSGameplay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerScoreChanged);

UCLASS()
class MCCPROJECT_API AMCCPSGameplay : public APlayerState
{
	GENERATED_BODY()

public:
	AMCCPSGameplay();
	
	UPROPERTY( BlueprintAssignable , Category = "Delegate")
	FOnPlayerScoreChanged OnPlayerKillScoreChanged;

	UPROPERTY( BlueprintAssignable , Category = "Delegate")
	FOnPlayerScoreChanged OnPlayerDeathScoreChanged;
	

	UFUNCTION(BlueprintCallable , Category = "Score")
	void AddPlayerKillScore(int32 ScorePoint);

	UFUNCTION(BlueprintCallable , Category = "Score")
	void AddPlayerDeathScore(int32 ScorePoint);

protected:

	UPROPERTY(Replicated)
	int32 PlayerKillScore;

	UPROPERTY(Replicated)
	int32 PlayerDeathScore;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UFUNCTION(BlueprintPure , Category = "Score")
	FORCEINLINE int32 GetPlayerKillScore() const { return PlayerKillScore; }

	UFUNCTION(BlueprintPure , Category = "Score")
	FORCEINLINE int32 GetPlayerDeathScore() const { return PlayerDeathScore; }
};
