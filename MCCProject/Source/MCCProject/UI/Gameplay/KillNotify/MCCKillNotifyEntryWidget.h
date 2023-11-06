// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MCCKillNotifyEntryWidget.generated.h"

class UTextBlock;


UCLASS()
class MCCPROJECT_API UMCCKillNotifyEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupWidget(APlayerState* Killer ,APlayerState* Victim);

	// Implement this function to play destroy animation
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyKillEntry();

protected:

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* TextKiller;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* TextVictim;

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 4;
	
	FTimerHandle DestroyTimeHandle;
	
};
