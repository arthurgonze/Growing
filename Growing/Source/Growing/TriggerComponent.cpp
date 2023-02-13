// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Mover.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

    if(puzzle_movable_actor)
        SetMover(puzzle_movable_actor->FindComponentByClass<UMover>());
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(mover == nullptr){
        return;
    }

    AActor *actor = GetKeyActor(); 
    if(actor != nullptr){
        UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
        if(component == nullptr){
            this->AttachToComponent(component,FAttachmentTransformRules::KeepWorldTransform);
            component->SetSimulatePhysics(false);
        }
        mover->SetShouldMove(true);
    }
    else{
        mover->SetShouldMove(false);
    }
}

AActor* UTriggerComponent::GetKeyActor() const
{
    TArray<AActor*> actors;
    GetOverlappingActors(actors);

    for(AActor *actor : actors)
    {
        if(actor->ActorHasTag(key_actor_tag) && !actor->ActorHasTag("Grabbed"))
        {
            return actor;
        }  
    }
        
    
    return nullptr;
}

void UTriggerComponent::SetMover(UMover* newMover)
{
    mover = newMover;
}