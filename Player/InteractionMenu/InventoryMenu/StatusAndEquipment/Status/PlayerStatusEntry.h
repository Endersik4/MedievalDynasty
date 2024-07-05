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

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UImage> StatusIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UProgressBar> StatusProgressBar = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> StatusValueText = nullptr;

private:

	UPROPERTY(Transient)
	TObjectPtr<class UPlayerStatusObject> PlayerStatusObject = nullptr;
};
