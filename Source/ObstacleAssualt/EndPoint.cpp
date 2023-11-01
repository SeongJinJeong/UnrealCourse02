// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPoint.h"

// Sets default values
AEndPoint::AEndPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->CheckPlayerOnEndPoint();
}

void AEndPoint::CheckPlayerOnEndPoint() {
	FVector MyLoc = this->GetActorLocation();
	FVector PlayerLoc = this->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (MyLoc == PlayerLoc)
		FGenericPlatformMisc::RequestExit(false);
}

