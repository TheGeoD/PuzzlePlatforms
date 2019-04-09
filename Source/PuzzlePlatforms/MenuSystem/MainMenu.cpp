// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success)
	{
		return false; 
	}
	if(Host && Join)
	{
		Host->OnClicked.AddDynamic(this, &UMainMenu::UserClickedHost);
		Join->OnClicked.AddDynamic(this, &UMainMenu::UserClickedJoin);
	}

	MenuInterface = Cast<IMenuInterface>(GetGameInstance()); 
	return true; 
}

void UMainMenu::UserClickedHost()
{
	if(MenuInterface)
	{
		MenuInterface->Host(); 
	}
}

void UMainMenu::UserClickedJoin()
{
}
