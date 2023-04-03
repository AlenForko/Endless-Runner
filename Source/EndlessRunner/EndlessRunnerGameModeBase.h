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

public:
	UFUNCTION()
	void SpawnPlatform();

	UFUNCTION()
	void SpawnNewPlatforms();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	TSubclassOf<class ARunningPlatform> PlatformClass;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	int32 AmountOfTiles = 11;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	FTransform NextSpawn;

	UPROPERTY(EditAnywhere, Category = "New Platforms")
	FTransform NewPlatformSpawn;
	
	ARunningPlatform* Platform;

	UFUNCTION()
	void CreateInitialPlatforms();
};
