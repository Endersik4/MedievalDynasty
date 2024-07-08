// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/KnowledgeMenu/DetailedKnowledgeInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "MediaPlayer.h"

void UDetailedKnowledgeInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	VideoToPlayImage->SetVisibility(ESlateVisibility::Collapsed);
	SetVisibility(ESlateVisibility::Hidden);
}

void UDetailedKnowledgeInfoWidget::NativeDestruct()
{
	Super::NativeDestruct();

	DisableDetailedKnowledgeWidget();
}

void UDetailedKnowledgeInfoWidget::UpdateDetailedKnowledgeInformation(const FName& KnowledgeRowName, TObjectPtr<UDataTable> KnowledgeInfoDataTable)
{
	if (!IsValid(KnowledgeInfoDataTable))
		return;

	SetVisibility(ESlateVisibility::Visible);

	FGameKnowledge* KnowledgeInfo = KnowledgeInfoDataTable->FindRow<FGameKnowledge>(KnowledgeRowName, "");
	if (!KnowledgeInfo)
		return;

	KnowledgeNameText->SetText(KnowledgeInfo->KnowledgeName);
	KnowledgeDescriptionText->SetText(KnowledgeInfo->KnowledgeDescription);

	StartVideo(KnowledgeInfo);
}

void UDetailedKnowledgeInfoWidget::StartVideo(FGameKnowledge* KnowledgeInfo)
{
	if (!KnowledgeInfo->bUseVideo)
	{
		DisableDetailedKnowledgeWidget(false);
	}

	if (!IsValid(KnowledgeInfo->MediaPlayerToPlay))
		return;

	VideoToPlayImage->SetVisibility(ESlateVisibility::Visible);
	VideoToPlayImage->SetBrushFromMaterial(KnowledgeInfo->MediaPlayerMaterial);

	CurrentPlayingMediaPlayer = KnowledgeInfo->MediaPlayerToPlay;
	CurrentPlayingMediaPlayer->OpenSource(KnowledgeInfo->MediaSourceToPlay);
	CurrentPlayingMediaPlayer->SetLooping(true);
	CurrentPlayingMediaPlayer->Rewind();
	CurrentPlayingMediaPlayer->Play();
}

void UDetailedKnowledgeInfoWidget::DisableDetailedKnowledgeWidget(bool bHideWidget)
{
	if (IsValid(CurrentPlayingMediaPlayer))
		CurrentPlayingMediaPlayer->Close();

	VideoToPlayImage->SetVisibility(ESlateVisibility::Collapsed);

	if (bHideWidget)
		SetVisibility(ESlateVisibility::Hidden);
}
