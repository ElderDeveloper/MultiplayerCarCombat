// Fill out your copyright notice in the Description page of Project Settings.


#include "MCCGMGameplay.h"

#include "MCCGSGameplay.h"
#include "MCCPSGameplay.h"
#include "MCCPCGameplay.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MCCProject/Player/MCCPlayerPawn.h"


AMCCGMGameplay::AMCCGMGameplay()
{
	PrimaryActorTick.bCanEverTick = true;
	GameStateClass = AMCCGSGameplay::StaticClass();
	PlayerStateClass = AMCCPSGameplay::StaticClass();
	PlayerControllerClass = AMCCPCGameplay::StaticClass();
}


void AMCCGMGameplay::ReceiveSpawnPlayer(AMCCPCGameplay* PlayerController)
{
	FTransform SpawnTransform;
	if (FindPlayerStartPoint(SpawnTransform) && PlayerController)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Owner = PlayerController;
		SpawnTransform.SetScale3D(FVector(1.f));

		if(const auto SpawnedCharacter = GetWorld()->SpawnActor<AMCCPlayerPawn>(PlayerController->PlayerPawnClass , SpawnTransform , SpawnParameters))
		{
			PlayerController->Possess(SpawnedCharacter);
		}
		else
		{
			UKismetSystemLibrary::PrintString( GetWorld() , FString::Printf(TEXT("Spawn Player Not Spawned")) , true , true , FLinearColor::Red , 5.f);
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString( GetWorld() , FString::Printf(TEXT("Spawn Location Not Found")) , true , true , FLinearColor::Red , 5.f);
	}
}


bool AMCCGMGameplay::FindPlayerStartPoint(FTransform& PlayerTransform)
{
	if(PlayerStartPoints.IsValidIndex(0))
	{
		const int32 RandomIndex = FMath::RandRange(0 ,PlayerStartPoints.Num()-1);
		if (PlayerStartPoints.IsValidIndex(RandomIndex))
		{
			PlayerTransform = PlayerStartPoints[RandomIndex]->GetActorTransform();
			return true;
		}
	}
	return false;
}


void AMCCGMGameplay::FindAllPlayerStartPoints()
{
	PlayerStartPoints.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
		{
			PlayerStartPoints.Add(PlayerStart);
		}
	}
}


void AMCCGMGameplay::BeginPlay()
{
	Super::BeginPlay();
	FindAllPlayerStartPoints();
}


void AMCCGMGameplay::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	if (const auto PCGameplay = Cast<AMCCPCGameplay>(NewPlayer))
	{
		PCGameplay->RequestRespawnDelay();
	}
}


void AMCCGMGameplay::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

