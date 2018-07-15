// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralTerrain.generated.h"

UCLASS()
class PROJECTCODE_API AProceduralTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralTerrain();

	UPROPERTY(BlueprintReadWrite, Category = "Procedural Terrain")
	TArray<FVector> vertices;

	TArray<int32> triangles;
	//empty arrays
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	UPROPERTY(EditAnywhere)
	UMaterial *Mat;
	UPROPERTY(EditAnywhere)
	int sideSize = 100;
	UPROPERTY(EditAnywhere)
	int size = 5;
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent * mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform & Transform);

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void GetNeighbors(const int vertice, const int depth, TArray<int> &neighbors);

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void UpdateMesh();

	void CreateTriangles();

	
	
};
