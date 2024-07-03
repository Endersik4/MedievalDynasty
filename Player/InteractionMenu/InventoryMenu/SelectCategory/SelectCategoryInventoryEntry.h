// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "SelectCategoryInventoryEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API USelectCategoryInventoryEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> SelectCategoryButton = nullptr;

	UFUNCTION()
	void OnClicked_SortInventoryButton();

private:
	UPROPERTY(Transient)
	TObjectPtr<class USelectCategoryEntryObject> SelectCategoryEntryObject = nullptr;
};
