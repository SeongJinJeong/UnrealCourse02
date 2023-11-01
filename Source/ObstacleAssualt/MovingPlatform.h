// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"


UCLASS()
class OBSTACLEASSUALT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="Moving")
	FVector MovingVelocity = FVector(100, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Moving")
	float MoveDistance = 100;

	UPROPERTY(EditAnywhere, Category="Rotating")
	FRotator RotateVelocity;

	UPROPERTY(EditAnywhere, Category="Scaling")
	FVector ScaleVelocity;
	UPROPERTY(EditAnywhere, Category = "Scaling")
	int ScaleSizeMultiple = 1;
	FVector StartScale;

	UPROPERTY(EditAnywhere, Category="Falling")
	float FallingDelay = -1;
	UPROPERTY(VisibleAnywhere, Category = "Falling");
	float FallingElapsedTime = 0;
	UPROPERTY(VisibleAnywhere, Category = "Falling");
	bool isPlatformVisible = true;

	FVector StartLoc;

	void MovePlatform(float dt);
	void RotatePlatform(float dt);
	void ScalePlatform(float dt);
	void FallPlatform(float dt);
	bool shouldPlatformReturn(FVector currLoc) const;
	float GetDistanceMoved() const;
};
