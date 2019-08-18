// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverlayMenu.h"
#include "Components/Button.h"

bool UGameOverlayMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}
	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverlayMenu::UserClickedMainMenuButton);
	}
	if(CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UGameOverlayMenu::UserClickedCancelButton);
	}

	return true; 
}


void UGameOverlayMenu::UserClickedMainMenuButton()
{
	this->TearDown();
	if(MenuInterface)
	{
		MenuInterface->LoadMainMenu();
	}
}

void UGameOverlayMenu::UserClickedCancelButton()
{
	ReturnGameInputControl();
}



