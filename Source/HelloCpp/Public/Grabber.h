// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOCPP_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	void Grab();
	void GrabRelease();
	FTransform GetPlayerTraceStart();
	FVector GetLineTraceEnd();
	
	UPROPERTY(EditAnywhere)
	float TraceLength = 250;

	UPhysicsHandleComponent* MyPhysicsHandle = nullptr;
	UInputComponent* MyInputComponent = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
