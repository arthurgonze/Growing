// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROWING_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool toggle);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere) 
	FVector move_offset;

	UPROPERTY(EditAnywhere) 
	float move_time;
	
	UPROPERTY(EditAnywhere) 
	float distance_tolerance = 0.1f;

	bool should_move_to_target = false;

	FVector original_location;
	float speed;

	void MoveToTarget(float DeltaTime, FVector target_location);	
};
