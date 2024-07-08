// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"

#include "KnowledgeInformationEntryObject.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDYNASTY_API UKnowledgeInformationEntryObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient)
	FText GameKnowledgeDisplayText = FText();
	UPROPERTY(Transient)
	FName GameKnowledgeRowName = FName();
	UPROPERTY(Transient)
	TObjectPtr<UKnowledgeWidget> KnowledgeWidget = nullptr;
};
