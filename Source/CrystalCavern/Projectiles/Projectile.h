// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
// #include "CrystalCavern/PlayerChecks.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class CRYSTALCAVERN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

private:
	UPROPERTY(EditAnywhere, Category="Setup")
	USphereComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* Projectile;
	UPROPERTY(EditAnywhere, Category="Setup")
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(EditAnywhere, Category="Setup")
	float ProjectileDamage = 1.0f;
	
	// UPROPERTY(EditAnywhere, Category="Setup")
	// APlayerChecks* PlayerChecks;
};
