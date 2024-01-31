// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorCube.h"
#include "Grabber.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "WallDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOCPP_API UWallDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallDoor();

	UPROPERTY(EditAnywhere, Category = "Wall")
	EColorType blockedColor;
	
	UPROPERTY(EditAnywhere, Category = "Cube Scale")
	ATriggerVolume* TriggerVolume;

	UPROPERTY(EditAnywhere, Category = "Cube Scale")
	EColorType requiredColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Cube Scale")
	float RequiredWeight = 100;
	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Weight")
	float TotalWeight;
	
	float TotalWeightOfActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *colorMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *transMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *myMesh;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UGrabber* grabber = nullptr;
	
	bool isOpen;

	UFUNCTION() void BeginOverlap(AActor* overlappedActor, AActor* otherActor);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
