// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MedievalDynasty/Player/Inventory/ItemData.h"
#include "PlayerStatusComponent.generated.h"




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
	FORCEINLINE const FFloatRange& GetTemperatureToleranceRange() const { return TemperatureToleranceRange; }
	
	void RefreshWeightValue();
	void RefreshMoneyValue();

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
	double Energy = 100.0;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Food = 88.8;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Water = 52.4;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double Weight = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status|Money")
	double Money = 50.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status|Money")
	FName MoneyRowNameInDataAsset = FName(TEXT("CoinItem"));
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	double Poison = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	double Intoxication = 0.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status")
	double TemperatureTolerance = 20.f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	double ProtectionFromCold = 0.06f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	double ProtectionFromHeat = 0.18f;
	UPROPERTY(Transient, EditDefaultsOnly, Category = "Player Status", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	double Dirtiness = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
