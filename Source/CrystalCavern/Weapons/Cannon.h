// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/TimelineComponent.h"
#include "CrystalCavern/Projectiles/Projectile.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class CRYSTALCAVERN_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	
	UFUNCTION()
	void ShootingProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CannonShootingCurve;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<AProjectile> Bullet;

private:
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* Cannon;
	UPROPERTY(EditAnywhere, Category="Setup")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY()
	FTimerHandle ShootingDelay;
	UFUNCTION()
	void DelayShooting();
	
	UPROPERTY(EditAnywhere, Category="Setup")
	float DelayBetweenShots = 1.0f;
	UPROPERTY(EditAnywhere, Category="Setup")
	float ProjectileScale = 1.0f;
	
	UPROPERTY()
	FVector StartingCannonLocation;
};
