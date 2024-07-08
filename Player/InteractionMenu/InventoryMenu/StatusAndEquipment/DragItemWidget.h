// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MedievalDynasty/Player/Inventory/ItemData.h"

#include "DragItemWidget.generated.h"

class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UDragItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void StartDraggingItem(FBaseItemData NewCurrentDragingItem, const FVector2D& StartDragingLocation);
	void StopDraggingItem();

	FORCEINLINE FBaseItemData GetCurrentDragingItem() const { return CurrentDragingItem; }
	FORCEINLINE bool GetIsDraggingItem() const { return bIsDraggingItem; }

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float Delta) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> DraggingItemIconImage = nullptr;

private:
	// When player presses Item Button then save Cursor Position and after moving 
	UPROPERTY(EditDefaultsOnly, Category = "Draging Item Icon Settings")
	float CursorDistanceToStartMovingItem = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Draging Item Icon Settings")
	float MoveItemIconToCursorTime = 0.13f;
	UPROPERTY(EditDefaultsOnly, Category = "Draging Item Icon Settings")
	float RemoveDragingItemTime = 0.01f;

	UPROPERTY(Transient)
	bool bIsDraggingItem = false;
	UPROPERTY(Transient)
	FBaseItemData CurrentDragingItem = FBaseItemData();

	bool CheckIfCanStartDraggingItem();
	UPROPERTY(Transient)
	bool bStartCheckingDraggingItem = false;
	UPROPERTY(Transient)
	FVector2D CursorPositionWhenPressed = FVector2D(0.f);

	void DraggingItemIcon(const FGeometry& MyGeometry, float Delta);
	UPROPERTY(Transient)
	bool bIgnoreSmoothDragging = false;
	UPROPERTY(Transient)
	FVector2D ItemEntryIconPosition = FVector2D(0.f);
	UPROPERTY(Transient)
	float MoveItemIconToCursorTimeElapsed = 0.f;

	void RemoveDragingItem();

	UPROPERTY(Transient)
	FTimerHandle RemoveCurrentDraggingItemHandle = FTimerHandle();
};
