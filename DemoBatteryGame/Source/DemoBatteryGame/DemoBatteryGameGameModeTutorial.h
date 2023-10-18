// 2023 (c) ViolettaLappy - hoanglongplanner

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include <GameFramework/Actor.h>

#include "DemoBatteryGameGameModeTutorial.generated.h"

/**
 *
 */
UCLASS()
class DEMOBATTERYGAME_API ADemoBatteryGameGameModeTutorial : public AGameModeBase {
	GENERATED_BODY()

public:
	ADemoBatteryGameGameModeTutorial();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> PlayerRecharge;

	float SpawnZ = 500.0f;

	UPROPERTY(EditAnywhere)
		float SpawnXMin;

	UPROPERTY(EditAnywhere)
		float SpawnXMax;

	UPROPERTY(EditAnywhere)
		float SpawnYMin;

	UPROPERTY(EditAnywhere)
		float SpawnYMax;

	void SpawnPlayerRecharge();

};
