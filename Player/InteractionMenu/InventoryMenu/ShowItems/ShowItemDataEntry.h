// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "ShowItemDataEntry.generated.h"

class UTextBlock;
UCLASS()
class MEDIEVALDYNASTY_API UShowItemDataEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void DeselectShowItemEntry();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float Delta) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> SelectItemButton = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> ItemMovingIconImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemAmountTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDurabilityTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemWeightTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPriceTextBlock = nullptr;

	UFUNCTION()
	void OnPressed_SelectItemButton();
	UFUNCTION()
	void OnReleased_SelectItemButton();
	UFUNCTION()
	void OnHovered_SelectItemButton();
	UFUNCTION()
	void OnUnhovered_SelectItemButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Show Item Data Settings")
	FSlateColor OnHoveredFontColor = FSlateColor();
	UPROPERTY(EditDefaultsOnly, Category = "Show Item Data Settings")
	FButtonStyle ItemSelectedButtonStyle = FButtonStyle();
	// When player presses Item Button then save Cursor Position and after moving 
	UPROPERTY(EditDefaultsOnly, Category = "Moving Item Icon Settings")
	float CursorDistanceToStartMovingItem = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Moving Item Icon Settings")
	float MoveItemIconToCursorTime = 0.13f;

	void UpdateItemDisplayInformations();

	void ChangeFontColorToAllTextes(const FSlateColor& NewColor);

	UPROPERTY(Transient)
	TObjectPtr<class UShowItemDataObject> ShowItemDataObject = nullptr;

	bool CheckIfCanStartMovingItem();
	UPROPERTY(Transient)
	bool bCanStartMovingItem = false;
	UPROPERTY(Transient)
	FVector2D CursorLocationWhenPressed = FVector2D(0.f);

	void MovingItemIcon(const FGeometry& MyGeometry, float Delta);
	UPROPERTY(Transient)
	bool bMovingItemIcon = false;
	UPROPERTY(Transient)
	bool bIgnoreSmoothItemMoving = false;
	UPROPERTY(Transient)
	FVector2D OriginalMovingItemImagePosition = FVector2D(0.f);
	UPROPERTY(Transient)
	float MoveItemIconToCursorTimeElapsed = 0.f;

	UPROPERTY(Transient)
	FSlateColor OriginalTextColor = FSlateColor();
	UPROPERTY(Transient)
	FButtonStyle OriginalSelectItemButtonStyle = FButtonStyle();
};
