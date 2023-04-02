// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"
#include "RunningPlatform.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

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
		ARunningPlatform* Platform = World->SpawnActor<ARunningPlatform>(PlatformClass, NextSpawn);

		if(Platform)
		{
			NextSpawn += Platform->NextSpawnPlatform;
		}
	}
}

