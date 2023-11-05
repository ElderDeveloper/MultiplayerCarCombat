// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MCCProject/Interface/MCCPlayerInterface.h"
#include "MCCPlayerPawn.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MCCPROJECT_API AMCCPlayerPawn : public AWheeledVehiclePawn , public IMCCPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMCCPlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

protected:

	UPROPERTY(BlueprintReadOnly , Replicated , Category = "Player|Attributes")
	float Health = 100.0f;

	UPROPERTY(BlueprintReadOnly , Replicated , Category = "Player|Attributes")
	float MaxHealth = 100.0f;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION(BlueprintPure , Category = "Player|Components")
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	virtual float GetHealth_Implementation() override;
	virtual float GetMaxHealth_Implementation() override;

};
