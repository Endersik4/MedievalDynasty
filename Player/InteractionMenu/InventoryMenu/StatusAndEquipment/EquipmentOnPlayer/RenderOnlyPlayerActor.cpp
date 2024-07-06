// Copyright Adam Bartela. All Rights Reserved


#include "MedievalDynasty/Player/InteractionMenu/InventoryMenu/StatusAndEquipment/EquipmentOnPlayer/RenderOnlyPlayerActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"

ARenderOnlyPlayerActor::ARenderOnlyPlayerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = RootSceneComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 200.f;

	CaptureOnlyPlayerSceneComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture Only Player Scene Component"));
	CaptureOnlyPlayerSceneComponent->SetupAttachment(SpringArmComponent);
	CaptureOnlyPlayerSceneComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureOnlyPlayerSceneComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
}

void ARenderOnlyPlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARenderOnlyPlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARenderOnlyPlayerActor::CaptureOnlyActor(TObjectPtr<AActor> ActorToCapture)
{
	CaptureOnlyPlayerSceneComponent->ShowOnlyActorComponents(ActorToCapture);
}

