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
	FText KnowledgeNameDisplayText = FText();
	UPROPERTY(Transient)
	FName KnowledgeRowName = FName();
	UPROPERTY(Transient)
	bool bKnowledgeSelected = false;
	UPROPERTY(Transient)
	TObjectPtr<UKnowledgeWidget> KnowledgeWidget = nullptr;
};
