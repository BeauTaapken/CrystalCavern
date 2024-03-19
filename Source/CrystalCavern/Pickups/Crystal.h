// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Crystal.generated.h"

UCLASS()
class CRYSTALCAVERN_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystal();

	UFUNCTION()
	void AttractionProgress(float Value);
	UFUNCTION()
	void ScaleProgress(float Value);
	UFUNCTION()
	void LightIntensityProgress(float Value);

protected:
	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* AttractionCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* ScaleCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* LightIntensityCurve;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UFUNCTION()
	void DestroyCrystal();

	UPROPERTY(EditAnywhere, Category="Setup")
	USphereComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* PyramidTop;
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* PyramidBottom;
	UPROPERTY(EditAnywhere, Category="Setup")
	UPointLightComponent* PointLight;
	UPROPERTY()
	FVector StartingLocation;
	UPROPERTY()
	FVector StartingScale;
	UPROPERTY()
	float StartingIntensity;
};
