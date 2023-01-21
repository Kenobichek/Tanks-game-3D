// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float fireRange = 700.f;

	FTimerHandle fireRateTimerHandle;
	float fireRate = 2.f;
	void checkFireCondition();
	bool inFireRange();
};
