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
	UE_LOG(LogTemp,Display,TEXT(""))
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->MovePlatform(DeltaTime);
	this->RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float dt) 
{
	FVector currLoc = this->GetActorLocation();
	
	if (this->shouldPlatformReturn(currLoc) == true) {
		FVector direction = this->MovingVelocity.GetSafeNormal();
		FVector nextStartLoc = this->StartLoc + direction * this->MoveDistance;
		this->SetActorLocation(nextStartLoc);
		this->StartLoc = nextStartLoc;
		this->MovingVelocity = -(this->MovingVelocity);
		return;
	}

	currLoc += this->GetDistanceMoved(dt);
	this->SetActorLocation(currLoc);
}

bool AMovingPlatform::shouldPlatformReturn(FVector currLoc) {
	float distance = FVector::Dist(StartLoc, currLoc);
	return distance > this->MoveDistance;
}

FVector AMovingPlatform::GetDistanceMoved(float dt) {
	return this->MovingVelocity * dt;
}

void AMovingPlatform::RotatePlatform(float dt) 
{
	FString rotate = this->GetActorRotation().ToString();
	UE_LOG(LogTemp, Display, TEXT("Delta Time : %f \nCurrent Rotation : %s"), dt, *rotate);
}