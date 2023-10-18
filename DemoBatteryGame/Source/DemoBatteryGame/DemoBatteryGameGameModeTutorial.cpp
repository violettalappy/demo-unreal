// 2023 (c) ViolettaLappy - hoanglongplanner


#include "DemoBatteryGameGameModeTutorial.h"

ADemoBatteryGameGameModeTutorial::ADemoBatteryGameGameModeTutorial() {
	PrimaryActorTick.bCanEverTick = true;	

	SpawnXMin = 0.0f;
	SpawnXMax = 3000.0f;

	SpawnYMin = 0.0f;
	SpawnYMax = 3000.0f;
}

void ADemoBatteryGameGameModeTutorial::BeginPlay() {	
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1, 
			15.0f, 
			FColor::Yellow, 
			TEXT("GameMode started now"));
	}

	FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(
		unusedHandle,
		this,
		&ADemoBatteryGameGameModeTutorial::SpawnPlayerRecharge,
		FMath::RandRange(1, 3),
		true
	);
}

void ADemoBatteryGameGameModeTutorial::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADemoBatteryGameGameModeTutorial::SpawnPlayerRecharge() {

	float randX = FMath::RandRange(SpawnXMin, SpawnXMax);
	float randY = FMath::RandRange(SpawnYMin, SpawnYMax);

	FVector spawnPosition = FVector(randX, randY, SpawnZ);
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(PlayerRecharge, &spawnPosition, &spawnRotation);
}
