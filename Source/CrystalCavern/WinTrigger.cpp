// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"

#include "Kismet/GameplayStatics.h"
#include "Pickups/Crystal.h"


// Sets default values
AWinTrigger::AWinTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();
	// UGlobalPlayerChecks test = UGlobalPlayerChecks;
	// GlobalPlayerChecks = UGlobalPlayerChecks::InitComponent(GetWorld());
}

void AWinTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Would be a lot better if we can make it so a "blueprint macro" like thing is used here, idk how though
	if (OtherActor == UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn() && AnyCrystalsRemaining())
	{
		CompleteLevel();
	}
}

bool AWinTrigger::AnyCrystalsRemaining() const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrystal::StaticClass(), FoundActors);
	return FoundActors.Num() <= 0;
}

void AWinTrigger::CompleteLevel()
{
	int CurrentLevelIndex = GetCurrentLevelIndex();
	if (CurrentLevelIndex < LevelNames.Num())
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelNames[CurrentLevelIndex++]);
		return;
	}
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}

int AWinTrigger::GetCurrentLevelIndex() const
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
	return LevelNames.Find(CurrentLevelName);
}
