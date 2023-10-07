// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorC.h"
#include "ActorS.h"

bool UActorC::isDead()
{
	return this->ActorS.Hp <= 0;
}

UActorC::UActorC()
{
}

UActorC::UActorC(FActorS actorS)
{
	this->ActorS = actorS;
}
