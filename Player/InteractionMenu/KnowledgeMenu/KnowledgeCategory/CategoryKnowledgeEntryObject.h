// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"

#include "CategoryKnowledgeEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UCategoryKnowledgeEntryObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FKnowledgeCategory KnowledgeCategory;
	UPROPERTY()
	bool bInitialCategory = false;
	UPROPERTY()
	TObjectPtr<UKnowledgeWidget> KnowledgeWidget = nullptr;
	
};
