// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/ShowItems/ShowItemDataEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "ShowItemDataObject.h"
#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/InventoryMenuWidget.h"

void UShowItemDataEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectItemButton->OnPressed.AddDynamic(this, &UShowItemDataEntry::OnPressed_SelectItemButton);
	SelectItemButton->OnReleased.AddDynamic(this, &UShowItemDataEntry::OnReleased_SelectItemButton);
	SelectItemButton->OnHovered.AddDynamic(this, &UShowItemDataEntry::OnHovered_SelectItemButton);
	SelectItemButton->OnUnhovered.AddDynamic(this, &UShowItemDataEntry::OnUnhovered_SelectItemButton);

	OriginalTextColor = ItemAmountTextBlock->GetColorAndOpacity();
	OriginalSelectItemButtonStyle = SelectItemButton->GetStyle();
	ItemMovingIconImage->SetVisibility(ESlateVisibility::Collapsed);

	OriginalMovingItemImagePosition = ItemMovingIconImage->GetRenderTransform().Translation;
}

void UShowItemDataEntry::NativeTick(const FGeometry& MyGeometry, float Delta)
{
	Super::NativeTick(MyGeometry, Delta);


	if (!CheckIfCanStartMovingItem())
		return;

	MovingItemIcon(MyGeometry, Delta);
}

bool UShowItemDataEntry::CheckIfCanStartMovingItem()
{
	if (!bCanStartMovingItem)
		return true;

	if (UKismetMathLibrary::EqualEqual_Vector2DVector2D(UWidgetLayoutLibrary::GetMousePositionOnPlatform(), CursorLocationWhenPressed, CursorDistanceToStartMovingItem))
	{ 
		return false;
	}

	ItemMovingIconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	bMovingItemIcon = true;
	MoveItemIconToCursorTimeElapsed = 0.f;

	bCanStartMovingItem = false;

	return true;
}


void UShowItemDataEntry::MovingItemIcon(const FGeometry& MyGeometry, float Delta)
{
	if (!bMovingItemIcon)
		return;

	const FVector2D LocalMousePosition = MyGeometry.AbsoluteToLocal(UWidgetLayoutLibrary::GetMousePositionOnPlatform());

	if (bIgnoreSmoothItemMoving)
	{
		ItemMovingIconImage->SetRenderTranslation(LocalMousePosition);
		return;
	}

	if (MoveItemIconToCursorTimeElapsed <= MoveItemIconToCursorTime)
	{
		const FVector2D NewItemMovingIconPosition = FMath::Lerp(OriginalMovingItemImagePosition, LocalMousePosition, MoveItemIconToCursorTimeElapsed / MoveItemIconToCursorTime);
		ItemMovingIconImage->SetRenderTranslation(NewItemMovingIconPosition);
		MoveItemIconToCursorTimeElapsed += Delta;
	}
	else
	{
		bIgnoreSmoothItemMoving = true;
	}
}

void UShowItemDataEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!IsValid(ListItemObject))
		return;
	
	ShowItemDataObject = Cast<UShowItemDataObject>(ListItemObject);
	if (!IsValid(ShowItemDataObject))
		return;

	if (ShowItemDataObject->bInitallySelectedItem)
	{
		OnPressed_SelectItemButton();
		OnReleased_SelectItemButton();
	}

	UpdateItemDisplayInformations();
}

void UShowItemDataEntry::UpdateItemDisplayInformations()
{
	if (!IsValid(ShowItemDataObject))
		return;

	if (IsValid(ShowItemDataObject->ItemData.ItemIcon))
	{
		ItemIconImage->SetBrushFromTexture(ShowItemDataObject->ItemData.ItemIcon);
		ItemMovingIconImage->SetBrushFromTexture(ShowItemDataObject->ItemData.ItemIcon);
	}
	
	ItemNameTextBlock->SetText(ShowItemDataObject->ItemData.ItemDisplayText);
	ItemAmountTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemAmount));

	const FString ItemDurability = FString::FromInt(FMath::FloorToInt32(ShowItemDataObject->ItemData.ItemDurability)) + "%";
	ItemDurabilityTextBlock->SetText(FText::FromString(ItemDurability));

	ItemWeightTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemData.ItemWeight * ShowItemDataObject->ItemAmount));

	ItemPriceTextBlock->SetText(FText::AsNumber(ShowItemDataObject->ItemData.ItemPrice));
}

void UShowItemDataEntry::OnPressed_SelectItemButton()
{
	if (!IsValid(ShowItemDataObject))
		return;

	if (!IsValid(ShowItemDataObject->InventoryMenuWidget))
		return;

	ShowItemDataObject->InventoryMenuWidget->OnClicked_ShowItemDataEntry(ShowItemDataObject);
	ShowItemDataObject->InventoryMenuWidget->SetSelectedShowItemDataEntry(this);
	ChangeFontColorToAllTextes(OnHoveredFontColor);
	SelectItemButton->SetStyle(ItemSelectedButtonStyle);

	CursorLocationWhenPressed = UWidgetLayoutLibrary::GetMousePositionOnPlatform();
	bCanStartMovingItem = true;
}

void UShowItemDataEntry::OnReleased_SelectItemButton()
{
	bCanStartMovingItem = false;
	bMovingItemIcon = false;
	bIgnoreSmoothItemMoving = false;
	ItemMovingIconImage->SetVisibility(ESlateVisibility::Collapsed);
	ItemMovingIconImage->SetRenderTranslation(OriginalMovingItemImagePosition);
}

void UShowItemDataEntry::OnHovered_SelectItemButton()
{
	;
}

void UShowItemDataEntry::OnUnhovered_SelectItemButton()
{
	;
}

void UShowItemDataEntry::DeselectShowItemEntry()
{
	ChangeFontColorToAllTextes(OriginalTextColor);
	SelectItemButton->SetStyle(OriginalSelectItemButtonStyle);
}

void UShowItemDataEntry::ChangeFontColorToAllTextes(const FSlateColor& NewColor)
{
	ItemNameTextBlock->SetColorAndOpacity(NewColor);
	ItemAmountTextBlock->SetColorAndOpacity(NewColor);
	ItemDurabilityTextBlock->SetColorAndOpacity(NewColor);
	ItemWeightTextBlock->SetColorAndOpacity(NewColor);
	ItemPriceTextBlock->SetColorAndOpacity(NewColor);
}

