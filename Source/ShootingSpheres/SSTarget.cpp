// Fill out your copyright notice in the Description page of Project Settings.


#include "SSTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "ShootingSpheresProjectile.h"

// Sets default values
ASSTarget::ASSTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh component 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	Mesh->BodyInstance.SetCollisionProfileName("BlockAll");
	Mesh->OnComponentHit.AddDynamic(this, &ASSTarget::OnHit);
}


void ASSTarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Destroy sphere if hit by projectile
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && Cast<AShootingSpheresProjectile>(OtherActor))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Emitter, FTransform(Mesh->GetComponentTransform()));
		Destroy();
	}
}

void ASSTarget::SetRight(bool bRight)
{
	bIsRight = bRight;
}

bool ASSTarget::GetRight()
{
	return bIsRight;
}


// Called when the game starts or when spawned
void ASSTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

