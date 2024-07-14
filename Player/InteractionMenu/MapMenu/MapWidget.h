// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

UCLASS()
class MEDIEVALDYNASTY_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> MapCanvasPanel = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> MapImage = nullptr;


private:
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	FKey MouseButtonForDraggingMap = FKey();
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	float DraggingSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	FInt32Range ZoomRange = FInt32Range(0, 12);
	UPROPERTY(EditAnywhere, Category = "Map Settings")
	float ZoomFactor = 0.8f;

	UPROPERTY(Transient)
	bool bIsDraggingMap = false;
	UPROPERTY(Transient)
	int32 CurrentZoom = 0;

	// returns a Vector that does not exceed the size of the MapImage
	FVector2D ClampSides(const FGeometry& MyGeometry, FVector2D VectorToClamp);
};
