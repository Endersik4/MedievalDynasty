// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "QuickSelectEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UQuickSelectEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> QuickSelectButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ToolIconImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuickSelectNumberText = nullptr;

	UFUNCTION()
	void OnPressed_QuickSelectButton();
	UFUNCTION()
	void OnReleased_QuickSelectButton();
	UFUNCTION()
	void OnHovered_QuickSelectButton();
	UFUNCTION()
	void OnUnhovered_QuickSelectButton();

	UFUNCTION()
	void ItemFoundNewSlot();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Quick Select Settings")
	TEnumAsByte<EItemType> CanEquipOnlyItemType = EIT_Tools;

	UPROPERTY(Transient)
	TObjectPtr<class UQuickSelectEntryObject> QuickSelectEntryObject = nullptr;
};
