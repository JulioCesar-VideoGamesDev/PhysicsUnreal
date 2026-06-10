// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileWeaponComponent.h"
#include "PhysicsCharacter.h"
#include "PhysicsProjectile.h"
#include "Camera/CameraComponent.h"

void UProjectileWeaponComponent::Fire()
{
	Super::Fire();

    UE_LOG(LogTemp, Warning, TEXT("ShootProjectile"));

    float HitLength = 1000000.f;
    float HitStrength = 1000000.f;

    FHitResult hit{};

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Character);

    if (m_ProjectileClass)
    {
        FVector SpawnLocation = GetOwner()->GetActorLocation() + FireOffset->GetComponentLocation();
        FRotator SpawnRotation = Character->GetFirstPersonCameraComponent()->GetComponentRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = Character;

        APhysicsProjectile* Projectile = GetWorld()->SpawnActor<APhysicsProjectile>(
            m_ProjectileClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
        );

        //Projectile->GetProjectileMovement()->
    }
}
