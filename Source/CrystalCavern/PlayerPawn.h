// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CRYSTALCAVERN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	public:
		// Sets default values for this pawn's properties
		APlayerPawn();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	private:
		void MoveForward(float AxisValue);
		void MoveRight(float AxisValue);
	
		UPROPERTY(EditAnywhere, Category="Setup")
		UStaticMeshComponent* PlayerMesh;
		UPROPERTY(EditAnywhere, Category="Setup")
		USpringArmComponent* CameraSpringArm;
		UPROPERTY(EditAnywhere, Category="Setup")
		UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, Category="Setup")
		float MovementSpeed = 12.0f;
};
