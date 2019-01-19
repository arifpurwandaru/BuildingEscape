// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#define JANGKRIK

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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerVector;
	FRotator PlayerRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		JANGKRIK PlayerVector,
		JANGKRIK PlayerRotator
	);


	/*UE_LOG(LogTemp, Warning, TEXT("Vector: %s  Rotator: %s"), 
		*PlayerVector.ToString(), 
		*PlayerRotator.ToString());*/

	FVector LineEnd = PlayerVector + PlayerRotator.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerVector, LineEnd, FColor(255, 0, 0), false, 0.f, 0.f,10.f);


	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		JANGKRIK Hit,
		PlayerVector,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameter
	);
	AActor* ActorHit = Hit.GetActor();
	if(ActorHit){
		UE_LOG(LogTemp, Warning, TEXT("Nabrak: %s"), *(ActorHit->GetName()) );
	}
	
}

