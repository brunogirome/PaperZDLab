// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroC.h"

UHeroC::UHeroC()
{
}

 UHeroC::UHeroC(FHeroS heroS)
	 : UActorC(heroS)
 {
	 this->HeroS = heroS;
 }
