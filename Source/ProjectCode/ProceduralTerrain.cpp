#include "ProceduralTerrain.h"



void AProceduralTerrain::BeginPlay()
{
	Super::BeginPlay();

}

void AProceduralTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AProceduralTerrain::AProceduralTerrain()
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true; //multithread cooking
}


void AProceduralTerrain::UpdateMesh()
{
	mesh->UpdateMeshSection_LinearColor(0, vertices, normals, UV0, vertexColors, tangents);
}

//Construction Script
void AProceduralTerrain::OnConstruction(const FTransform & Transform)
{
	CreateTriangles();
	mesh->SetMaterial(0, Mat);
}


void AProceduralTerrain::GetNeighbors(const int vertice, const int depth, TArray<int> &neighbors)
{
	TArray<int> neighborsTemp;
	for (int i = -depth; i <= depth; i++)
	{
		for (int j = -depth; j <= depth; j++) 
		{
			if (vertices.IsValidIndex(vertice + i + (j * (size + 1))))
			{
				neighborsTemp.Add(vertice + i + (j * (size + 1)));
			}
		}
	}
	neighbors = neighborsTemp;
}

void AProceduralTerrain::CreateTriangles()
{
	//fill array
	vertices.Init(FVector(), (size + 1)*(size + 1));
	//set vertices
	for (int i = 0, y = 0; y <= size; y++)
	{
		for (int x = 0; x <= size; x++, i++) 
		{
			vertices[i] = FVector(x*sideSize, y*sideSize, 0);
		}
	}

	//init triangles
	triangles.Init(0, size*size * 6);
	//set traingles
	for (int ti = 0, vi = 0, y = 0; y < size; y++, vi++) {
		for (int x = 0; x < size; x++, ti += 6, vi++) {
			triangles[ti] = vi;
			triangles[ti + 3] = triangles[ti + 2] = vi + 1;
			triangles[ti + 4] = triangles[ti + 1] = vi + size + 1;
			triangles[ti + 5] = vi + size + 2;
		}
	}


	//create mesh
	mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, true);

	//enable collision
	mesh->ContainsPhysicsTriMeshData(true);
}