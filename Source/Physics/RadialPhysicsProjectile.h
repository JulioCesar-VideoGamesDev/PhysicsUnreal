// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsProjectile.h"
#include "RadialPhysicsProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICS_API ARadialPhysicsProjectile : public APhysicsProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};
