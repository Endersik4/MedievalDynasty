// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	EIT_Tools UMETA(DisplayName = "Tools"),
	EIT_Cloth UMETA(DisplayName = "Cloth"),
	EIT_Food UMETA(DisplayName = "Food"),
	EIT_Crafts UMETA(DisplayName = "Crafts"),
	EIT_Miscellaneous UMETA(DisplayName = "Miscellaneous"),
	EIT_Campign UMETA(DisplayName = "Campign"),
};

USTRUCT(BlueprintType)
struct FBaseItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	int32 ItemID = 0;
	UPROPERTY(EditAnywhere)
	FText ItemDisplayText = FText();
	UPROPERTY(EditAnywhere, meta = (MultiLine = "true"))
	FText ItemDisplayDescription = FText();
	UPROPERTY(EditAnywhere)
	FText ItemStorageName = FText();
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> ItemType = EIT_Miscellaneous;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> ItemIcon = nullptr;
	UPROPERTY(EditAnywhere, meta = (ClampMax = "100.0", ClampMin = "0.0", UIMin = "0.0", UIMax = "100.0"))
	float ItemDurability = 0.f;
	UPROPERTY(EditAnywhere)
	float ItemWeight = 0.f;
	UPROPERTY(EditAnywhere)
	float ItemPrice = 0.f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APickableItem> PickableItemClass;
	 
	const bool operator==(const EItemType& OtherItemType) const
	{
		return ItemType == OtherItemType;
	}
	const bool operator==(const int32& OtherItemID) const
	{
		return ItemID == OtherItemID;
	}
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	int32 ItemAmount = 0;
	UPROPERTY(EditAnywhere)
	FBaseItemData ItemData = FBaseItemData();

	FInventoryItem()
	{
		ItemAmount = 0;
		ItemData = FBaseItemData();
	}

	FInventoryItem(int32 NewItemAmount, FBaseItemData _NewItemData)
	{
		ItemAmount = NewItemAmount;
		ItemData = _NewItemData;
	}
};

UCLASS()
class MEDIEVALDYNASTY_API UItemData : public UObject
{
	GENERATED_BODY()


	
};
