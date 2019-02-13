// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventLawang);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
		FEventLawang OnRequestMbukakLawang;


	UPROPERTY(BlueprintAssignable)
		FEventLawang OnNutupLawang;

private:
		UPROPERTY(EditAnywhere)
			ATriggerVolume* PresurePlate = nullptr;

		UPROPERTY(EditAnywhere)
			float BeratTotalBenBsMbukak = 30.0f;

		AActor* Owner;

		float GetTotalBeratYgAdaDiTriggerVolume();
};
