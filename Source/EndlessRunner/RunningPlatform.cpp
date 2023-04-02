// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlatform.h"

#include "EndlessRunnerGameModeBase.h"
#include "Runner.h"
#include "Components/BoxComponent.h"
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

	BoxTriggerMesh = CreateDefaultSubobject<UBoxComponent>("Box Trigger");
	BoxTriggerMesh->SetupAttachment(PlatformComponent);
	BoxTriggerMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	
}

// Called when the game starts or when spawned
void ARunningPlatform::BeginPlay()
{
	Super::BeginPlay();

	RunnerGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(RunnerGameMode);
	
	BoxTriggerMesh->OnComponentBeginOverlap.AddDynamic(this, &ARunningPlatform::OnTriggerBoxOverlap);
}

// Called every frame
void ARunningPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentLocation = GetActorLocation();
	
	CurrentLocation.X -= Speed * DeltaTime;
	SetActorLocation(CurrentLocation);
}

void ARunningPlatform::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunner* Runner = Cast<ARunner>(OtherActor);
	
	if(Runner)
	{
		RunnerGameMode->SpawnPlatform();
	}
}


