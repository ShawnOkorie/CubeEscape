// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "ColorCube.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerVolume) UE_LOG(LogTemp, Error, TEXT("Trigger Volume is Null"));

	/*
	TArray<TObjectPtr<AActor>>triggerVolumeChildren = TriggerVolume->Children;

	for (TObjectPtr<AActor> Child : triggerVolumeChildren)
	{
		UE_LOG(LogTemp, Warning, TEXT("Child: %s"), Child);
	}*/
	
	ValidActors = GetWorld() -> GetFirstPlayerController() -> GetPawn();
	
	rotator = GetOwner() -> GetActorRotation();
	
	startRot.Yaw = rotator.Yaw;
	targetRot.Yaw = rotator.Yaw + TargetYaw;;
}

void UOpenDoor::OpenDoor()
{
	doorTriggered = true;
	lastTimeOpened = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	doorTriggered = false;
}

float UOpenDoor::TotalWeightOfActors()
{
	TotalWeight = 0;
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->FindComponentByClass<UColorCube>())
		{
			if (Actor->FindComponentByClass<UColorCube>()->Color == requiredColor)
			{
				TotalWeight += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			}
		}
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Weight: %f"), TotalWeight);
	return TotalWeight;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!TriggerVolume) return;

	
	if (RequiredWeight <= TotalWeightOfActors())
		OpenDoor();
		
	else if(GetWorld()->GetTimeSeconds() - lastTimeOpened > closeDelay)
		CloseDoor();

	
	if (!doorTriggered)
	{
		if (rotator.Yaw != startRot.Yaw)
		{
			GetOwner() -> SetActorRotation(startRot);
			rotator = startRot;
		}
	}
	else
	{
		rotator = FMath::Lerp(rotator, targetRot, 1 * DeltaTime);
		GetOwner() -> SetActorRotation(rotator);
	}
}
