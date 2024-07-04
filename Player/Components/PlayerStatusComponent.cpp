// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"

#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "MedievalDynasty/Player/Inventory/InventoryComponent.h"

UPlayerStatusComponent::UPlayerStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMedievalPlayer>(GetOwner());
}

void UPlayerStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

double UPlayerStatusComponent::GetStatusValue(EStatusType StatusToGet)
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

float UPlayerStatusComponent::GetStatusMaxValue(EStatusType StatusToGet)
{
	switch (StatusToGet)
	{
	case EST_Health: return MaxHealth; break;
	case EST_Food: return MaxFood; break;
	case EST_Water: return MaxWater; break;
	case EST_Weight: return MaxWeight; break;
	default: return 0.f;
	}
}

void UPlayerStatusComponent::RefreshWeightValue()
{
	if (!IsValid(Player))
		return;

	Weight = 0.0;

	for (const FInitiallInventory& CurrentItem : Player->GetInventoryComponent()->GetInventory())
	{
		FBaseItemData* ItemData = Player->GetInventoryComponent()->GetItemDataFromDataTable(CurrentItem.ItemRowName);
		if (!ItemData)
			continue;

		Weight += ItemData->ItemWeight * CurrentItem.ItemAmount;
	}
}

