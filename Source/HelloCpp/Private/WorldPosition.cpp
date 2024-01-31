// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//FString ownerName = GetOwner() -> GetActorLabel();
	
	//FString ownerPosition = GetOwner() -> GetActorLocation().ToString();

	//UE_LOG(LogTemp, Error, TEXT("Actor: %s Position: %s") ,*ownerName, *ownerPosition);

	//if (GEngine) GEngine -> AddOnScreenDebugMessage(-1, 5, FColor::Green,*ownerName.Append(" ").Append(*ownerPosition));
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

