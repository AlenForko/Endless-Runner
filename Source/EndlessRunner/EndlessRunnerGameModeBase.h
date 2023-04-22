// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 * 
 */
class UUserWidget;
class ARunningPlatform;

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	AEndlessRunnerGameModeBase();
	
public:
	UFUNCTION()
	void SpawnNewPlatforms();

	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> ObjectsInScene;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<ARunningPlatform> PlatformClass;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	int32 AmountOfTiles = 11;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	FTransform NextSpawn;

	UPROPERTY(EditAnywhere, Category = "New Platforms")
	FTransform NewPlatformSpawn;
	
	ARunningPlatform* LastPlatform;

	UFUNCTION()
	void CreateInitialPlatforms();

	UFUNCTION()
	void SpawnPlatform();

	void MoveObjects(TArray<AActor*> Actors, float DeltaTime);

	float DestroyLocation = -1000.f;
	
	float Speed = 500.f;
};
