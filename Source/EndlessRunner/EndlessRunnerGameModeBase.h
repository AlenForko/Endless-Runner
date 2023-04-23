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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, PointsCount);
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	AEndlessRunnerGameModeBase();

	FTimerHandle SpawnTimer;

	
public:
	UFUNCTION()
	void SpawnNewPlatforms();

	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> ObjectsInScene;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UFUNCTION()
	void AddToPoints();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<ARunningPlatform> PlatformClass;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	int32 AmountOfTiles = 11;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	FTransform NextSpawn;
	
	FTransform NewPlatformSpawn;
	
	ARunningPlatform* LastPlatform;

	UFUNCTION()
	void CreateInitialPlatforms();

	UFUNCTION()
	void SpawnPlatform();

	void MoveObjects(TArray<AActor*>& Actors, float DeltaTime, float ObjectSpeed);

	float DestroyLocation = -1000.f;
	
	float Speed = 600.f;
	
	float SpawnDelay = 0.5f;
	
	int32 TotalPoints;

	
};
