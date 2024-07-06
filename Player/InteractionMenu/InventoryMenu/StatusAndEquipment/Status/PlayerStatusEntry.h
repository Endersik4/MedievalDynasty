// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PlayerStatusEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UPlayerStatusEntry : public UUserWidget, public IUserObjectListEntry 
{
	GENERATED_BODY()

public:
	void UpdatePlayerStatusEntry();
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> StatusIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UProgressBar> StatusProgressBar = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> StatusValueText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> HoverStatusButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UBorder> HoverStatusBorder = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> HoverStatusTextBlock = nullptr;

	UFUNCTION()
	void OnHovered_HoverStatusBorder();
	UFUNCTION()
	void OnUnhovered_HoverStatusBorder();

private:

	void MoveHoverStatus(const FGeometry& MyGeometry);
	UPROPERTY(Transient)
	bool bStatusHovered = false;

	UPROPERTY(Transient)
	TObjectPtr<class UPlayerStatusObject> PlayerStatusObject = nullptr;
};
