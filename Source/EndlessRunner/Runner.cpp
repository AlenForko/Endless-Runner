// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MoveForward();

	
}

// Called to bind functionality to input
void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Right", this, &ARunner::MoveRight);
}

void ARunner::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
	
}

void ARunner::MoveForward()
{
	// FVector Velocity = GetMovementComponent()->Velocity;
	//
	// Velocity.X = GetMovementComponent()->GetMaxSpeed();
	//
	// GetMovementComponent()->Velocity = Velocity;
}


