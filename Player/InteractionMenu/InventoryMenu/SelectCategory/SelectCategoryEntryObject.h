// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"
#include "SelectCategoryEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API USelectCategoryEntryObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool bInitallySelectedCategory = false;
	UPROPERTY(EditAnywhere)
	FCategoryInventory CategoryToDivideItems;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInventoryMenuWidget> InventoryMenuWidget = nullptr;
};
