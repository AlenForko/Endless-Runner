// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "GameHud.h"
#include "Obstacle.h"
#include "RunningPlatform.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartTime = GetWorld()->GetRealTimeSeconds();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud) // Checks if the HUD is there, otherwise crash game.

	GameHud->InitializeHud(this);
	GameHud->AddToViewport();
	
	CreateInitialPlatforms();

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEndlessRunnerGameModeBase::SpawnNewPlatforms, SpawnDelay, true);
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Speed += 0.01f;
	
	MoveObjects(ObjectsInScene, DeltaTime, Speed);
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

void AEndlessRunnerGameModeBase::AddToPoints()
{
	TotalPoints += 1;

	OnCoinsCountChanged.Broadcast(TotalPoints);
}

void AEndlessRunnerGameModeBase::MoveObjects(TArray<AActor*> &Actors, float DeltaTime, float ObjectSpeed)
{
	for (auto Object : Actors)
	{
		FVector ObjectLocation = Object->GetActorLocation();

		ObjectLocation.X -= ObjectSpeed * DeltaTime;
		
		Object->SetActorLocation(ObjectLocation);
		
		if(ObjectLocation.X <= DestroyLocation)
		{
			ObjectsInScene.Remove(Object);
			Object->Destroy();
		}
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms()
{
	if(GetWorld())
	{
		if(!LastPlatform) return;
		
		LastPlatform->SpawnObject();
		
		FTransform NewTransform = LastPlatform->GetTransform() + NextSpawn;
		LastPlatform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, NewTransform);
		LastPlatform->SetFolderPath(TEXT("Platforms/Obstacles"));
		ObjectsInScene.Add(LastPlatform);
	}
}



