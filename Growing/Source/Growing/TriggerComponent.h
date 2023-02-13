// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"


class UMover;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROWING_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UTriggerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) 
	void SetMover(UMover* mover);

private:
	UPROPERTY(EditAnywhere) 
	FName key_actor_tag;
	
	UMover* mover;

	UPROPERTY(EditAnywhere) 
	AActor* puzzle_movable_actor;

	AActor* GetKeyActor() const;
};
