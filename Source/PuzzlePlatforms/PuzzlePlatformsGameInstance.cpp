// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Contructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));

}

void UPuzzlePlatformsGameInstance::Host()
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));
	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");

// 	UWorld* World = GetWorld();
// 	if(World)
// 	{
// 		World->ServerTravel(""); 
// 	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute); 
	}
}
