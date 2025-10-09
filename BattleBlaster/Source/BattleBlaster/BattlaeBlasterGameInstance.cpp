// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlaeBlasterGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBattlaeBlasterGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= LastLevelIndex)
	{
		CurrentLevel = Index;
		FString LeveNameString = FString::Printf(TEXT("Level_%d"), CurrentLevel);
		UGameplayStatics::OpenLevel(GetWorld(),*LeveNameString);
	}
}
void UBattlaeBlasterGameInstance::LoadNextLevel()
{
	if (CurrentLevel < LastLevelIndex)
	{
		ChangeLevel(CurrentLevel + 1);
	}
	else {
		RestartGame();
	}
}
void UBattlaeBlasterGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevel);
}
void UBattlaeBlasterGameInstance::RestartGame()
{
	ChangeLevel(1);
}