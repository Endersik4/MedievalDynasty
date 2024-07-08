// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "KnowledgeInformationEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UKnowledgeInformationEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> KnowledgeInformationButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> KnowledgeNameText = nullptr;

	UFUNCTION()
	void OnClicked_KnowledgeInformationButton();

private:
	UPROPERTY(Transient)
	TObjectPtr<class UKnowledgeInformationEntryObject> KnowledgeInformationEntryObject = nullptr;
};
