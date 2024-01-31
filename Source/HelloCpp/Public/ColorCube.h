// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColorCube.generated.h"

UENUM(BlueprintType)
enum class EColorType : uint8
{
	Color_None  UMETA(DisplayName = "None"),
	Color_Red  UMETA(DisplayName = "Red"),
	Color_Blue UMETA(DisplayName = "Blue"),
	Color_Green UMETA(DisplayName = "Green"),
};

UENUM(BlueprintType)
enum class EWeightClass : uint8
{
	Weight_Light  UMETA(DisplayName = "Light"),
	Weight_Medium  UMETA(DisplayName = "Medium"),
	Weight_Heavy UMETA(DisplayName = "Heavy"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOCPP_API UColorCube : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorCube();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EColorType Color;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
