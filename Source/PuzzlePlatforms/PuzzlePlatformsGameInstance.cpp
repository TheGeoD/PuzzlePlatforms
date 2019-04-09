// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Contructor"));
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class; 
	}
	
}

void UPuzzlePlatformsGameInstance::Init()
{

	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/Maps/Menu");
	}
}


void UPuzzlePlatformsGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		//Changing controls to game controls from UI controls
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}

}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		//Changing controls to game controls from UI controls
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
		if (Menu)
		{
			Menu->AddToViewport();
		}
		FInputModeUIOnly InputMode;

		InputMode.SetWidgetToFocus(Menu->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}
