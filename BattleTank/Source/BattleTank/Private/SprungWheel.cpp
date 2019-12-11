// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassAxleConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstrain"));
	SetRootComponent(MassAxleConstrain);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetSimulatePhysics(true);
	Axle->SetupAttachment(MassAxleConstrain);

	AxleWheelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstrain"));
	AxleWheelConstrain->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraints();
}

void ASprungWheel::SetupConstraints()
{
	if (!ensure(GetAttachParentActor()))
		return;

	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	MassAxleConstrain->SetConstrainedComponents(Tank, NAME_None, Axle, NAME_None);

	AxleWheelConstrain->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

