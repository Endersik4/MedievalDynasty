// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/DragItemWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UDragItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DraggingItemCanvasSlot = Cast<UCanvasPanelSlot>(DraggingItemIconImage->Slot);

	DraggingItemIconImage->SetVisibility(ESlateVisibility::Hidden);
}

void UDragItemWidget::StartDraggingItem(FBaseItemData NewCurrentDragingItem, const FVector2D& StartDragingLocation)
{
	CurrentDragingItem = NewCurrentDragingItem;
	ItemEntryIconPosition = GetTickSpaceGeometry().AbsoluteToLocal(StartDragingLocation);
	
	CursorPositionWhenPressed = UWidgetLayoutLibrary::GetMousePositionOnPlatform();
	bStartCheckingDraggingItem = true;
}

void UDragItemWidget::NativeTick(const FGeometry& MyGeometry, float Delta)
{
	Super::NativeTick(MyGeometry, Delta);

	if (!CheckIfCanStartDraggingItem())
		return;

	DraggingItemIcon(MyGeometry, Delta);
}

bool UDragItemWidget::CheckIfCanStartDraggingItem()
{
	if (!bStartCheckingDraggingItem)
		return true;

	if (UKismetMathLibrary::EqualEqual_Vector2DVector2D(UWidgetLayoutLibrary::GetMousePositionOnPlatform(), CursorPositionWhenPressed, CursorDistanceToStartMovingItem))
	{
		return false;
	}

	DraggingItemIconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (IsValid(CurrentDragingItem.ItemIcon))
		DraggingItemIconImage->SetBrushFromTexture(CurrentDragingItem.ItemIcon);

	bIsDraggingItem = true;
	MoveItemIconToCursorTimeElapsed = 0.f;

	bStartCheckingDraggingItem = false;
	bIgnoreSmoothDragging = false;

	return true;
}

void UDragItemWidget::DraggingItemIcon(const FGeometry& MyGeometry, float Delta)
{
	if (!bIsDraggingItem || !IsValid(DraggingItemCanvasSlot))
		return;

	const FVector2D& MousePosition = MyGeometry.AbsoluteToLocal(UWidgetLayoutLibrary::GetMousePositionOnPlatform());

	if (bIgnoreSmoothDragging)
	{
		DraggingItemCanvasSlot->SetPosition(MousePosition);
		return;
	}

	if (MoveItemIconToCursorTimeElapsed <= MoveItemIconToCursorTime)
	{
		const FVector2D NewItemMovingIconPosition = FMath::Lerp(ItemEntryIconPosition, MousePosition, MoveItemIconToCursorTimeElapsed / MoveItemIconToCursorTime);
		DraggingItemCanvasSlot->SetPosition(NewItemMovingIconPosition);

		MoveItemIconToCursorTimeElapsed += Delta;
	}
	else
	{
		bIgnoreSmoothDragging = true;
	}
}

void UDragItemWidget::StopDraggingItem()
{
	if (!IsValid(DraggingItemIconImage))
		return;

	bStartCheckingDraggingItem = false;
	bIgnoreSmoothDragging = false;
	DraggingItemIconImage->SetVisibility(ESlateVisibility::Hidden);

	// when Mouse left Click is released and the mouse is over on QuickSelect/Equipment Button then OnHovered function is called to Set item icon in image
	GetWorld()->GetTimerManager().SetTimer(RemoveCurrentDraggingItemHandle, this, &UDragItemWidget::RemoveDragingItem, RemoveDragingItemTime, false);
}

void UDragItemWidget::RemoveDragingItem()
{
	CurrentDragingItem = FBaseItemData();
	bIsDraggingItem = false;
}