// Fill out your copyright notice in the Description page of Project Settings.


#include "MCCWeaponBase.h"

#include "Components/ArrowComponent.h"
#include "Projectiles/MCCProjectileBase.h"

UMCCWeaponBase::UMCCWeaponBase()
{
	ArrowComponentFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponentFirePoint"));
	SetIsReplicatedByDefault(true);
}

void UMCCWeaponBase::Server_FireWeapon_Implementation()
{
	Multi_SpawnProjectile();
}

void UMCCWeaponBase::Multi_SpawnProjectile_Implementation()
{
	if(IsValid(ProjectileClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.Instigator = GetOwner()->GetInstigator();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AMCCProjectileBase* Projectile = GetWorld()->SpawnActor<AMCCProjectileBase>(ProjectileClass , ArrowComponentFirePoint->GetComponentLocation() , ArrowComponentFirePoint->GetComponentRotation() , SpawnParameters);
	}
}
