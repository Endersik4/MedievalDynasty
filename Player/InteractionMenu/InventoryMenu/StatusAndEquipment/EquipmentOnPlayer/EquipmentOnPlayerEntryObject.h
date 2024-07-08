// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/StatusAndEquipmentWidget.h"
#include "EquipmentOnPlayerEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UEquipmentOnPlayerEntryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	FEquipmentOnPlayer EquipmentOnPlayer;
	UPROPERTY(EditAnywhere)
	bool bOccupied = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInventoryMenuWidget> InventoryMenuWidget = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
