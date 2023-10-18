// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Controller.h>
#include <GameFramework/SpringArmComponent.h>

#include <UMG/Public/Blueprint/UserWidget.h>

#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>

#include "DemoBatteryGameCharacterTutorial.generated.h"

UCLASS()
class DEMOBATTERYGAME_API ADemoBatteryGameCharacterTutorial : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoBatteryGameCharacterTutorial();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* m_pCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* m_pCameraFollow;

	bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Power;

	UPROPERTY(EditAnywhere)
		float PowerThreshold;	

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerPowerGui;

	UUserWidget* PlayerPowerWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* arg_hitComponent,
			class AActor* arg_otherActor,
			class UPrimitiveComponent* arg_otherComponent,
			int32 arg_otherBodyIndex,
			bool arg_bFromSweep,
			const FHitResult& arg_sweepResult);

	void RestartGame();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float arg_axis);
	void MoveRight(float arg_axis);
};
