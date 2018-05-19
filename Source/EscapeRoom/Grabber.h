// Fill out your copyright notice in the Description page of Project Settings.
//Used to grab some items on the scene
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float reach = 100.0f;
	UInputComponent* InputComponent = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	//method to grab the item
	void Grab();
	//method to release the item that was grabbed
	void Release();

	//methods to get the components from the owner
	void FindPhysicHandleComponent();
	void FindInputComponent();

	//method to detect the object within grabing reach of the player
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return the position of the player
	FVector GetReachTraceStart() const;

	//returns the end of the reach of the grabber
	FVector GetReachTraceEnd() const;

};
