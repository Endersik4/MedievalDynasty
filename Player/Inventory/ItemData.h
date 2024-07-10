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
	EIT_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum EEquipmentType
{
	EET_None UMETA(DisplayName = "None"),
	EET_ChestWear UMETA(DisplayName = "Chest Wear"),
	EET_HeadWear UMETA(DisplayName = "Head Wear"),
	EET_ArmWear UMETA(DisplayName = "Arm Wear"),
	EET_LegWear UMETA(DisplayName = "Leg Wear"),
	EET_FootWear UMETA(DisplayName = "Foot Wear"),
	EET_Torch UMETA(DisplayName = "Torch"),
	EET_Arrows UMETA(DisplayName = "Arrows"),
};

UENUM(BlueprintType)
enum EStatusType
{
	EST_Health UMETA(DisplayName = "Health"),
	EST_Energy UMETA(DisplayName = "Energy"),
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

UENUM(BlueprintType)
enum EMathOperation
{
	EMO_Add UMETA(DisplayName = "Add"),
	EMO_Substract UMETA(DisplayName = "Substract"),
	EMO_Multiply UMETA(DisplayName = "Multiply"),
	EMO_Divide UMETA(DisplayName = "Divide"),
};

USTRUCT(BlueprintType)
struct FEatEffectsAction
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText EatEffectDisplayName = FText();
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMathOperation> MathOperation = EMO_Add;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EStatusType> StatusToBeAffected = EST_Food;
	UPROPERTY(EditAnywhere)
	double ValueForMathOperation = 0.f;
};

UENUM(BlueprintType)
enum EDurabilityType
{
	EDT_Uses UMETA(DisplayName = "Uses"),
	EDT_DestroyOverTime UMETA(DisplayName = "Destroy Over Time"),
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
	FText ItemTypeText = FText();
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDurabilityType> DurabilityType = EDT_Uses;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> ItemIcon = nullptr;
	UPROPERTY(EditAnywhere)
	float ItemDurability = 0.f;
	UPROPERTY(EditAnywhere)
	float ItemInitallDurability = 0.f;
	UPROPERTY(EditAnywhere)
	double ItemWeight = 0.f;
	UPROPERTY(EditAnywhere)
	float ItemPrice = 0.f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APickableItem> PickableItemClass;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "ItemType == EItemType::EIT_Food", EditConditionHides))
	TArray<FEatEffectsAction> EatActions;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ItemType == EItemType::EIT_Tools || ItemType == EItemType::EIT_Cloth", EditConditionHides))
	TEnumAsByte<EEquipmentType> EquipmentType = EET_None;
	 
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
