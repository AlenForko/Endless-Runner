// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FHighScoreData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	int32 Score;
};

UCLASS()
class ENDLESSRUNNER_API UHighScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	UHighScoreManager();

	UFUNCTION()
    TArray<FHighScoreData> GetHighScores();

	UFUNCTION()
	void AddHighScore(const FHighScoreData& HighScore);

	UFUNCTION()
	void SaveHighScores();

	UFUNCTION()
	void LoadHighScores();
	
private:
	TArray<FHighScoreData> HighScores;
	const FString HighScoreFileName = TEXT("HighScores.sav");
};
