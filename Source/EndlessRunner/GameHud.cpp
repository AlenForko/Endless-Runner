// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"

#include "EndlessRunnerGameModeBase.h"
#include "Components/TextBlock.h"

void UGameHud::InitializeHud(AEndlessRunnerGameModeBase* GameMode)
{
	if(GameMode)
	{
		PointsCount->SetText(FText::AsNumber(0));

		GameMode->OnCoinsCountChanged.AddDynamic(this, &UGameHud::SetCoinsCount);
	}
}

void UGameHud::SetCoinsCount(const int32 CoinsCount)
{
	 PointsCount->SetText(FText::AsNumber(CoinsCount));
}