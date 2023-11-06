// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MCCPlayerPawn.generated.h"


class USplineComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MCCPROJECT_API AMCCPlayerPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMCCPlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	USplineComponent* SplineComponent;

	UFUNCTION( BlueprintCallable , Category = "AI")
	void SetTargetAIPath(FVector Location);

	UFUNCTION( BlueprintCallable , Category = "AI")
	void SetMouseHoldDownPosition(FVector Location , bool bIsHoldDown);

	UFUNCTION( BlueprintCallable , Category = "AI")
	void BreakAIControl();
	
protected:

	bool bHasPath = false;
	bool bIsMouseHoldDown = false;
	FVector MouseHoldDownPosition;
	
	UFUNCTION()
	void OnTakeAnyDamageHandler(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	void CheckIsPossessed();

	UFUNCTION()
	void ApplyVehicleMovement(float DeltaTime);

	UFUNCTION(BlueprintPure)
	void GetPath(float& Steering);

	UFUNCTION(BlueprintPure)
	void GetSteeringAndThrottleToLocation(float& Steering , float& Throttle) const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE USplineComponent* GetSplineComponent() const { return SplineComponent; }

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE bool HasPath() const { return bHasPath; }

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE bool IsMouseHoldDown() const { return bIsMouseHoldDown; }
};
