// Copyright Adam Bartela. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KnowledgeWidget.generated.h"

UENUM()
enum EKnowledgeType
{
	EKT_Game UMETA(DisplayName = "Game"),
	EKT_Items UMETA(DisplayName = "Items"),
};

USTRUCT(BlueprintType)
struct FGameKnowledge : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText KnowledgeName = FText();
	UPROPERTY(EditAnywhere, meta = (MultiLine = true))
	FText KnowledgeDescription = FText();
	UPROPERTY(EditAnywhere)
	bool bUseVideo = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseVideo"))
	TObjectPtr<UMaterial> MediaPlayerMaterial = nullptr;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseVideo"))
	TObjectPtr<class UMediaPlayer> MediaPlayerToPlay = nullptr;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseVideo"))
	TObjectPtr<class UMediaSource> MediaSourceToPlay = nullptr;
};

USTRUCT(BlueprintType)
struct FDropDownMenuData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText DropDownMenuName = FText();
	UPROPERTY(EditAnywhere)
	TArray<FName> AllKnowledgeInMenuRowNames;
};

USTRUCT(BlueprintType)
struct FKnowledgeCategory
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EKnowledgeType> KnowledgeType = EKT_Game;
	UPROPERTY(EditAnywhere)
	FButtonStyle SelectCategoryButtonStyle = FButtonStyle();
	UPROPERTY(EditAnywhere)
	FButtonStyle CategorySelectedButtonStyle = FButtonStyle();
	UPROPERTY(EditAnywhere)
	FText CategoryDisplayText = FText();

	UPROPERTY(EditAnywhere)
	TArray<FDropDownMenuData> AllKnowledgeDropDownMenu;
};

class UImage;
UCLASS()
class MEDIEVALDYNASTY_API UKnowledgeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateCategoryDisplayText(const FText& NewCategoryDisplayText);
	void FIllKnowledgeTreeView(TObjectPtr<class UCategoryKnowledgeEntryObject> CategoryObjectToFillFrom);

	FORCEINLINE TObjectPtr<UDataTable> GetKnowledgeInformationDataAsset() const {return KnowledgeInformationDataAsset;}
	FORCEINLINE TObjectPtr<class UDetailedKnowledgeInfoWidget> GetDetailedKnowledgeInfoWidget() const {return DetailedKnowledgeInfoWidget;}

	void SetDeselectCategoryFunc(TFunction<void(bool)> NewDeselectCategoryFunc);
	void SetDeselectEntryFunc(TFunction<void(bool)> NewDeselectEntryFunc);


protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTileView> KnowledgeCategoriesTileView = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTreeView> KnowledgeTreeView = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> CategoryNameHorizontalBox = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> CategoryDisplayName = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> LeftCategoryDecorationImage = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> RightCategoryDecorationImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UScrollBox> KnowledgeListHolderScrollBox = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UDetailedKnowledgeInfoWidget> DetailedKnowledgeInfoWidget = nullptr;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Knowledge settings")
	TObjectPtr<UDataTable> KnowledgeInformationDataAsset;
	UPROPERTY(EditDefaultsOnly, Category = "Category Knowledge settings")
	TEnumAsByte<EKnowledgeType> InitalKnowledgeCategoryType = EKT_Game;
	UPROPERTY(EditDefaultsOnly, Category = "Category Knowledge settings")
	TArray<FKnowledgeCategory> AllKnowledgeCategories;

	void FIllKnowledgeCategoriesTileView();

	TFunction<void(bool)> DeselectEntryFunc;
	TFunction<void(bool)> DeselectCategoryFunc;
};
