// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/TextBlock.h"

void UGameHud::InitializeHud(AEndlessRunnerGameModeBase* GameMode)
{
	if(GameMode)
	{
		PointsCount->SetText(FText::FromString("Score: 0"));
		Lives->SetText(FText::FromString("Lives: 3"));

		GameMode->OnCoinsCountChanged.AddDynamic(this, &UGameHud::SetCoinsCount);
		GameMode->OnLivesCountChanged.AddDynamic(this, &UGameHud::SetLivesCount);
	}
}

void UGameHud::SetCoinsCount(const int32 CoinsCount)
{
	FString Score = "Score: ";
	Score.AppendInt(CoinsCount);
	
	PointsCount->SetText(FText::FromString(Score));
}

void UGameHud::SetLivesCount(const int32 LivesCount)
{
	FString Life = "Lives: ";
	Life.AppendInt(LivesCount);
	
	Lives->SetText(FText::FromString(Life));
}
