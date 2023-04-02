// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"
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
		Platform = World->SpawnActor<ARunningPlatform>(PlatformClass, NextSpawn);
		
		if(Platform)
		{
			NextSpawn += Platform->NextSpawnPlatform;
			Platform->SetFolderPath(TEXT("Platforms"));
		}
	}
}
