// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define VARIABELBERUBAH

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
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PresurePlate) {
		UE_LOG(LogTemp, Error, (TEXT("PresurePlate is Null in %s")), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenTheDoor(){
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseTheDoor() {
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (PresurePlate->IsOverlappingActor(ActorThatOpens)) {
	//	OpenTheDoor();
	//	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	//}

	if (GetTotalBeratYgAdaDiTriggerVolume() > 30.0f) {
		OpenTheDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseTheDoor();
	}
}

float UOpenDoor::GetTotalBeratYgAdaDiTriggerVolume()
{
	float TotalMass = 0.0f;
	TArray<AActor*> overlappingActor;
	if (!PresurePlate) {
		return TotalMass;
	}
	PresurePlate->GetOverlappingActors(VARIABELBERUBAH overlappingActor);

	for (const auto& Aktor : overlappingActor) {
		TotalMass += Aktor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

