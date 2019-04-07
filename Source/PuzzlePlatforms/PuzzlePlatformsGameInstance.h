// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
class UUserWidget; 
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()
public: 
	UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer); 

	virtual void Init() override;
	


	UFUNCTION(Exec)
	void Host(); 

	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
	void LoadMenu(); 

private: 
	TSubclassOf<UUserWidget> MenuClass; 
};
