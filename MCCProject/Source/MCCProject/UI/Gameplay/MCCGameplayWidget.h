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
	
	UFUNCTION(BlueprintCallable)
	void UpdateScoreboard();

protected:
	
	UPROPERTY()
	TArray<UTextBlock*> PlayerScoreboardTexts;

	UPROPERTY()
	AGameStateBase* GameState;

 	UFUNCTION()
	void BindGameStateDelegates();

	UFUNCTION()
	void OnReceiveKillNotify(APlayerState* Killer ,APlayerState* Victim);
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

