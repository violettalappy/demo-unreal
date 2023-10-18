// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoBatteryGameCharacterTutorial.h"

// Sets default values
ADemoBatteryGameCharacterTutorial::ADemoBatteryGameCharacterTutorial() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//Using this, will change movement direction based on mouse pos
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//This line allow yaw rotation based on movement input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	m_pCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_pCameraBoom->SetupAttachment(RootComponent);

	m_pCameraBoom->TargetArmLength = 300.0f;
	m_pCameraBoom->bUsePawnControlRotation = true;

	m_pCameraFollow = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFollow"));
	m_pCameraFollow->SetupAttachment(m_pCameraBoom, USpringArmComponent::SocketName);
	m_pCameraFollow->bUsePawnControlRotation = false;

	Power = 100.0f;
	PowerThreshold = 10.0f;
}

// Called when the game starts or when spawned
void ADemoBatteryGameCharacterTutorial::BeginPlay() {
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADemoBatteryGameCharacterTutorial::OnBeginOverlap);

	if (PlayerPowerGui != nullptr) {
		PlayerPowerWidget = CreateWidget(GetWorld(), PlayerPowerGui);
		PlayerPowerWidget->AddToViewport();
	}
}

// Called every frame
void ADemoBatteryGameCharacterTutorial::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Power -= DeltaTime * PowerThreshold;

	if (Power <= 0.0f) {
		if (!isDead) {
			isDead = true;

			GetMesh()->SetSimulatePhysics(true);

			FTimerHandle unusedHandle;

			GetWorldTimerManager().SetTimer(
				unusedHandle,
				this,
				&ADemoBatteryGameCharacterTutorial::RestartGame,
				3.0f,
				false);

		}
	}
}

void ADemoBatteryGameCharacterTutorial::OnBeginOverlap(
	UPrimitiveComponent* arg_hitComponent,
	AActor* arg_otherActor,
	UPrimitiveComponent* arg_otherComponent,
	int32 arg_otherBodyIndex,
	bool arg_bFromSweep,
	const FHitResult& arg_sweepResult) {

	if (arg_otherActor->ActorHasTag("Recharge")) {

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Blue,
				TEXT("Collided with "));

			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Yellow,
				FString::Printf(TEXT("Collided with %s !!"), *arg_otherActor->GetName()));
		}

		//UE_LOG(LogTemp, Warning, TEXT("Collided With"));

		Power += 20.0f;

		if (Power > 100.0f) {
			Power = 100.0f;
		}

		arg_otherActor->Destroy();
	}
}

void ADemoBatteryGameCharacterTutorial::RestartGame() {

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}


// Called to bind functionality to input
void ADemoBatteryGameCharacterTutorial::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADemoBatteryGameCharacterTutorial::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoBatteryGameCharacterTutorial::MoveRight);
}

void ADemoBatteryGameCharacterTutorial::MoveForward(float arg_axis) {

	if (!isDead) {
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, arg_axis);
	}

}

void ADemoBatteryGameCharacterTutorial::MoveRight(float arg_axis) {

	if (!isDead) {
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, arg_axis);
	}

}

