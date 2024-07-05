// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/StatusAndEquipmentWidget.h"
#include "PlayerStatusObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UPlayerStatusObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FStatusEntry StatusEntry;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
