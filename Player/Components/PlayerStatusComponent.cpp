// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"

UPlayerStatusComponent::UPlayerStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UPlayerStatusComponent::GetStatusValue(EStatusType StatusToGet)
{
	switch (StatusToGet)
	{
	case EST_Health: return Health; break;
	case EST_Food: return Food; break;
	case EST_Water: return Water; break;
	case EST_Weight: return Weight; break;
	case EST_Money: return Money; break;
	case EST_Poison: return Poison; break;
	case EST_Intoxication: return Intoxication; break;
	case EST_TemperatureTolerance: return TemperatureTolerance; break;
	case EST_ProtectionFromCold: return ProtectionFromCold; break;
	case EST_ProtectionFromHeat: return ProtectionFromHeat; break;
	case EST_Dirtiness: return Dirtiness; break;
	default: return 0.f;
	}
}

