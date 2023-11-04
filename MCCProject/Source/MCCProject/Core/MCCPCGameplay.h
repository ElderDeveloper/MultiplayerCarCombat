// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MCCPCGameplay.generated.h"

class AMCCPlayerPawn;
class UNiagaraSystem;
class UUserWidget;
class UInputMappingContext;
class UInputAction;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class MCCPROJECT_API AMCCPCGameplay : public APlayerController
{
	GENERATED_BODY()

public:
	/*
	AMCCPCGameplay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	TSubclassOf<AMCCPlayerPawn> PlayerPawnClass;

	// FX Class that we will spawn when clicking 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UI")
	TSubclassOf<UUserWidget> PlayerScoreboardClass;

	// MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	// Click Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;
	

	UFUNCTION(BlueprintCallable , Category = "Gameplay")
	virtual void RequestRespawn();
	virtual void RequestRespawnDelay();

protected:

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category = "Respawn")
	bool bShouldHaveRespawnDelay;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category = "Respawn")
	float RespawnDelay;


	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	FVector TargetDestination;
	float InputDownTime;
	
	void PlayerCharacterSpawned();

	// Input handlers for SetDestination action.
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetupInputComponent() override;

public:
	
	UFUNCTION(BlueprintPure , Category = "Gameplay")
	FName GetPlayerName() const;

	*/
};
