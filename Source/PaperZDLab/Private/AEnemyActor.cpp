#include "AEnemyActor.h"

void AEnemyActor::BeginPlay()
{
  Super::BeginPlay();

  this->setupAIController();
}

void AEnemyActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

AEnemyActor::AEnemyActor() {}