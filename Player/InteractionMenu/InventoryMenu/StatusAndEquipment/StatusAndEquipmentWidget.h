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

	//UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	//TObjectPtr<UTileView> EquipmentTileView = nullptr;

	//UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
///	TObjectPtr<UTileView> WeaponShortcutsTileView = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTileView> PlayerStatusTileView = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FStatusEntry> StatusEntries;

	void FillPlayerStatusTileView();

	UPROPERTY(Transient)
	TObjectPtr<class AMedievalPlayer> Player = nullptr;
};
