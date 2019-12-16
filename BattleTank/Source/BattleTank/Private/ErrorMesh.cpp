// Fill out your copyright notice in the Description page of Project Settings.


#include "ErrorMesh.h"

// Sets default values
AErrorMesh::AErrorMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticTry = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticTry"));
}

// Called when the game starts or when spawned
void AErrorMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AErrorMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

