#include "RadialPhysicsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Weapons/PhysicsWeaponComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/OverlapResult.h"

void ARadialPhysicsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    const FVector ExplosionLocation = Hit.ImpactPoint;

    // Daño en área
    UGameplayStatics::ApplyRadialDamageWithFalloff(
        this,
        25.f, // Daño máximo
        5.f, // Daño mínimo
        ExplosionLocation, // Centro de la explosión
        100.f, // Radio de daño mínimo
        500.f, // Radio de daño máximo
        1.f, // Falloff
        DamageType, // Tipo de daño
        {}, // Actores ignorados
        this, // Damage Causer
        GetInstigatorController() // Instigador
    );

    // Fuerza física en área
    if (UWorld* World = GetWorld())
    {
        TArray<FOverlapResult> Overlaps;

        FCollisionShape Sphere = FCollisionShape::MakeSphere(500.f);

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);

        World->OverlapMultiByChannel(
            Overlaps,
            ExplosionLocation,
            FQuat::Identity,
            ECC_PhysicsBody,
            Sphere,
            QueryParams
        );

        for (const FOverlapResult& Overlap : Overlaps)
        {
            UPrimitiveComponent* Component = Overlap.GetComponent();

            if (!Component || !Component->IsSimulatingPhysics())
                continue;

            Component->AddRadialImpulse(
                ExplosionLocation,
                500.f, // Radio
                1000.f, // Fuerza
                ERadialImpulseFalloff::RIF_Linear,
                true // bVelChange
            );
        }
    }

    Destroy();
}
