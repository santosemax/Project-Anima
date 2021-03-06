// Fill out your copyright notice in the Description page of Project Settings.

#include "CitanTriggerBox.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printf(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

// Default Values (defined in header file as constructor)
ACitanTriggerBox::ACitanTriggerBox()
{
	// Register Events
	OnActorBeginOverlap.AddDynamic(this, &ACitanTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACitanTriggerBox::OnOverlapEnd);
}

void ACitanTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void ACitanTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// If other actor is overlapping (excluding itself)
	if (OtherActor && (OtherActor != this))
	{
		MainCharacter->eventPossible = true;
		
		print("Overlap Begin");
		printf("Overlapped Actor = %s", *OverlappedActor->GetName());

		MainCharacter->PromptPlayer();
	}
}

void ACitanTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// If other actor is overlapping (excluding itself)
	if (OtherActor && (OtherActor != this))
	{
		MainCharacter->eventPossible = false;
		
		print("Overlap Ended");
		printf("Overlapped Actor = %s", *OtherActor->GetName());

		MainCharacter->UnpromptPlayer();
	}
}



