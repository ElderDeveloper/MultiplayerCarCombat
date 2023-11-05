// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MCCGSGameplay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReceiveKill , APlayerState* , Killer , APlayerState* , Victim);

UCLASS()
class MCCPROJECT_API AMCCGSGameplay : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable , Category = "Gameplay")
	FOnReceiveKill OnReceiveKill;
	
	UFUNCTION(BlueprintCallable ,  Category = "Gameplay")
	virtual void ReceiveKill(APlayerState* Killer ,  APlayerState* Victim);
};
