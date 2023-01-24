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

	startGame();

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

int AToonTanksGameMode::getTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(
		this,
		ATower::StaticClass(),
		Towers
	);

	return Towers.Num();
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
		gameOver(false);
	}
	else if (ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->handleDestruction();
		if (getTargetTowerCount() == 0)
		{
			gameOver(true);
		}
	}
}

