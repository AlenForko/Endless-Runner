// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartGame);
	}

	if(ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	}
}

void UMainMenu::StartGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMap"));
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("quit"));
	}
}


