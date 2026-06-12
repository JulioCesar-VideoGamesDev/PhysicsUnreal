// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileWeaponComponent.h"
#include "PhysicsCharacter.h"
#include "PhysicsProjectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UProjectileWeaponComponent::Fire()
{
	Super::Fire();

    UE_LOG(LogTemp, Warning, TEXT("ShootProjectile"));

	// Calculate impact location
	FVector rayStart{ Character->FirstPersonCameraComponent->GetComponentLocation() };
	FVector rayDir{ Character->FirstPersonCameraComponent->GetForwardVector() };
	FVector rayEnd{ rayStart + rayDir * 1000000 };

	FVector bulletSpawn{ GetComponentLocation() + GetComponentRotation().RotateVector(MuzzleOffset) };
	FVector bulletEnd{ rayEnd };

	FHitResult hit{};
	FCollisionQueryParams queryParams{};
	queryParams.AddIgnoredActor(GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(hit, rayStart, rayEnd, ECC_Visibility, queryParams))
	{
		bulletEnd = hit.ImpactPoint;
	}

	// Spawn projectile
	FActorSpawnParameters spawnParams{};
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	APhysicsProjectile* projectile = GetWorld()->SpawnActor<APhysicsProjectile>(m_ProjectileClass, FTransform(bulletSpawn), spawnParams);
	if (projectile)
	{
		projectile->m_OwnerWeapon = this;

		FVector projectileDir = (bulletEnd - bulletSpawn).GetSafeNormal();
		projectile->DamageType = DamageType;
		projectile->GetProjectileMovement()->Velocity = projectileDir * projectile->GetProjectileMovement()->InitialSpeed;
	}
}
