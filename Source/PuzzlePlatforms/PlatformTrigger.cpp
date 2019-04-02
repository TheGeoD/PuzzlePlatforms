// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"
#include "PuzzlePlatformsCharacter.h"
// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APuzzlePlatformsCharacter* TriggeringCharacter = Cast<APuzzlePlatformsCharacter>(OtherActor); //Verify that it's a character activating the trigger; 
	if(!TriggeringCharacter)
	{
		return; 
	}
	for(AMovingPlatform* MoPlat : PlatformToTriggers)
	{
		if(MoPlat)
		{
			MoPlat->AddActiveTrigger();
		}
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APuzzlePlatformsCharacter* TriggeringCharacter = Cast<APuzzlePlatformsCharacter>(OtherActor); //Verify that it's a character activating the trigger; 
	if (!TriggeringCharacter)
	{
		return; 
	}
	for (AMovingPlatform* MoPlat : PlatformToTriggers)
	{
		if (MoPlat)
		{
			MoPlat->RemoveActiveTrigger(); 
		}
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

