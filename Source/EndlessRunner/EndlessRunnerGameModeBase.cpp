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
		Platform = World->SpawnActor<ARunningPlatform>(PlatformClass, NewPlatformSpawn);
		
		if(Platform)
		{
			NewPlatformSpawn += NextSpawn;
			Platform->SetFolderPath(TEXT("Platforms"));
			
		}
		
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms()
{
	if(GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("OLD Platform pos: %f"), Platform->GetActorLocation().X);
		Platform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, Platform->GetTransform() + NextSpawn);
		Platform->SetFolderPath(TEXT("Platforms"));
		UE_LOG(LogTemp, Warning, TEXT("NEW Platform pos: %f"), Platform->GetActorLocation().X);
	}
}

