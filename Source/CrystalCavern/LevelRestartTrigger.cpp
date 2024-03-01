// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelRestartTrigger.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelRestartTrigger::ALevelRestartTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ALevelRestartTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelRestartTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelRestartTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (OtherActor == UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.0f, 1.0f, TimeToFade, FLinearColor::Black, false, true);
		GetWorldTimerManager().SetTimer(WaitForFade, this, &ALevelRestartTrigger::ReloadLevel, TimeToFade, false);
	}
}

void ALevelRestartTrigger::ReloadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	GetWorldTimerManager().ClearTimer(WaitForFade);
}

