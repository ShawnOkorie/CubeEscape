// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorCube.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOCPP_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	
	UPROPERTY(EditAnywhere, Category = "Door Opening")
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere, Category = "Door Opening")
	float closeDelay;

	UPROPERTY(EditAnywhere, Category = "Cube Scale")
	ATriggerVolume* TriggerVolume;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Cube Scale")
	AActor* ValidActors;

    UPROPERTY(EditAnywhere, Category = "Cube Scale")
	EColorType requiredColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Cube Scale")
	float RequiredWeight = 100;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Weight")
	float TotalWeight;
	
	float TotalWeightOfActors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FRotator rotator;
	FRotator targetRot;
	FRotator startRot;
	bool doorTriggered;
	float lastTimeOpened;
	
	
	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
