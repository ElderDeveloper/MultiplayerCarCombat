// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MCCKillNotifyWidget.generated.h"

class UVerticalBox;


UCLASS()
class MCCPROJECT_API UMCCKillNotifyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UVerticalBox* VBKillNotify;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> KillEntryClass;

	UFUNCTION(BlueprintCallable)
	void OnReceiveKillNotify(APlayerState* Killer ,APlayerState* Victim);
	
protected:

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
};
