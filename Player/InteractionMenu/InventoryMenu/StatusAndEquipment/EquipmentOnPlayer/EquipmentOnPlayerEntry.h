// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "EquipmentOnPlayerEntry.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UEquipmentOnPlayerEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UButton> EquipmentOnPlayerButton = nullptr;
};
