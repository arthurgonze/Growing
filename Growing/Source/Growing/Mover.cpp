// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	original_location = GetOwner()->GetActorLocation();
	speed = move_offset.Length() / move_time;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(should_move_to_target){
		MoveToTarget(DeltaTime, original_location + move_offset);
	}
	else{
		MoveToTarget(DeltaTime, original_location);
	}
}

void UMover::SetShouldMove(bool toggle)
{
	should_move_to_target = toggle;
}

void UMover::MoveToTarget(float DeltaTime, FVector target_location){
	FVector current_location = GetOwner()->GetActorLocation();

	// if(FVector::Distance(current_location, target_location) < distance_tolerance)
	// 	return;

	FVector new_location = FMath::VInterpConstantTo(current_location, target_location, DeltaTime, speed);
	GetOwner()->SetActorLocation(new_location);
}

