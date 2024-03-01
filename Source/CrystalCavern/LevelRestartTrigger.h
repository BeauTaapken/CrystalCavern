// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LevelRestartTrigger.generated.h"

UCLASS()
class CRYSTALCAVERN_API ALevelRestartTrigger : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ALevelRestartTrigger();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;
		virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	private:
		void ReloadLevel();
	
		FTimerHandle WaitForFade;
	
		UPROPERTY(EditAnywhere, Category="Setup")
		USceneComponent* DefaultSceneRoot;
		UPROPERTY(EditAnywhere, Category="Setup")
		UBoxComponent* Trigger;
	
		UPROPERTY(EditAnywhere, Category="Setup")
		float TimeToFade = 1.0f;
};
