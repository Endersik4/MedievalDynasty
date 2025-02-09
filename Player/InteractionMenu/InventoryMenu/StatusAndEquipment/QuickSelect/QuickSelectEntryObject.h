// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/StatusAndEquipmentWidget.h"

#include "QuickSelectEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UQuickSelectEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FQuickToolSelectEntry QuickSelectEntry;
	UPROPERTY(EditAnywhere)
	FBaseItemData ItemInQuickSelect;
	UPROPERTY(EditAnywhere)
	bool bQuickSelectOccupied = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInventoryMenuWidget> InventoryMenuWidget = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
