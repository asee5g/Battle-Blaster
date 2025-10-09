// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "ScreenMessage.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UScreenMessage : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UTextBlock* MessageTextBlock;
public:
	void SetMessageText(FString Message);
};
