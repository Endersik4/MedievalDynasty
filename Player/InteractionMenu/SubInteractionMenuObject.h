// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractionMenuWidget.h"
#include "SubInteractionMenuObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API USubInteractionMenuObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient)
	FSubInteractionMenuType SubInteractionMenuType = FSubInteractionMenuType();
	UPROPERTY(Transient)
	TObjectPtr<UInteractionMenuWidget> InteractionMenuWidget = nullptr;
};
