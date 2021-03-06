// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OverallHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOVECPP_API AOverallHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// Pause Widget Pointer
	TSharedPtr<class SPauseWidget> PauseWidget;
	TSharedPtr<class SWidget> PauseWidgetContainer;
	// Dialogue Widget Pointer
	TSharedPtr<class SDialogueWidget> DialogueWidget;
	TSharedPtr<class SWidget> DialogueWidgetContainer;

	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();

	void ShowDialogue();
	void RemoveDialogue();
	
};
