// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "BattlaeBlasterGameInstance.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Number of Towers : %d"), TowerCount);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank) {
			UE_LOG(LogTemp, Display, TEXT("Game Mode : Failed to find Tank."));
		}
	}

	int32 LoopIndex = 0;
	while (LoopIndex < TowerCount) {
		AActor* TowerActor = Towers[LoopIndex];
		if (TowerActor) {
			ATower* Tower = Cast<ATower>(TowerActor);
			if (Tower && Tank) {
				Tower->Tank = Tank;
				//UE_LOG(LogTemp, Display, TEXT("Tower Name : %s"), *Tower->GetActorNameOrLabel());
			}
		}
		LoopIndex++;
	}

	APlayerController* PlayercController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayercController)
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayercController, ScreeenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}
	}

	CountDownSeconds = CountDownDelay;
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &ABattleBlasterGameMode::OnCountDownTimerTimeOut, 1.0f, true);
}

void ABattleBlasterGameMode::OnCountDownTimerTimeOut()
{
	CountDownSeconds -= 1;
	if (CountDownSeconds > 0)
	{
		//UE_LOG(LogTemp, Display, TEXT("Count Down %d"), CountDownSeconds);
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountDownSeconds));
	}
	else if (CountDownSeconds == 0)
	{
		//UE_LOG(LogTemp, Display, TEXT("Go.."));
		ScreenMessageWidget->SetMessageText("Go..");
		Tank->SetPlayerEnbale(true);
	}
	else {
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		//UE_LOG(LogTemp, Display, TEXT("Clear Timer"));
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{

	bool IsGameOver = false;
	if (DeadActor == Tank)
	{
		//UE_LOG(LogTemp, Display, TEXT("Tank Died, Defeated"));
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else {
		ATower* DeadTower = Cast<ATower>(DeadActor);
		if (DeadTower)
		{
			//UE_LOG(LogTemp, Display, TEXT("A Towewr Died"));
			DeadTower->HandleDestruction();
			TowerCount--;
			if (TowerCount == 0.0f)
			{
				//UE_LOG(LogTemp, Display, TEXT("All tower Died , Victory"));
				IsGameOver = true;
				IsGamevictory = true;
			}
		}
	}
	if (IsGameOver)
	{
		FString GameOverString = IsGamevictory ? "Victory..!" : "Defeted...!";
		//UE_LOG(LogTemp, Display, TEXT("%s"), *GameOverString);
		ScreenMessageWidget->SetMessageText(GameOverString);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout, GameOverdelay, true);
	}
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	//FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UBattlaeBlasterGameInstance* BattlaeBlasterGameINstance = Cast<UBattlaeBlasterGameInstance>(GameInstance);
		if (BattlaeBlasterGameINstance)
		{
			if (IsGamevictory)
			{
				BattlaeBlasterGameINstance->LoadNextLevel();
			}
			else {
				BattlaeBlasterGameINstance->RestartCurrentLevel();
			}
		}
	}
}

