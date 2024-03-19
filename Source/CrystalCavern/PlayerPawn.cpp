// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SetRootComponent(PlayerMesh);
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->AttachToComponent(PlayerMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.0f, 0.0f, 3.0f, FLinearColor::Black);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent was not set on PlayerPawn!"));
		return;
	}
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
}

float APlayerPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (!TakingDamage)
	{
		TakingDamage = true;
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.0f, 1.0f, TimeToFade, FLinearColor::Black, false, true);
		GetWorldTimerManager().SetTimer(WaitForFade, this, &APlayerPawn::ReloadLevel, TimeToFade, false);
	}
	
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void APlayerPawn::ReloadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	GetWorldTimerManager().ClearTimer(WaitForFade);
}

void APlayerPawn::MoveForward(float AxisValue)
{
	if (PlayerMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerMesh was not set on PlayerPawn!"));
		return;
	}

	FVector Torque = FVector(0.0f, MovementSpeed*AxisValue, 0.0f);
	PlayerMesh->AddTorqueInRadians(Torque, NAME_None, true);
}

void APlayerPawn::MoveRight(float AxisValue)
{
	if (PlayerMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerMesh was not set on PlayerPawn!"));
		return;
	}

	FVector Torque = FVector(MovementSpeed*AxisValue, 0.0f, 0.0f);
	PlayerMesh->AddTorqueInRadians(Torque, NAME_None, true);
}

