// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCPCGameplay.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MCCGMGameplay.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/PlayerState.h"
/*

AMCCPCGameplay::AMCCPCGameplay()
{
	bShouldHaveRespawnDelay = false;
	RespawnDelay = 5.0f;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	TargetDestination = FVector::ZeroVector;
}


void AMCCPCGameplay::OnInputStarted()
{
	StopMovement();
}

void AMCCPCGameplay::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	InputDownTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		TargetDestination = Hit.Location;
	}
	
	// Move towards
	if (GetPawn())
	{
		const FVector WorldDirection = (TargetDestination - GetPawn()->GetActorLocation()).GetSafeNormal();
		GetPawn()->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AMCCPCGameplay::OnSetDestinationReleased()
{
	// If it was a short press
	if (InputDownTime <= 0.5)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TargetDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, TargetDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	InputDownTime = 0.f;
}



void AMCCPCGameplay::RequestRespawn()
{
	if (const auto GMGameplay = GetWorld()->GetAuthGameMode<AMCCGMGameplay>())
	{
		GMGameplay->ReceiveSpawnPlayer(this);
	}
}

void AMCCPCGameplay::RequestRespawnDelay()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(  TimerHandle , [this]() 
	{
		RequestRespawn();
	}, RespawnDelay, false );
}

void AMCCPCGameplay::PlayerCharacterSpawned()
{
}

void AMCCPCGameplay::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	RequestRespawn();
}

void AMCCPCGameplay::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacterSpawned();
}

void AMCCPCGameplay::OnUnPossess()
{
	Super::OnUnPossess();
	RequestRespawn();
}

void AMCCPCGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMCCPCGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMCCPCGameplay::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMCCPCGameplay::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMCCPCGameplay::OnSetDestinationReleased);
	}
}

FName AMCCPCGameplay::GetPlayerName() const
{
	return *PlayerState->GetPlayerName();
}

*/