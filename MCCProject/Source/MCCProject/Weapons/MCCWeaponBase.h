// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "MCCWeaponBase.generated.h"

class AMCCProjectileBase;
class UArrowComponent;
/**
 * 
 */
UCLASS(BlueprintType , Blueprintable , meta = (BlueprintSpawnableComponent))
class MCCPROJECT_API UMCCWeaponBase : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UMCCWeaponBase();

	UPROPERTY(VisibleDefaultsOnly , BlueprintReadWrite , Category = "Weapon")
	UArrowComponent* ArrowComponentFirePoint;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Weapon")
	TSubclassOf<AMCCProjectileBase> ProjectileClass;

	UFUNCTION(BlueprintCallable , Server , Reliable , Category = "Weapon")
	void Server_FireWeapon();

	UFUNCTION(NetMulticast , Reliable)
	void Multi_SpawnProjectile();
};
