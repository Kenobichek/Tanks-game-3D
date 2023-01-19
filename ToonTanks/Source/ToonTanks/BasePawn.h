// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables of the tank", meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleCompon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables of the tank", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables of the tank", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables of the tank", meta = (AllowPrivateAccess = "true"));
	USceneComponent* ProjectileSpawnPoint;

};