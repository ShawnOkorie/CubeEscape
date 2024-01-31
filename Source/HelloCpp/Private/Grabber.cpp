// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	MyPhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if (!MyPhysicsHandle) UE_LOG(LogTemp, Error, TEXT("No Physics Handlle found!"))

	MyInputComponent = GetOwner()-> FindComponentByClass<UInputComponent>();

	//Setting up Input
	if (!MyInputComponent) 
	{
		UE_LOG(LogTemp, Error, TEXT("No Input Component found!"));
	}
	else
	{
		MyInputComponent -> BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
		MyInputComponent -> BindAction("Grab",IE_Released, this, &UGrabber::GrabRelease);
	}

}

FTransform UGrabber::GetPlayerTraceStart()
{
	FVector PlayerPOVLocation;
	FRotator PlayerPOVRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerPOVLocation,OUT PlayerPOVRotation);
	
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"),*PlayerPOVLocation.ToCompactString(),*PlayerPOVRotation.ToCompactString());

	return FTransform(PlayerPOVRotation,PlayerPOVLocation);
}

FVector UGrabber::GetLineTraceEnd()
{
	return GetPlayerTraceStart().GetLocation() + GetPlayerTraceStart().GetRotation().Vector() * TraceLength;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//DrawDebugLine(GetWorld(),GetPlayerTraceStart().GetLocation(),GetLineTraceEnd(),FColor(0,255,0),false,0,0,0.5f);

	if (MyPhysicsHandle->GrabbedComponent) MyPhysicsHandle->SetTargetLocation(GetLineTraceEnd());
}

void UGrabber::Grab()
{
	
	FHitResult hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld() -> LineTraceSingleByObjectType(OUT hit,GetPlayerTraceStart().GetLocation(),GetLineTraceEnd(),FCollisionObjectQueryParams(ECC_PhysicsBody),TraceParams);
	
	
	if (hit.GetActor())
	{
		MyPhysicsHandle->GrabComponentAtLocation(hit.GetComponent(), NAME_None, GetLineTraceEnd());
	}
}

void UGrabber::GrabRelease()
{
	if (MyPhysicsHandle->GrabbedComponent) MyPhysicsHandle->ReleaseComponent();
}



