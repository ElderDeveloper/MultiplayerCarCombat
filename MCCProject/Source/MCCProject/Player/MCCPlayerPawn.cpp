// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCPlayerPawn.h"

#include "ChaosVehicleMovementComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MCCProject/Core/MCCGSGameplay.h"
#include "Net/UnrealNetwork.h"


class AMCCGSGameplay;

AMCCPlayerPawn::AMCCPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// We do not attach it to the root component because we want it to be able to move freely
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}



void AMCCPlayerPawn::SetTargetAIPath(FVector Location)
{
	if (const auto NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		// Check if a valid path was found
		if (const auto NavPath = NavigationSystem->FindPathToLocationSynchronously(GetWorld() , GetActorLocation() , Location , GetController()))
		{
			// Get the path points
			const TArray<FNavPathPoint>& PathPoints = NavPath->GetPath()->GetPathPoints();
			
			SplineComponent->ClearSplinePoints();
			for (const auto i : PathPoints)
			{
				SplineComponent->AddSplinePoint(i.Location , ESplineCoordinateSpace::World);
			}
			SplineComponent->UpdateSpline();
			bHasPath = true;
		}
		else
		{
			bHasPath = false;
			UE_LOG(LogTemp, Warning, TEXT("No valid path found."));
		}
	}
}



void AMCCPlayerPawn::SetMouseHoldDownPosition(FVector Location, bool bIsHoldDown)
{
	MouseHoldDownPosition = Location;
	bIsMouseHoldDown = bIsHoldDown;
	bHasPath = false;
}



void AMCCPlayerPawn::BreakAIControl()
{
	bHasPath = false;
	bIsMouseHoldDown = false;
}



void AMCCPlayerPawn::OnTakeAnyDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType,AController* InstigatedBy, AActor* DamageCauser)
{
	if (HasAuthority())
	{
		if (const auto GSGameplay = GetWorld()->GetGameState<AMCCGSGameplay>())
		{
			GSGameplay->ReceiveKill(InstigatedBy->PlayerState , GetController()->PlayerState);
		}
		Destroy();
	}
}



void AMCCPlayerPawn::CheckIsPossessed()
{
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer( Handle , [this]()
	{
		if (!GetController())
		{
			Destroy();
		}
	} , 0.1f , false);
}



void AMCCPlayerPawn::GetPath(float& Steering)
{
	if (SplineComponent)
	{
		const FVector ClosestPoint = SplineComponent->FindTangentClosestToWorldLocation(GetActorLocation() , ESplineCoordinateSpace::World).GetSafeNormal();
		FVector Forward = ClosestPoint * 500.f + GetActorLocation();
		const FVector TargetLocation = SplineComponent->FindTangentClosestToWorldLocation(ClosestPoint, ESplineCoordinateSpace::World);
		const FRotator Rotation = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(TargetLocation , GetActorLocation()) , GetActorRotation());
		Steering = UKismetMathLibrary::MapRangeClamped(Rotation.Yaw , -90.f , 90.f , 1.f , -1.f);

		const FVector LastLocation = SplineComponent->GetWorldLocationAtDistanceAlongSpline(SplineComponent->GetSplineLength());
		if (UKismetMathLibrary::EqualEqual_VectorVector(GetActorLocation() ,LastLocation , 50.f ))
		{
			bHasPath = false;
		}
	}
}



void AMCCPlayerPawn::GetSteeringAndThrottleToLocation(float& Steering, float& Throttle) const
{
	const FRotator Rotation = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(MouseHoldDownPosition , GetActorLocation()) , GetActorRotation());
	if (Rotation.Yaw > -90.f && Rotation.Yaw < 90.f)
	{
		Steering = UKismetMathLibrary::MapRangeClamped(Rotation.Yaw , -180.f , 180.f , 2.f , -2.f);
		Throttle = -1.f;
	}
	else
	{
		Steering = UKismetMathLibrary::MapRangeClamped(Rotation.Yaw , -90.f , 90.f , 1.f , -1.f);
		Throttle = 1.f;
	}
}



void AMCCPlayerPawn::ApplyVehicleMovement(float DeltaTime)
{
	float Steering = 0.f;
	float Throttle = 0.f;
	
	if (bIsMouseHoldDown)
	{
		GetSteeringAndThrottleToLocation(Steering , Throttle);
		if (Throttle < 0.f)
		{
			GetVehicleMovementComponent()->SetThrottleInput(0);
			GetVehicleMovementComponent()->SetBrakeInput(1);
		}
		else
		{
			GetVehicleMovementComponent()->SetThrottleInput(Throttle);
			GetVehicleMovementComponent()->SetBrakeInput(0);
		}
		
		GetVehicleMovementComponent()->SetSteeringInput(Steering);
	}
	else
	{
		if (bHasPath)
		{
			GetPath(Steering);
			GetVehicleMovementComponent()->SetThrottleInput(1);
			GetVehicleMovementComponent()->SetSteeringInput(Steering);
		}
		else
		{
			GetVehicleMovementComponent()->SetThrottleInput(0);
			GetVehicleMovementComponent()->SetSteeringInput(0);
		}
	}
}



void AMCCPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AMCCPlayerPawn::OnTakeAnyDamageHandler);
	CheckIsPossessed();
}



void AMCCPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ApplyVehicleMovement(DeltaTime);
}
