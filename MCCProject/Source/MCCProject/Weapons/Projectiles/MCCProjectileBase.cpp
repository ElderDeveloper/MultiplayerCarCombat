// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MCCProject/Player/MCCPlayerPawn.h"


AMCCProjectileBase::AMCCProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollisionComponent"));
	ProjectileCollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	ProjectileCollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = ProjectileCollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	ProjectileMeshComponent->SetGenerateOverlapEvents(false);
	ProjectileMeshComponent->SetNotifyRigidBodyCollision(false);
	ProjectileMeshComponent->SetSimulatePhysics(false);
	ProjectileMeshComponent->SetEnableGravity(false);
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	InitialLifeSpan = 10.f;
	bReplicates = true;

}


void AMCCProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto PlayerPawn = Cast<AMCCPlayerPawn>(OtherActor))
	{
		if (PlayerPawn != GetOwner())
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.f , GetOwner()->GetInstigatorController() , GetOwner() , UDamageType::StaticClass());
			Destroy();
		}
	}
}

void AMCCProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector NewPosition = GetActorLocation() + GetActorForwardVector() * ProjectileSpeed * DeltaTime;
		NewPosition.Z = GetActorLocation().Z;
		SetActorLocation(NewPosition,true);
	}
}

inline void AMCCProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectileCollisionComponent->OnComponentBeginOverlap.AddDynamic(this , &AMCCProjectileBase::OnProjectileBeginOverlap);
}
