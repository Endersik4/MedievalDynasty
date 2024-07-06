// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MedievalDynasty/Player/Components/PlayerStatusComponent.h"
#include "StatusAndEquipmentWidget.generated.h"

UENUM(BlueprintType)
enum EStatusValueType
{
	ESVT_Max UMETA(DisplayName = "Max Value"),
	ESVT_Percent UMETA(DisplayName = "Percent"),
	ESVT_Temperature UMETA(DisplayName = "Temperature"),
};

USTRUCT(BlueprintType)
struct FStatusEntry
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> StatusIconTexture = nullptr;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EStatusType> StatusType = EST_Food;
	UPROPERTY(EditAnywhere)
	FProgressBarStyle StatusProgressBarStyle = FProgressBarStyle();
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EStatusValueType> StatusValueType = ESVT_Max;
	UPROPERTY(EditAnywhere)
	FText StatusEntryDisplayName = FText();
};

USTRUCT(BlueprintType)
struct FQuickToolSelectEntry
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	int32 QuickAttackNum = 0;
};

USTRUCT(BlueprintType)
struct FEquipmentOnPlayer
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FButtonStyle EquipmentButtonStyle = FButtonStyle();
};


class UWrapBox;
class UTextBlock;
class UTileView;
class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UStatusAndEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
		
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> ShortcutsTextWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ShortcutsTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> PlayerStatusTextWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerStatusTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> PlayerNameAndAgeTextWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameAndAgeTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTileView> EquipmentTileView = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> RenderedPlayerImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTileView> WeaponShortcutsTileView = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTileView> PlayerStatusTileView = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Status Settings")
	FText AgeText = FText();
	UPROPERTY(EditDefaultsOnly, Category = "Status Settings")
	TArray<FStatusEntry> StatusEntries;
	UPROPERTY(EditDefaultsOnly, Category = "Quick Weapon Select Settings")
	TArray<FQuickToolSelectEntry> QuickSelectEntries;
	UPROPERTY(EditDefaultsOnly, Category = "Equipment Settings")
	TArray<FEquipmentOnPlayer> AllEquipmentsOnPlayer;
	UPROPERTY(EditDefaultsOnly, Category = "Equipment Settings")
	TSubclassOf<class ARenderOnlyPlayerActor> RenderOnlyPlayerActorClass = nullptr;

	void FillPlayerStatusTileView();
	void FillWeaponShortcutsTileView();
	void FillEquipmentTileView();

	void RenderPlayerInWidget();

	UPROPERTY(Transient)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<ARenderOnlyPlayerActor> SpawnedRenderOnlyPlayer = nullptr;
};
