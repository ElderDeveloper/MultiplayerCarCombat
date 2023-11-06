// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCPCGameplay.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MCCGMGameplay.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "MCCProject/Player/MCCPlayerPawn.h"
#include "MCCProject/UI/Gameplay/MCCGameplayWidget.h"


AMCCPCGameplay::AMCCPCGameplay()
{
	bShouldHaveRespawnDelay = false;
	RespawnDelay = 0.1f;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	TargetDestination = FVector::ZeroVector;
	InputDownTime = 0.f;
	SetDestinationClickAction = nullptr;
	DefaultMappingContext = nullptr;
	PlayerPawnClass = nullptr;
	FXCursor = nullptr;
	GameplayWidgetClass = nullptr;
	
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
	if (const auto PlayerPawn = Cast<AMCCPlayerPawn>(GetPawn()))
	{
		if (InputDownTime > 0.5)
		{
			PlayerPawn->SetMouseHoldDownPosition(TargetDestination , true);
		}
		else
		{
			PlayerPawn->SetMouseHoldDownPosition(TargetDestination , false);
		}
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
	if (const auto PlayerPawn = Cast<AMCCPlayerPawn>(GetPawn()))
	{
		PlayerPawn->SetMouseHoldDownPosition(TargetDestination , false);
		PlayerPawn->SetTargetAIPath(TargetDestination);
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, TargetDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	InputDownTime = 0.f;
}


void AMCCPCGameplay::OnPlayerDeath(APlayerState* Killer)
{
}

void AMCCPCGameplay::RequestRespawn(float Delay)
{
	if (HasAuthority())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(  TimerHandle , [this]() 
		{
			if (const auto GMGameplay = GetWorld()->GetAuthGameMode<AMCCGMGameplay>())
			{
				GMGameplay->ReceiveSpawnPlayer(this);
			}
		}, Delay, false );
	}
}


void AMCCPCGameplay::RequestRespawnDelay()
{
	if (HasAuthority())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(  TimerHandle , [this]() 
		{
			UE_LOG(LogTemp , Warning , TEXT("Delayed Respawn"));
			RequestRespawn();
		}, RespawnDelay, false );
	}
}


void AMCCPCGameplay::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		if (IsValid(GameplayWidgetClass))
		{
			GameplayWidget = CreateWidget<UMCCGameplayWidget>(this, GameplayWidgetClass);
			if (GameplayWidget)
			{
				GameplayWidget->AddToViewport();
			}
		}
	}
}


void AMCCPCGameplay::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}


void AMCCPCGameplay::OnUnPossess()
{
	Super::OnUnPossess();
	
	if (bShouldHaveRespawnDelay)
	{
		RequestRespawnDelay();
	}
	else
	{
		// Instant respawn causes possess issues.
		RequestRespawn(0.1);
	}
}


void AMCCPCGameplay::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMCCPCGameplay::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMCCPCGameplay::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMCCPCGameplay::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMCCPCGameplay::OnSetDestinationReleased);
	}
}


FName AMCCPCGameplay::GetPlayerDisplayName() const
{
	return *PlayerState->GetPlayerName();
}

