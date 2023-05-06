// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ALadder::ALadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	SetRootComponent(RootComponent);

	TopArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Top Arrow"));

	TopArrow->SetupAttachment(RootComponent);

	TopArrow->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	BottomArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Bottom Arrow"));

	BottomArrow->SetupAttachment(RootComponent);

	BottomArrow->SetRelativeLocation(FVector(0.f, 0.f, 0.f));	

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));

	CollisionBox->SetupAttachment(RootComponent);

	LadderMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Ladder Mesh"));
}

void ALadder::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    MakeLadder();
}

void ALadder::MakeLadder() 
{	
	
	TArray<UStaticMeshComponent*> StaticMeshComponents;

    // Encontre todos os componentes de StaticMesh no actor
    GetComponents<UStaticMeshComponent>(StaticMeshComponents);

    // Destrua cada componente de StaticMesh encontrado
    for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
    {
        StaticMeshComponent->DestroyComponent();
    }
	
	auto lastIndex = EndOfLadder.Size() / PieceSize;

	for (size_t i = 0; i < lastIndex; i++)
	{
		// Cria o componente de malha estática
		FString Name = "LadderStair_" + FString::FromInt(i);
        UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *Name);

        // Define a malha estática a partir da variável declarada no header
        MeshComponent->SetStaticMesh(LadderMesh);

		MeshComponent->RegisterComponent();

        // Adiciona o componente ao componente raiz do objeto
        MeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -1.0f * i * PieceSize));

		MeshComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}

	CollisionBox->SetBoxExtent(FVector(CollisionBox->GetScaledBoxExtent().X, CollisionBox->GetScaledBoxExtent().Y, (EndOfLadder.Size() / 2) ));

	BottomArrow->SetRelativeLocation(EndOfLadder);

//
	CollisionBox->SetRelativeLocation(FVector(CollisionBox->GetRelativeLocation().X, CollisionBox->GetRelativeLocation().Y, (EndOfLadder.Size() / 2) * -1));
}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ALadder::GetLadderBottom()
{
    return BottomArrow->GetComponentTransform().GetLocation();
}

FVector ALadder::GetLadderTop()
{
    return TopArrow->GetComponentTransform().GetLocation();
}

