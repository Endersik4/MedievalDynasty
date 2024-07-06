// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatusComponent.generated.h"


UENUM(BlueprintType)
enum EStatusType
{
	EST_Health UMETA(DisplayName = "Health"),
	EST_Food UMETA(DisplayName = "Food"),
	EST_Water UMETA(DisplayName = "Water"),
	EST_Weight UMETA(DisplayName = "Weight"),
	EST_Money UMETA(DisplayName = "Money"),
	EST_Poison UMETA(DisplayName = "Poison"),
	EST_Intoxication UMETA(DisplayName = "Intoxication"),
	EST_TemperatureTolerance UMETA(DisplayName = "Temperature Tolerance"),
	EST_ProtectionFromCold UMETA(DisplayName = "Protection From Cold"),
	EST_ProtectionFromHeat UMETA(DisplayName = "Protection From Heat"),
	EST_Dirtiness UMETA(DisplayName = "Dirtiness"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MEDIEVALDYNASTY_API UPlayerStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	double GetStatusValue(EStatusType StatusToGet);
	float GetStatusMaxValue(EStatusType StatusToGet);
	const FFloatRange& GetTemperatureToleranceRange() const { return TemperatureToleranceRange; }
	
	void RefreshWeightValue();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player Status")
	float MaxHealth = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Status")
	float MaxFood = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Status")
	float MaxWater = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Status")
	float MaxWeight = 35.f;
	UPROPERTY(EditDefaultsOnly, Category = "Player Status")
	FFloatRange TemperatureToleranceRange = FFloatRange(0.f, 40.f);

	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Health = 100.0;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Food = 88.8;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Water = 52.4;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Weight = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	float Money = 50.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float Poison = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float Intoxication = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	float TemperatureTolerance = 20.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float ProtectionFromCold = 0.06f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float ProtectionFromHeat = 0.18f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float Dirtiness = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
