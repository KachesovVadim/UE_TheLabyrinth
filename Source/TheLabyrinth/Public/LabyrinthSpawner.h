// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Logging/LogVerbosity.h"
#include "LabyrinthSpawner.generated.h"


using namespace std;

UCLASS()
class THELABYRINTH_API ALabyrinthSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabyrinthSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Wall;

	void SpawnStaticMeshActor(const FVector& InLocation, const FRotator& ActorRotation);
	UFUNCTION(BlueprintCallable)
	void SpawnWalls(int rows, int cols, FVector LocInWrld);

};
