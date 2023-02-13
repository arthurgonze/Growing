// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(physics_handle && physics_handle->GetGrabbedComponent()){
		FVector target_location = GetComponentLocation() + (GetForwardVector() * hold_distance);
		physics_handle->SetTargetLocationAndRotation(target_location, GetComponentRotation());
	}
}


void UGrabber::Grab(){
	physics_handle = GetPhysicsHandle();
	if(physics_handle == nullptr) return;

	FHitResult hit_result;
	if(GetGrabbableInReach(hit_result))
	{
		hit_result.GetComponent()->SetSimulatePhysics(true);
		hit_result.GetComponent()->WakeAllRigidBodies();

		AActor* hit_actor = hit_result.GetActor();
		hit_actor->Tags.Add("Grabbed");
		hit_actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		physics_handle->GrabComponentAtLocationWithRotation(
			hit_result.GetComponent(),
			NAME_None,
			hit_result.ImpactPoint,
			GetComponentRotation());
	}
}
void UGrabber::Release(){
	if(physics_handle && physics_handle->GetGrabbedComponent()){
		physics_handle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		physics_handle->ReleaseComponent();
	}
}

inline UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!result)
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	return result;
}

bool UGrabber::GetGrabbableInReach(FHitResult &out_hit) const{
	FVector line_start, line_end;
	line_start = GetComponentLocation();
	line_end = line_start + (GetForwardVector() * max_grab_distance);

	FCollisionShape sphere = FCollisionShape::MakeSphere(grab_radius);
	
	return GetWorld()->SweepSingleByChannel(out_hit, line_start, line_end, FQuat::Identity, ECC_GameTraceChannel2, sphere);
}
