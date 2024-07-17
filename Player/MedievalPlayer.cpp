// Copyright Adam Bartela.All Rights Reserved


#include "MedievalDynasty/Player/MedievalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

#include "Inventory/InventoryComponent.h"
#include "Components/PlayerStatusComponent.h"
#include "MedievalDynasty/Objects/Components/WaypointComponent.h"

AMedievalPlayer::AMedievalPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Capsule Component"));
	RootComponent = PlayerCapsuleComponent;
	PlayerCapsuleComponent->SetSimulatePhysics(true);

	PlayerSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Skeletal Mesh"));
	PlayerSkeletalMesh->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	PlayerStatusComponent = CreateDefaultSubobject<UPlayerStatusComponent>(TEXT("Player Status Component"));
	WaypointComponent = CreateDefaultSubobject<UWaypointComponent>(TEXT("Waypoint Component"));

	bReplicates = true;
	SetReplicateMovement(true);
}

void AMedievalPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void AMedievalPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateMeshTowardsCameraDir(DeltaTime);
}

void AMedievalPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMedievalPlayer::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMedievalPlayer::Right);

	PlayerInputComponent->BindAxis(FName(TEXT("LookRight")), this, &AMedievalPlayer::LookRight);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp")), this, &AMedievalPlayer::LookUp);

	PlayerInputComponent->BindAction<FSelectSubInteractionMenu>(FName(TEXT("OpenInventory")), IE_Pressed, InventoryComponent.Get(), &UInventoryComponent::OpenInteractionMenu, 0);
	PlayerInputComponent->BindAction<FSelectSubInteractionMenu>(FName(TEXT("OpenSkills")), IE_Pressed, InventoryComponent.Get(), &UInventoryComponent::OpenInteractionMenu, 1);
}

void AMedievalPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMedievalPlayer, ReplicatedRotation);
}

#pragma region ////////// movement ///////////
void AMedievalPlayer::Forward(float Axis)
{
	FVector Dir = CameraComponent->GetForwardVector();
	Dir.Z = 0.f;
	ReplicateMove(Dir, Axis, FName(TEXT("Right")));
}

void AMedievalPlayer::Right(float Axis)
{
	FVector Dir = CameraComponent->GetRightVector();
	Dir.Z = 0.f;
	ReplicateMove(Dir, Axis, FName(TEXT("Forward")));
}

void AMedievalPlayer::ReplicateMove(FVector Direction, float Axis, const FName InputAxisName)
{
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		Move(Direction, Axis, InputAxisName);
	}
	else
	{
		ServerMove(Direction, Axis, InputAxisName);
	}
}

void AMedievalPlayer::Move(FVector Direction, float Axis, const FName InputAxisName)
{
	float Speed = MovementSpeed / (GetInputAxisValue(InputAxisName) != 0.f ? ForwardAndRightAtTheSameTimeDivider : 1);

	Direction.Z = 0.f;
	const FVector& Force = (Axis * Direction * Speed) + CalculateCounterMovement();
	PlayerCapsuleComponent->AddImpulse(Force);
}

void AMedievalPlayer::ServerMove_Implementation(FVector Direction, float Axis, const FName InputAxisName)
{
	Move(Direction, Axis, InputAxisName);
}

FVector AMedievalPlayer::CalculateCounterMovement()
{	
	const FVector& CounterVelocity = GetVelocity() * FVector(-1.f, -1.f, 0.f);

	float CounterForce = CounterMovementForce;

	return FVector(CounterForce * CounterVelocity.X, CounterForce * CounterVelocity.Y, 0);
}
#pragma endregion

#pragma region //////////// look /////////////
void AMedievalPlayer::LookRight(float Axis)
{
	if (Axis == 0.f)
		return;

	FRotator OriginalRotation = SpringArmComponent->GetComponentRotation();
	OriginalRotation.Yaw += Axis;
	SpringArmComponent->SetWorldRotation(OriginalRotation);
}

void AMedievalPlayer::LookUp(float Axis)
{
	if (Axis == 0.f)
		return;

	FRotator OriginalRotation = SpringArmComponent->GetComponentRotation();
	OriginalRotation.Pitch += Axis;
	if (OriginalRotation.Pitch < LimitPitchRotation.GetLowerBoundValue() || OriginalRotation.Pitch > LimitPitchRotation.GetUpperBoundValue())
		return;

	SpringArmComponent->SetWorldRotation(OriginalRotation);
}
#pragma endregion

#pragma region ////////// Update Mesh Rotation //////////////
void AMedievalPlayer::RotateMeshTowardsCameraDir(float Delta)
{
	if (GetInputAxisValue(FName("Forward")) == 0 && GetInputAxisValue(FName("Right")) == 0)
		return;

	FRotator PlayerRot(0.f);
	PlayerRot.Yaw = PlayerSkeletalMesh->GetComponentRotation().Yaw;
	TargetRotationToRotate.Yaw = GetCurrentYawMoveDirection();
	FRotator NewRot = UKismetMathLibrary::RInterpTo(PlayerRot, TargetRotationToRotate, Delta, 7.f);
	
	SetPlayerRotation(NewRot);
}

float AMedievalPlayer::GetCurrentYawMoveDirection()
{
	const float ForwardVal = GetInputAxisValue(FName("Forward"));
	const float RightVal = GetInputAxisValue(FName("Right"));

	if (ForwardVal < 0 && RightVal < 0) // left bottom corner
		return (SpringArmComponent->GetComponentRotation().Yaw - 180.f) + 45.f;
	else if (ForwardVal < 0 && RightVal > 0) // right bottom corner
		return (SpringArmComponent->GetComponentRotation().Yaw - 180.f) - 45.f;
	else if (ForwardVal > 0 && RightVal > 0) // left top corner
		return SpringArmComponent->GetComponentRotation().Yaw + 45.f;
	else if (ForwardVal > 0 && RightVal < 0) // right top corner
		return SpringArmComponent->GetComponentRotation().Yaw - 45.f;
	else if (ForwardVal < 0) // bottom
		return SpringArmComponent->GetComponentRotation().Yaw - 180.f;
	else if (RightVal < 0) // left
		return SpringArmComponent->GetComponentRotation().Yaw - 90.f;
	else if (RightVal > 0) // right
		return SpringArmComponent->GetComponentRotation().Yaw + 90.f;
	else // top
		return SpringArmComponent->GetComponentRotation().Yaw;
}

void AMedievalPlayer::SetPlayerRotation(FRotator NewRotation)
{
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		PlayerSkeletalMesh->SetWorldRotation(NewRotation);
		ReplicatedRotation = NewRotation;

		UpdateRotationOnClients();
	}
	else // execute RPC on server
	{
		ServerSetPlayerRotation(NewRotation);
	}
}

void AMedievalPlayer::UpdateRotationOnClients()
{
	PlayerSkeletalMesh->SetWorldRotation(ReplicatedRotation);
}

void AMedievalPlayer::ServerSetPlayerRotation_Implementation(FRotator NewRotation)
{
	SetPlayerRotation(NewRotation);
}
#pragma endregion