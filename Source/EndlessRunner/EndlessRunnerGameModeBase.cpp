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
		
		if(LastPlatform)
		{
			NewPlatformSpawn += NextSpawn;
			LastPlatform->SetFolderPath(TEXT("Platforms"));	
		}
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms()
{
	if(GetWorld())
	{
		LastPlatform->SpawnObstacle();
		
		FTransform NewTransform = LastPlatform->GetTransform() + NextSpawn;
		LastPlatform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, NewTransform);
		LastPlatform->SetFolderPath(TEXT("Platforms"));
	}
}

