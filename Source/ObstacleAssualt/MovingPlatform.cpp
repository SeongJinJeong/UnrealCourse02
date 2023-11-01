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
	this->StartScale = this->GetActorScale();
	UE_LOG(LogTemp,Display,TEXT(""))
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->MovePlatform(DeltaTime);
	this->RotatePlatform(DeltaTime);
	this->ScalePlatform(DeltaTime);
	this->FallPlatform(DeltaTime);
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

	currLoc += this->MovingVelocity * dt;
	this->SetActorLocation(currLoc);
}

bool AMovingPlatform::shouldPlatformReturn(FVector currLoc) const {
	float distance = this->GetDistanceMoved();
	return distance > this->MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(this->StartLoc, this->GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float dt) 
{
	this->AddActorLocalRotation(this->RotateVelocity * dt);
}

void AMovingPlatform::ScalePlatform(float dt) {
	if (this->GetActorScale().Y > this->StartScale.Y * this->ScaleSizeMultiple) {
		FVector maximumScale = this->StartScale;
		maximumScale.Y = this->StartScale.Y * this->ScaleSizeMultiple;
		this->SetActorScale3D(maximumScale);

		this->ScaleVelocity.Y = -(this->ScaleVelocity.Y);
	}

	if (this->GetActorScale().Y < this->StartScale.Y) {
		this->SetActorScale3D(this->StartScale);
		this->ScaleVelocity.Y = -(this->ScaleVelocity.Y);
	}

	FVector nextScale = this->GetActorScale() + (this->ScaleVelocity * dt / 100);
	this->SetActorScale3D(nextScale);
}

void AMovingPlatform::FallPlatform(float dt) {
	if (this->FallingDelay < 0)
		return;

	this->FallingElapsedTime += dt;
	if (this->FallingElapsedTime >= this->FallingDelay) {
		this->isPlatformVisible = !this->isPlatformVisible;
		this->SetActorHiddenInGame(this->isPlatformVisible);
		this->SetActorEnableCollision(!this->isPlatformVisible);
		this->FallingElapsedTime = 0;
	}
}