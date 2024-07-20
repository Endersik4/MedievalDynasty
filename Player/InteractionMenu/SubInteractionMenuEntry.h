// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SubInteractionMenuEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API USubInteractionMenuEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void ActivateSubInteractionMenu(bool bActivate = true);
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual FReply NativeOnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UButton> SubInteractionButton = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> SubInteractionTextBlock = nullptr;

	UFUNCTION()
	void OnClicked_SubInteractionButton();
	UFUNCTION()
	void OnHovered_SubInteractionButton();
	UFUNCTION()
	void OnUnhovered_SubInteractionButton();

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OnHovered_SubInteractionButton_Anim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OnUnhovered_SubInteractionButton_Anim = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "SubInteraction Menu Settings")
	FSlateColor MenuActivatedTextColor = FSlateColor();
	UPROPERTY(EditDefaultsOnly, Category = "SubInteraction Menu Settings")
	FButtonStyle MenuActivatedButtonStyle = FButtonStyle();

	UPROPERTY(Transient)
	TObjectPtr<class USubInteractionMenuObject> SubInteractionMenuObject = nullptr;
	UPROPERTY(Transient)
	FSlateColor OriginalSubInteractionTextColor = FSlateColor();
	UPROPERTY(Transient)
	FButtonStyle OriginalSubInteractionButtonStyle = FButtonStyle();
};
