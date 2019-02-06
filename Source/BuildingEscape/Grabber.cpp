// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#define BERUBAH

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

	FindPhysicsHandleComponent();

	SetupInputComponent();
	 
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2);
	}
	
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}

}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, (TEXT("PhysicsHandler ora ketemu nang %s")), *(GetOwner()->GetName()))
	}
}


void UGrabber::SetupInputComponent()
{

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("TombolCekel", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("TombolCekel", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, (TEXT("InputComponent ora ketemu nang %s")), *(GetOwner()->GetName()))
	}
}



FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{

	FTwoVectors TracePoints = GetLineTracePoints();

	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		BERUBAH Hit,
		TracePoints.v1,
		TracePoints.v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameter
	);

	return Hit;
}


FTwoVectors UGrabber::GetLineTracePoints() const
{
	FVector StartLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		BERUBAH StartLocation,
		BERUBAH PlayerViewPointRotation
	);
	FVector EndLocation = StartLocation + PlayerViewPointRotation.Vector() * Reach;
	return FTwoVectors(StartLocation, EndLocation);
}


