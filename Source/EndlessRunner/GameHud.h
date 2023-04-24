// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PointsCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Lives;
public:
	UFUNCTION()
	void InitializeHud(class AEndlessRunnerGameModeBase* GameMode);

	UFUNCTION()
	void SetCoinsCount(const int32 CoinsCount);

	UFUNCTION()
	void SetLivesCount(const int32 LivesCount);
};
