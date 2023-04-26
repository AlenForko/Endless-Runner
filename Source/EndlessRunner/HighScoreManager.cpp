// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreManager.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

UHighScoreManager::UHighScoreManager()
{
    LoadHighScores();
}

TArray<FHighScoreData> UHighScoreManager::GetHighScores()
{
    return HighScores;
}

void UHighScoreManager::AddHighScore(const FHighScoreData& HighScore)
{
    HighScores.Add(HighScore);
}

void UHighScoreManager::SaveHighScores()
{
    USaveGame* SaveGameInstance = UGameplayStatics::CreateSaveGameObject(USaveGame::StaticClass());

    // Set the high scores on the save game object
    if (UHighScoreManager* HighScoreSaveGameInstance = Cast<UHighScoreManager>(SaveGameInstance))
    {
        HighScoreSaveGameInstance->HighScores = HighScores;
    }

    // Save the game to the specified file name
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, HighScoreFileName, 0);
}

void UHighScoreManager::LoadHighScores()
{
    const auto SavedData = Cast<UHighScoreManager>(UGameplayStatics::LoadGameFromSlot(HighScoreFileName, 0));
    if (SavedData)
    {
        HighScores = SavedData->HighScores;
    }
}


