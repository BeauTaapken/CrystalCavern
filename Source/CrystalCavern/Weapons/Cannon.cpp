// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalCavern/Weapons/Cannon.h"

#include "CrystalCavern/Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);	

	Cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	Cannon->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->AttachToComponent(Cannon, FAttachmentTransformRules::KeepRelativeTransform);
}



// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	if (CannonShootingCurve)
	{
		FOnTimelineFloatStatic ShootingProgress;
		ShootingProgress.BindUFunction(this, FName("ShootingProgress"));
		CurveTimeline.AddInterpFloat(CannonShootingCurve, ShootingProgress);
		StartingCannonLocation = Cannon->GetRelativeLocation();
		
		FOnTimelineEvent TimelineEvent;
		TimelineEvent.BindUFunction(this, FName("DestroyCrystal"));
		CurveTimeline.SetTimelineFinishedFunc(TimelineEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("1 or more of the curves is not set, Crystals can't be picked up!"));
	}
	GetWorldTimerManager().SetTimer(ShootingDelay, this, &ACannon::DelayShooting, DelayBetweenShots, true);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void ACannon::DelayShooting()
{
	if (!Bullet)
	{
		UE_LOG(LogTemp, Error, TEXT("Bullet has not been specified"));
		return;
	}
	// This should be done with a pool, can't be arsed to set it all up though, so I won't for this because it's just some practice
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(Bullet, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetActorScale3D(FVector(ProjectileScale));
	CurveTimeline.PlayFromStart();
}

void ACannon::ShootingProgress(float Value)
{
	Cannon->SetRelativeLocation(FVector(0.0f, Value, 0.0f));

}

