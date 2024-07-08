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

public:
	void SelectedKnowledgeInformationEntry(bool bSelected = true);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> KnowledgeInformationButton = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> KnowledgeNameText = nullptr;

	UFUNCTION()
	void OnPressed_KnowledgeInformationButton();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Knowledge Information Settings")
	FButtonStyle SelectedKnowledgeButtonStyle = FButtonStyle();
	UPROPERTY(EditDefaultsOnly, Category = "Knowledge Information Settings")
	FSlateColor SelectedKnowledgeFontColor = FSlateColor(FColor::White);

	UPROPERTY(Transient)
	TObjectPtr<class UKnowledgeInformationEntryObject> KnowledgeInformationEntryObject = nullptr;

	UPROPERTY(Transient)
	FButtonStyle OriginalKnowledgeButtonStyle = FButtonStyle();
	UPROPERTY(Transient)
	FSlateColor OriginalKnowledgeFontColor = FSlateColor();
};
