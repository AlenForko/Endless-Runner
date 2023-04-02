// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunningPlatform.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunningPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARunningPlatform();
	
	UPROPERTY(EditAnywhere)
	FTransform NextSpawnPlatform;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameModeBase* RunnerGameMode;

	UFUNCTION()
	void OnTriggerBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlatformComponent;

	UPROPERTY(EDitDefaultsOnly)
	class UBoxComponent* BoxTriggerMesh;

	UPROPERTY(EditAnywhere, Category = "Platform Speed")
	float Speed = 150;
	
	FVector CurrentLocation;
};
