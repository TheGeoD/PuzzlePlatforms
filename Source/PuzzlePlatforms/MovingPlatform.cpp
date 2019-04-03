// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "PlatformTrigger.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	PlatformSpeed = 100.f;
	
	bIsTriggerActivated = false; 
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay(); 

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); 
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	if (HasAuthority() && (ActiveTriggers != 0))
	{
		FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		float TargetDistance =(GlobalTargetLocation - GlobalStartLocation).Size(); 
		float DistanceTraveled = (Location - GlobalStartLocation).Size();
		if(DistanceTraveled >= TargetDistance)
		{
			FVector TempGlobalStart = GlobalStartLocation; 
			GlobalStartLocation = GlobalTargetLocation; 
			GlobalTargetLocation = TempGlobalStart;
		}
		Location += (PlatformSpeed * DeltaTime * Direction); 
		SetActorLocation(Location); 
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers += 1; 
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if( ActiveTriggers <= 0)
	{
		return; 
	}
	ActiveTriggers -= 1; 
}
