// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalPlayerChecks.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYSTALCAVERN_API UGlobalPlayerChecks : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlobalPlayerChecks();
	
	UGlobalPlayerChecks* InitComponent(UWorld* & WorldSetter);

	template<class T>
	bool CheckIfPlayer(AActor* HitActor, UWorld* World) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UPROPERTY(VisibleAnywhere, category = "Setup")
	// UWorld* World;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
