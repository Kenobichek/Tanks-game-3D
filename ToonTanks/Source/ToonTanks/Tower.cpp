// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::checkFireCondition, fireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (inFireRange())
	{
		rotateTurret(Tank->GetActorLocation());
	}
}

void ATower::handleDestruction()
{
	Super::handleDestruction();
	Destroy();
}

void ATower::checkFireCondition()
{
	if (inFireRange() && Tank->checkIsAlive())
	{
		fire();
	}
}

bool ATower::inFireRange()
{
	if (Tank)
	{
		float distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		return fireRange >= distance;

	}

	return false;
}
