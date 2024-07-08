// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"
#include "DropDownMenuEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UDropDownMenuEntryObject : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FDropDownMenuData DropDownMenuData;

	UPROPERTY()
	TObjectPtr<UKnowledgeWidget> KnowledgeWidget = nullptr;
	UPROPERTY()
	bool bMenuIsOpened = false;
};
