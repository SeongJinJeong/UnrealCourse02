// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	this->StartLoc = this->GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currLoc = this->GetActorLocation();
	//currLoc = currLoc + this->MovingVelocity * DeltaTime;
	currLoc += this->MovingVelocity * DeltaTime;
	this->SetActorLocation(currLoc);
	float distance = FVector::Dist(StartLoc, currLoc);
	if (distance > this->MoveDistance) {
		FVector direction = this->MovingVelocity.GetSafeNormal();
		FVector nextStartLoc = this->StartLoc + direction * this->MoveDistance;
		this->SetActorLocation(nextStartLoc);
		this->StartLoc = nextStartLoc;
		this->MovingVelocity = -(this->MovingVelocity);
		return;
	}
}