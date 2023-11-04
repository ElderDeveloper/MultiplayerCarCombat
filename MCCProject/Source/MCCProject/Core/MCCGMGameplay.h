// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MCCGMGameplay.generated.h"

class AMCCPCGameplay;
class AMCCPSGameplay;
class AMCCGSGameplay;
class APlayerStart;


UCLASS()
class MCCPROJECT_API AMCCGMGameplay : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMCCGMGameplay();
	
	UFUNCTION(BlueprintCallable)
	void ReceiveSpawnPlayer(AMCCPCGameplay* PlayerController);

	UFUNCTION(BlueprintPure)
	bool FindPlayerStartPoint(FTransform& PlayerTransform);

protected:
	
	TArray<APlayerStart*> PlayerStartPoints;

	void FindAllPlayerStartPoints();

	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

};
