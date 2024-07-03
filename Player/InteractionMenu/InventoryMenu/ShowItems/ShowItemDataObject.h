// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/Inventory/ItemData.h"
#include "ShowItemDataObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UShowItemDataObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 ItemAmount = 0;
	UPROPERTY(EditAnywhere)
	FBaseItemData ItemData;
	UPROPERTY(EditAnywhere)
	FName RowNameToFindItemData = FName();
	
};
