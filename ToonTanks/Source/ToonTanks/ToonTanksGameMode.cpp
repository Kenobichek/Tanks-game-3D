// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	handleGameStart();
}

void AToonTanksGameMode::handleGameStart()
{
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (toonTanksPlayerController)
	{
		toonTanksPlayerController->setPlayerEnabledState(false);
		
		FTimerHandle playerEnableTimerHandle;
		FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			toonTanksPlayerController,
			&AToonTanksPlayerController::setPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			playerEnableTimerHandle,
			playerEnableTimerDelegate,
			startDelay,
			false
		);
	}
}

void AToonTanksGameMode::actorDied(AActor* deadActor)
{
	if (deadActor == tank)
	{
		tank->handleDestruction();

		if (toonTanksPlayerController)
		{
			toonTanksPlayerController->setPlayerEnabledState(false);
		}
	}
	else if (ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->handleDestruction();
	}
}

