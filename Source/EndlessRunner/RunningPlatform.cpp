// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlatform.h"

#include "EndlessRunnerGameModeBase.h"
#include "Runner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunningPlatform::ARunningPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PlatformComponent = CreateDefaultSubobject<UStaticMeshComponent>("Platform Component");
	PlatformComponent->SetupAttachment(Root);
	
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
	
	CurrentLocation = GetActorLocation();
	
	CurrentLocation.X -= Speed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if(CurrentLocation.X <= DestroyPosition)
	{
		RunnerGameMode->SpawnNewPlatforms(CurrentLocation.X);
		Destroy();
	}
}


