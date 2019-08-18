// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"



void UServerRow::Setup(UMainMenu* Parent, FServerData ServerName, int32 Index)
{
	this->ServerName->SetText(FText::FromString(ServerName.Name));
	FString ConnectionFractionString = (FString::FromInt(ServerName.CurrentPlayers) + 
		("/") + FString::FromInt(ServerName.MaxPlayers)); 
	this->ConnectionFraction->SetText(FText::FromString(ConnectionFractionString));
	this->HostUser->SetText(FText::FromString(ServerName.OwnerName)); 
	this->Parent = Parent;
	this->Index = Index; 
}

bool UServerRow::Initialize()
{
	bool Success = Super::Initialize(); 
	if(!Success)
	{
		return false; 
	}
	if(ServerSelectRowButton)
	{
		ServerSelectRowButton->OnClicked.AddDynamic(this, &UServerRow::UserClickedHere); 
	}
	return true; 
}

void UServerRow::UserClickedHere()
{
	Parent->SelectIndex(Index);
}

