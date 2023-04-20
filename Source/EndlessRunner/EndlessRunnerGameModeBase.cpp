// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "Obstacle.h"
#include "RunningPlatform.h"
#include "Kismet/GameplayStatics.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialPlatforms();
}

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::CreateInitialPlatforms()
{
	for (int i = 0; i < AmountOfTiles; ++i)
	{
		SpawnPlatform();
	}
}

void AEndlessRunnerGameModeBase::SpawnPlatform()
{
	UWorld* World = GetWorld();
	
	if(World)
	{
		LastPlatform = World->SpawnActor<ARunningPlatform>(PlatformClass, NewPlatformSpawn);
		ObjectsInScene.Add(LastPlatform);
		
		if(LastPlatform)
		{
			NewPlatformSpawn += NextSpawn;
			LastPlatform->SetFolderPath(TEXT("Platforms"));	
		}
	}
}

void AEndlessRunnerGameModeBase::MoveObjects(TArray<AActor*> Actors, float DeltaTime)
{
	for (auto Object : Actors)
	{
			
		FVector ObjectLocation = Object->GetActorLocation();

		ObjectLocation.X -= Speed * DeltaTime;
		Object->SetActorLocation(ObjectLocation);

		if(ObjectLocation.X <= DestroyLocation)
		{
			SpawnNewPlatforms();
			ObjectsInScene.Remove(Object);
			Object->Destroy();
		}
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms()
{
	if(GetWorld())
	{
		LastPlatform->SpawnObject();
		
		FTransform NewTransform = LastPlatform->GetTransform() + NextSpawn;
		LastPlatform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, NewTransform);
		LastPlatform->SetFolderPath(TEXT("Platforms/Obstacles"));
		ObjectsInScene.Add(LastPlatform);
	}
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveObjects(ObjectsInScene, DeltaTime);
}

