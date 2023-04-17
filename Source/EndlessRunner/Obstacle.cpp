// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/BoxComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh");
	ObstacleMesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(Root);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlapBegin);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	ObstacleLocation = GetActorLocation();

	ObstacleLocation.X -= ObstacleSpeed * DeltaTime;

	SetActorLocation(ObstacleLocation);

	if(ObstacleLocation.X <= DestroyLocation)
	{
		Destroy();
	}
}

void AObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Actor name: %s"), *OtherActor->GetName())
	if(OtherActor)
	{
		Destroy();
	}
	
}

