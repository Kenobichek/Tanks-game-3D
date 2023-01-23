// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksGameMode::actorDied(AActor* deadActor)
{
	if (deadActor == tank)
	{
		APlayerController* tankController = tank->getAPlayerController();

		if (tankController)
		{
			tank->DisableInput(tankController);
			tankController->bShowMouseCursor = false;
			tank->handleDestruction();
		}
	}
	else if (ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->handleDestruction();
	}
}

