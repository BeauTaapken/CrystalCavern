// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalPlayerChecks.h"


// Sets default values for this component's properties
UGlobalPlayerChecks::UGlobalPlayerChecks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UGlobalPlayerChecks* UGlobalPlayerChecks::InitComponent(UWorld*& WorldSetter)
{
	// this->World = WorldSetter;
	return this;
}

template<class T>
bool UGlobalPlayerChecks::CheckIfPlayer(AActor* HitActor, UWorld* World) const
{
	if (World)
	{
		return HitActor == World->GetFirstPlayerController()->GetPawn();
	}
	return false;
}

// Called when the game starts
void UGlobalPlayerChecks::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGlobalPlayerChecks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

