#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::onHit);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay!!!"));

}

void AProjectile::onHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	auto owner = GetOwner();
	if (owner == nullptr) return;

	auto ownerInstigator =  owner->GetInstigatorController();

	auto damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != owner)
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, ownerInstigator, this, damageTypeClass);
		Destroy();
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
