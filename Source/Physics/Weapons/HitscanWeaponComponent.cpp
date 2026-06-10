// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeaponComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PhysicsCharacter.h"
#include "PhysicsWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

void UHitscanWeaponComponent::Fire()
{
	Super::Fire();

    UE_LOG(LogTemp, Warning, TEXT("Shoot"));

    float HitLength = 1000000.f;
    float HitStrength = 1000000.f;

    FHitResult hit{};

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Character);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        hit,
        Character->GetFirstPersonCameraComponent()->GetComponentLocation(), // + MuzzleOffset,
        Character->GetFirstPersonCameraComponent()->GetComponentLocation() + Character->GetFirstPersonCameraComponent()->GetForwardVector() * HitLength,
        ECC_Visibility,
        Params
    );

    DrawDebugLine(
        GetWorld(),
        Character->GetFirstPersonCameraComponent()->GetComponentLocation(), // + MuzzleOffset,
        Character->GetFirstPersonCameraComponent()->GetComponentLocation() + Character->GetFirstPersonCameraComponent()->GetForwardVector() * HitLength,
        FColor::Red,
        false,      
        0.5f,
        0,
        2.0f
    );

    if (bHit && hit.GetComponent()->IsSimulatingPhysics())
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit"));
        hit.GetComponent()->AddImpulse(Character->GetFirstPersonCameraComponent()->GetForwardVector() * HitStrength);
    }
}
