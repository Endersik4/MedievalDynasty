// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "DropDownMenuEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UDropDownMenuEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> DropDownMenuButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> DropDownArrowImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> DropDownMenuNameText = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTreeView> KnowledgeInformationsTreeView = nullptr;

	UFUNCTION()
	void OnClicked_DropDownMenuButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Drop Down Menu Settings")
	float ArrowAngleWhenClosed = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "Drop Down Menu Settings")
	float ArrowAngleWhenOpened = 90.f;

	UPROPERTY(Transient)
	TObjectPtr<class UDropDownMenuEntryObject> DropDownMenuEntryObject = nullptr;

	void FillKnowledgeInformationsTreeView();

};
