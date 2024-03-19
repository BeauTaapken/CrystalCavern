// Fill out your copyright notice in the Description page of Project Settings.


#include "Crystal.h"

#include "Components/PointLightComponent.h"
#include "CrystalCavern/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACrystal::ACrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	PyramidTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PyramidTop"));
	PyramidTop->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PyramidTop->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PyramidBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PyramidBottom"));
	PyramidBottom->AttachToComponent(PyramidTop, FAttachmentTransformRules::KeepRelativeTransform);
	PyramidBottom->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("CrystalLight"));
	PointLight->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	if (AttractionCurve && ScaleCurve &&  LightIntensityCurve)
	{
		FOnTimelineFloatStatic AttractionProgress;
		AttractionProgress.BindUFunction(this, FName("AttractionProgress"));
		CurveTimeline.AddInterpFloat(AttractionCurve, AttractionProgress);
		StartingLocation = GetActorLocation();
		
		FOnTimelineFloatStatic ScaleProgress;
		ScaleProgress.BindUFunction(this, FName("ScaleProgress"));
		CurveTimeline.AddInterpFloat(ScaleCurve, ScaleProgress);
		StartingScale = GetActorScale();
		
		FOnTimelineFloatStatic LightIntensityProgress;
		LightIntensityProgress.BindUFunction(this, FName("LightIntensityProgress"));
		CurveTimeline.AddInterpFloat(LightIntensityCurve, LightIntensityProgress);
		StartingIntensity = PointLight->Intensity;
		
		FOnTimelineEvent TimelineEvent;
		TimelineEvent.BindUFunction(this, FName("DestroyCrystal"));
		CurveTimeline.SetTimelineFinishedFunc(TimelineEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("1 or more of the curves is not set, Crystals can't be picked up!"));
	}
}

void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void ACrystal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (OtherActor == UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())
	{
		CurveTimeline.PlayFromStart();
	}
}

void ACrystal::DestroyCrystal()
{
	this->Destroy();
}

void ACrystal::AttractionProgress(float Value)
{
	const FVector NewLocation = FMath::Lerp(
		StartingLocation,
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation(),
		Value
	);
	SetActorLocation(NewLocation);
}

void ACrystal::ScaleProgress(float Value)
{
	const FVector NewScale = FMath::Lerp(
		StartingScale,
		FVector(0.0f),
		Value
	);
	SetActorScale3D(NewScale);
}

void ACrystal::LightIntensityProgress(float Value)
{
	const float NewIntensity = FMath::Lerp(
		StartingIntensity,
		0.0f,
		Value
	);
	// const float NewIntensity = 0.0f;
	PointLight->SetIntensity(NewIntensity);
}
