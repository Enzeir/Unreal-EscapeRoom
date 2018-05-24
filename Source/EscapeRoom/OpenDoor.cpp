// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a Trigger Volume!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//Poll the trigger Volume
	//if the mass of the objects in the volume is greater than an amount then the door opens
	if (GetMassOfActorOnPlate() > MassToOpen) 
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if ((GetWorld()->GetTimeSeconds() - lastDoorOpenTime) >= doorCloseDelay )
	{
		CloseDoor();
	}
}

void UOpenDoor::CloseDoor()
{

	owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


float UOpenDoor::GetMassOfActorOnPlate()
{
	float TotalMass = 0.f;

	//find the overlapping actors
	if (!PressurePlate) { return TotalMass; }
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Add the mass of the actors.
	for (const auto* it : OverlappingActors)
	{
		TotalMass += it->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}


	return TotalMass;
}
