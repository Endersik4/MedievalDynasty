// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SortedMapWaypointsWidget.generated.h"

class UTextBlock;
class UWrapBox;
class UImage;
class UButton;
UCLASS()
class MEDIEVALDYNASTY_API USortedMapWaypointsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetMapMenuWidget(TObjectPtr<class UMapMenuWidget> NewMapMenuWidget) { MapMenuWidget = NewMapMenuWidget; }

	void FillSortedWaypointsListView();

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> SortDisplayWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> SortDecorationImage_Left = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> SortDecorationImage_Right = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SortDisplayTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundSortDisplayNameImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> SortDisplayNameWrapBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SortDisplayNameTextBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> LeftChoice_SortButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> RightChoice_SortButton = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UListView> SortedWaypointsListView = nullptr;

	UFUNCTION()
	void OnPressed_LeftChoice_SortButton();
	UFUNCTION()
	void OnPressed_RightChoice_SortButton();

private:
	UPROPERTY(Transient)
	TObjectPtr<class UMapMenuWidget> MapMenuWidget = nullptr;
};
