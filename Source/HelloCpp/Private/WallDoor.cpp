// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDoor.h"
#include "Grabber.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UWallDoor::UWallDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UWallDoor::TotalWeightOfActors()
{
	TotalWeight = 0;

	if(!TriggerVolume) return TotalWeight;
	
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->FindComponentByClass<UColorCube>())
		{
			if (Actor->FindComponentByClass<UColorCube>())
			{
				TotalWeight += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			}
		}
	}
	
	return TotalWeight;
}

void UWallDoor::BeginOverlap(AActor* overlappedActor, AActor* otherActor)
{
	if (isOpen) return;
	
	if (otherActor->FindComponentByClass<UColorCube>())
	{
		if (otherActor->FindComponentByClass<UColorCube>()->Color == blockedColor)
		{
			if (grabber->MyPhysicsHandle->GrabbedComponent == otherActor->FindComponentByClass<UPrimitiveComponent>())
			{
				if(grabber) grabber->GrabRelease();
			}
			
			otherActor->FindComponentByClass<UPrimitiveComponent>()->AddForce(overlappedActor->GetActorForwardVector()*3000000);
			/*FVector reflect = UKismetMathLibrary::GetReflectionVector(otherActor->GetVelocity(),overlappedActor->GetActorForwardVector())*1000000000;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *overlappedActor->GetActorForwardVector().ToString());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *reflect.ToString());*/
		}	
	}
}

// Called when the game starts
void UWallDoor::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UWallDoor::BeginOverlap);

	grabber = GetWorld() -> GetFirstPlayerController() -> GetPawn() ->FindComponentByClass<UGrabber>();

	if (!grabber) UE_LOG(LogTemp, Error, TEXT("Grabber is Null"));
}

// Called every frame
void UWallDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TriggerVolume) return;

	if (RequiredWeight <= TotalWeightOfActors())
	{
		if (myMesh->GetMaterial(0) != transMat)
		{
			myMesh->SetMaterial(0, transMat);
			isOpen = true;
		}
	}
	else
	{
		if (myMesh->GetMaterial(0) != colorMat)
		{
			myMesh->SetMaterial(0, colorMat);
			isOpen = false;
		}
	}

	
}

