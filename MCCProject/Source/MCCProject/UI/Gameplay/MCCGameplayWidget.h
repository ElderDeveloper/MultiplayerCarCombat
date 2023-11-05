// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MCCGameplayWidget.generated.h"


class UProgressBar;
class UTextBlock;
class UVerticalBox;
class UMCCAttributeBar;
class UMCCKillNotifyWidget;

UCLASS()
class MCCPROJECT_API UMCCGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BindWidget))
	UMCCKillNotifyWidget* KillNotifyWidget;
	
	UPROPERTY(BlueprintReadOnly , EditAnywhere , meta = (BindWidget))
	UVerticalBox* VBPlayerScoreboard;

	UPROPERTY(BlueprintReadOnly , EditAnywhere , meta = (BindWidget))
	UProgressBar* ProgressBarHealth;

	UFUNCTION(BlueprintCallable)
	void UpdateScoreboard();

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float CurrentHealth , float MaxHealth);

protected:
	
	UPROPERTY()
	TArray<UTextBlock*> PlayerScoreboardTexts;

 	UFUNCTION()
	void BindOnPlayerKillNotify();

	UFUNCTION()
	void OnReceiveKillNotify(APlayerState* Killer ,APlayerState* Victim);
	
	virtual void NativeConstruct() override;
};
