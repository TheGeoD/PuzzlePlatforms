// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
bool UMenuWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false; 
	}
	UWorld* World = GetWorld(); 
	PlayerController = (World != nullptr) ? World->GetFirstPlayerController() : nullptr;
	return true; 
}
void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMenuWidget::Setup()
{
	this->AddToViewport();
	
	if (PlayerController)
	{
		FInputModeUIOnly InputModeData;

		//InputModeData.SetWidgetToFocus(this->TakeWidget()); This creates a warning in editor, "Attempting to focus Non-Focusable widget" 
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;
	}

}

void UMenuWidget::TearDown()
{

	UWorld* World = GetWorld(); 
	if(!World)
	{
		return; 
	}
	ULevel* Level = ((PlayerController != nullptr) ? PlayerController->GetLevel() : nullptr);
	if (World && Level)
	{
		OnLevelRemovedFromWorld(Level, World);
	}
	ReturnGameInputControl(); 
}

void UMenuWidget::ReturnGameInputControl()
{
	this->RemoveFromViewport(); 
	if (PlayerController)
	{
		FInputModeGameOnly InputModeData;
		InputModeData.SetConsumeCaptureMouseDown(false);

		PlayerController->SetInputMode(InputModeData);
	}
}


