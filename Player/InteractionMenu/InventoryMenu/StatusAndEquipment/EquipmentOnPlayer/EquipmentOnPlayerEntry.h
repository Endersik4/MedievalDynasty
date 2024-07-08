// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "EquipmentOnPlayerEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UEquipmentOnPlayerEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	void HighlightEquipment(bool bHighlight = true);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> EquipmentOnPlayerButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> EquipmentIconImage = nullptr;

	UFUNCTION()
	void OnHovered_EquipmentPlayerButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment On Player Settings")
	FButtonStyle OccupiedEquipmentButtonStyle = FButtonStyle();
	UPROPERTY(EditDefaultsOnly, Category = "Equipment On Player Settings")
	FButtonStyle HighlightedOccupiedEquipmentButtonStyle = FButtonStyle();

	UPROPERTY(Transient)
	TObjectPtr<class UEquipmentOnPlayerEntryObject> EquipmentOnPlayerEntryObject = nullptr;
};
