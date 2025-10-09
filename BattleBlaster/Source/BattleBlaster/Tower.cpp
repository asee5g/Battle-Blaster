// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

// Constructor
ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
    Super::BeginPlay();
    FTimerHandle FireTimerHandle;
    GetWorldTimerManager().SetTimer(FireTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tank && Tank->IsAlive && IsInFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATower::CheckFireCondition()
{
    if (Tank && IsInFireRange())
    {
        Fire();
    }
}

bool ATower::IsInFireRange()
{
    bool Result = false;
    if (Tank) {
        float DistanceRange = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        Result = (DistanceRange <= FireRange);
    }
    return Result;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


