// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARunningPlatform> PlatformClass;

	UPROPERTY()
	int32 AmountOfTiles = 10;

	UPROPERTY(EditDefaultsOnly)
	FTransform NextSpawn;

	UFUNCTION()
	void SpawnPlatform();
};
