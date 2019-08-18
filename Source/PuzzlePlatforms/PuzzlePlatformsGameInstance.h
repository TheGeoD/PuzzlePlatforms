// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
class UUserWidget; 
class UMainMenu;
class UGameOverlayMenu;
class IOnlineSubsystem; 
class FOnlineSessionSearch; 
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public: 
	UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer); 

	virtual void Init() override;
	

	UFUNCTION()
	virtual void Host(FString Name) override;


	UFUNCTION()
	virtual void Join(uint32 Index) override;
	/**Called from the Game instance Begin Play function to load the main menu*/ 
 	UFUNCTION(BlueprintCallable)
 	void LoadMenu(); 
	/** Builds the overlay menu*/
	UFUNCTION(BlueprintCallable)
	void ShowOverlay(); 
	/** Builds the main menu*/
	virtual void LoadMainMenu(); 
	/**Calls upon the menu to refresh the list of available Sessions*/
	virtual void RequestRefresh() override;

	void StartSession(); 


private: 
	TSubclassOf<UUserWidget> MenuClass;

	UPROPERTY()
	UMainMenu* Menu;

	TSubclassOf<UUserWidget> OverlayClass;

	IOnlineSubsystem* Subsystem;

	IOnlineSessionPtr SessionInterface; 

	/** Delegate function called on creation of Online Session */ 
	void OnCreateSessionComplete(FName SessionName, bool bSucceeded);
	/** Delegate function called on Destruction of Online Session */
	void OnDestroySessionComplete(FName SessionName, bool bSucceeded);
	/** Delegate function called when a search for Online Sessions is complete */
	void OnFindSessionComplete(bool bSucceeded);
	/**Creates an Online Session using the designated Online Subystem*/
	void CreateSession(); 

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FString CustomServerName; 
};
