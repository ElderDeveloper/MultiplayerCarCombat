// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MCCProjectileBase.generated.h"

class USphereComponent;

UCLASS()
class MCCPROJECT_API AMCCProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
											int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);
	AMCCProjectileBase();

	UPROPERTY(VisibleDefaultsOnly , BlueprintReadWrite , Category = "Projectile")
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly , BlueprintReadWrite , Category = "Projectile")
	USphereComponent* ProjectileCollisionComponent;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Projectile")
	float ProjectileSpeed = 1000.f;
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};

