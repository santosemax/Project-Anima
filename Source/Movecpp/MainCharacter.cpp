// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Destroy Default Mesh (Not Needed)
	GetMesh()->DestroyComponent();
	GetMesh()->SetActive(false);

	// Setup BoomArm
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));	
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 700.0f;
	BoomArm->bUsePawnControlRotation = true;

	// Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Setup Event Indicator
	EventPrompt = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Prompt"));
	EventPrompt->SetupAttachment(RootComponent);

	// Setup Box Collider (and its overlap functions)
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetCollisionProfileName(TEXT("Collider"));
	BoxCollider->SetupAttachment(RootComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

	AnimationSetup();

}


// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	EventPrompt->SetSpriteColor(FLinearColor(1.0, 1.0, 1.0, 0.0));
	EventPrompt->SetVisibility(false);

	eventPossible = false;

	// Connect BoxCollider Overlap Function
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd);

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	relVelocity = (AMainCharacter::GetCharacterMovement()->GetLastInputVector()) / 10;

	// Get Direction of Character (Debugging)
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
	//	FString::Printf(TEXT("Rel. Velocity: %s"), *relVelocity.ToString())); // Debug Line for Movement

	// Get Set Animation to the return of Animation Controller
	CharacterComponent->SetFlipbook(AnimationControl(relVelocity));

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

}

// Movement Functions
void AMainCharacter::MoveForward(float Value)
{
	direction = FVector(10.0f, 0.0f, 0.0f);

	if (Controller != nullptr && Value != 0.0)
	{
		AddMovementInput(direction, Value);
	}

}
void AMainCharacter::MoveRight(float Value)
{
	direction = FVector(0.0f, 10.0f, 0.0f);

	if (Controller != nullptr && Value != 0.0)
	{
		AddMovementInput(direction, Value);
	}
}


