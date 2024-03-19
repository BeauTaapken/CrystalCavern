// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalPlayerChecks.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WinTrigger.generated.h"

UCLASS()
class CRYSTALCAVERN_API AWinTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinTrigger();

	virtual void BeginPlay() override;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:	
	UPROPERTY(EditAnywhere, Category="Setup")
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere, Category="Setup")
	UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere, Category="Setup")
	TArray<FName> LevelNames;

	UFUNCTION(BlueprintPure)
	bool AnyCrystalsRemaining() const;

	UFUNCTION()
	void CompleteLevel();
	
	UFUNCTION(BlueprintPure)
	int GetCurrentLevelIndex() const;
};
