// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Tank.h"
#include "ScreenMessage.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	ATank* Tank;
	int32 TowerCount;

	bool IsGamevictory = false;

	float GameOverdelay = 3.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreeenMessageClass;

	UScreenMessage* ScreenMessageWidget;

	UPROPERTY(EditAnywhere)
	int32 CountDownDelay = 3;

	int32 CountDownSeconds;

	FTimerHandle CountDownTimerHandle;

	void ActorDied(AActor* DeadActor);

	void OnGameOverTimerTimeout();

	void OnCountDownTimerTimeOut();
	
};
