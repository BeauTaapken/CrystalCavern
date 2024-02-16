// Fill out your copyright notice in the Description page of Project Settings.


#include "Crystal.h"


// Sets default values
ACrystal::ACrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TODO this is the spot i'm gonna have to add all needed items
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	PyramidTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PyramidTop"));
	PyramidTop->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PyramidBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PyramidBottom"));
	PyramidBottom->AttachToComponent(PyramidTop, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

