// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/KnowledgeWidget.h"

#include "DetailedKnowledgeInfoWidget.generated.h"

class UImage;
class UTextBlock;
UCLASS()
class MEDIEVALDYNASTY_API UDetailedKnowledgeInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateDetailedKnowledgeInformation(const FName& KnowledgeRowName, TObjectPtr<UDataTable> KnowledgeInfoDataTable);
	void DisableDetailedKnowledgeWidget(bool bHideWidget = true);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> KnowledgeIconImage = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> KnowledgeNameText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UScrollBox> KnowledgeScrollBox = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> VideoToPlayImage = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> KnowledgeDescriptionText = nullptr;

private:
	UPROPERTY(Transient)
	TObjectPtr<class UMediaPlayer> CurrentPlayingMediaPlayer = nullptr;

	void StartVideo(FGameKnowledge* KnowledgeInfo);
};
