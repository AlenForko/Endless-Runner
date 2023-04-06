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
		LastPlatform = World->SpawnActor<ARunningPlatform>(PlatformClass, NewPlatformSpawn);
		
		if(LastPlatform)
		{
			NewPlatformSpawn += NextSpawn;
			LastPlatform->SetFolderPath(TEXT("Platforms"));	
		}
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms(float XPosition)
{
	if(GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("OLD Platform pos: %f"), LastPlatform->GetActorLocation().X);
		
		FTransform NewTransform = LastPlatform->GetTransform() + NextSpawn;
		//FVector NewLocation = NewTransform.GetLocation();
		//NewLocation.X = XPosition + NextSpawn.GetLocation().X;
		//NewTransform.SetLocation(NewLocation);
		LastPlatform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, NewTransform);
		LastPlatform->SetFolderPath(TEXT("Platforms"));
		
		UE_LOG(LogTemp, Warning, TEXT("NEW Platform pos: %f"), LastPlatform->GetActorLocation().X);
	}
}

