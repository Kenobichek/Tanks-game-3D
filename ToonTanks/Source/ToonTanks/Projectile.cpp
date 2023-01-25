#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	trailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::onHit);
	if (launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
}

void AProjectile::onHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	auto owner = GetOwner();

	if (owner == nullptr)
	{
		Destroy();
		return;
	}

	auto ownerInstigator =  owner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != owner)
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, ownerInstigator, this, damageTypeClass);
		if (hitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticles, GetActorLocation(), GetActorRotation());
		}
		if (hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
		if (hitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
		}
		Destroy();
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
