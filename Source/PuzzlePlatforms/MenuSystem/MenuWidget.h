// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	void Setup(); 
	void TearDown(); 
	void ReturnGameInputControl();
	
	virtual bool Initialize() override; 
	void SetMenuInterface(IMenuInterface* MenuInterface);

	IMenuInterface* MenuInterface; 

protected: 
	APlayerController* PlayerController;

};
