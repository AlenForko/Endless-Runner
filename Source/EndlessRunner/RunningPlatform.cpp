// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlatform.h"
#include "Coins.h"
#include "EndlessRunnerGameModeBase.h"
#include "Obstacle.h"
#include "Runner.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

class ACoins;
// Sets default values
ARunningPlatform::ARunningPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PlatformComponent = CreateDefaultSubobject<UStaticMeshComponent>("Platform Component");
	PlatformComponent->SetupAttachment(Root);

	MiddleLane = CreateDefaultSubobject<UArrowComponent>("Middle Lane");
	MiddleLane->SetupAttachment(Root);

	RightLane = CreateDefaultSubobject<UArrowComponent>("Right Lane");
	RightLane->SetupAttachment(Root);

	LeftLane = CreateDefaultSubobject<UArrowComponent>("Left Lane");
	LeftLane->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARunningPlatform::BeginPlay()
{
	Super::BeginPlay();

	RunnerGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(RunnerGameMode);
}

// Called every frame
void ARunningPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// CurrentLocation = GetActorLocation();
	//
	// CurrentLocation.X -= Speed * DeltaTime;
	// SetActorLocation(CurrentLocation);
	//
	// if(CurrentLocation.X <= DestroyPosition)
	// {
	// 	RunnerGameMode->SpawnNewPlatforms();
	// 	Destroy();
	// }
}

void ARunningPlatform::SpawnObject()
{
	if(ObstacleClass)
	{
		SpawnLaneObstacles(MiddleLane);
		SpawnLaneObstacles(RightLane);
		SpawnLaneObstacles(LeftLane);
	}
}

void ARunningPlatform::SpawnLaneObstacles(const UArrowComponent* Lane) const
{
	const float RandomValue = FMath::RandRange(0, 1);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if(UKismetMathLibrary::InRange_FloatFloat(RandomValue,
		0.5,
		1,
		true,
		true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleClass, SpawnLocation, SpawnParameters);
		RunnerGameMode->ObjectsInScene.Add(Obstacle);
	}
	else
	{
	    ACoins* Coins = GetWorld()->SpawnActor<ACoins>(CoinsClass, SpawnLocation, SpawnParameters);
		RunnerGameMode->ObjectsInScene.Add(Coins);
	}
}


