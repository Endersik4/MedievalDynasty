// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "CategoryKnowledgeEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UCategoryKnowledgeEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	void ActivateCategoryEntry(bool bActivate);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> SelectCategoryButton = nullptr;

	UFUNCTION()
	void OnClicked_SelectCategoryButton();

private:

	UPROPERTY(Transient)
	TObjectPtr<class UCategoryKnowledgeEntryObject> CategoryKnowledgeEntryObject = nullptr;
};
