// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameState.h"

#include "Kismet/GameplayStatics.h"

#include "MyGameInstance.h"
#include "MyGameMode.h"

#include "PartyManager.h"
#include "Hero.h"

TArray<AHero *> AMyGameState::GetPartyMembers()
{
  return this->gameInstance->PartyManager->Heroes;
}

APartyLeader *AMyGameState::GetPartyLeader()
{
  return this->gameInstance->PartyManager->Leader;
}

TArray<APartyMember *> AMyGameState::GetAIMembers()
{
  return this->gameInstance->PartyManager->AIMembers;
}

// TArray<UEnemyStats *> AMyGameState::GetEnemyPartyMembers()
// {
//   return this->GameMode->EnemyParty;
// }

// TArray<float> AMyGameState::GetATTACK_STRENGTH_ACCURACY()
// {
//   return this->GameInstance->ATTACK_STRENGTH_ACCURACY_BASE;
// }

// TArray<UItemClass *> AMyGameState::GetInventory()
// {
//   return this->GameInstance->Inventory;
// }

TEnumAsByte<CurrentGameState> AMyGameState::GetCurrentGameState()
{
  return this->gameInstance->CurrentGameState;
}

// TEnumAsByte<BattleStateEnum> AMyGameState::GetBattleState()
// {
//   return this->GameMode->BattleState;
// }

// TEnumAsByte<BattleStateEnum> AMyGameState::GetLastBattleState()
// {
//   return this->GameMode->LastBattleState;
// }

// TEnumAsByte<SpellTypeEnum> AMyGameState::GetSpellCastedType()
// {
//   return this->GameMode->CastedSpell->SpellType;
// }

// UCombatActorStats *AMyGameState::GetCurrentActor()
// {
//   return this->GameMode->CurrentActor;
// }

// void AMyGameState::SetBattleState(BattleStateEnum newBattleState)
// {
//   this->GameMode->SetBattleState(newBattleState);
// }

// UHeroStats *AMyGameState::GetHeroByPartyPosition(uint8 position)
// {
//   return (*this->GameMode->HeroParty)[position];
// }

// UEnemyStats *AMyGameState::GetEnemyByPartyPosition(uint8 position)
// {
//   return this->GameMode->EnemyParty[position];
// }

// float AMyGameState::GetActorAccuracyByStrength(uint8 level)
// {
//   return this->GameMode->GetActorAccuracyByStrength(level);
// }

// bool AMyGameState::GetAlreadyAttacked()
// {
//   return this->GameMode->AlreadyAttacked;
// }

// bool AMyGameState::IsPartyBuffActive(PartyBuffTypeEnum partyBuffType)
// {
//   for (FActiveBuffStruct partyBuff : this->GameMode->ActivePartyBuffs)
//   {
//     if (partyBuff.SpellPointer->PartyBuffType == partyBuffType)
//     {
//       return true;
//     }
//   }

//   return false;
// }

void AMyGameState::SetCurrentGameMode(CurrentGameState newCurrentGameState)
{
  this->gameInstance->CurrentGameState = newCurrentGameState;
}

// void AMyGameState::SetEnemyAsTargetByPosition(uint8 enemyPosition)
// {
//   UCombatActorStats *enemy = (UCombatActorStats *)this->GameMode->EnemyParty[enemyPosition];

//   this->GameMode->TargetActor = enemy;
// }

// void AMyGameState::SetHeroAsTargetByName(FString name)
// {
//   int32 heroIndex =
//       (*this->GameMode->HeroParty).IndexOfByPredicate([&](UHeroStats *hero)
//                                                       { return hero->Name == name; });

//   UCombatActorStats *hero = (UCombatActorStats *)(*this->GameMode->HeroParty)[heroIndex];

//   this->GameMode->TargetActor = hero;
// }

// void AMyGameState::SetAttackStrengthChoice(uint8 choice)
// {
//   this->GameMode->AttackStrengthChoice = choice;

//   this->SetBattleState(PHYSICAL_ATTACK);
// }

// void AMyGameState::StartBattle(TArray<FName> enemiesRowNames)
// {
//   this->GameMode->StartBattle(enemiesRowNames);
// }

// void AMyGameState::CastSpell(uint8 position)
// {
//   this->GameMode->CastedSpellPositon = position;

//   this->SetBattleState(SPELL_CAST);
// }

// void AMyGameState::AddItemToInventory(FName itemName, uint8 amount)
// {
//   this->GameInstance->AddItem(itemName, amount);
// }

// void AMyGameState::SelectItemToConsume(uint8 positonOnInventory)
// {
//   this->GameMode->SelectedItem = this->GameInstance->Inventory[positonOnInventory];

//   this->SetBattleState(SELECT_TARGET);
// }

// void AMyGameState::RemoveItemFromInventory(int32 position)
// {
//   this->GameInstance->RemoveItem(position);
// }

// void AMyGameState::ConsumeItemOnInventory(int32 position, UHeroStats *selectedHero)
// {
//   UItemClass *item = this->GameInstance->Inventory[position];

//   switch (item->ConsumableType)
//   {
//   case POTION_HP:
//     selectedHero->HealHp(item->ConsumableHealing);

//     item->Consume();
//     break;
//   }
// }

// void AMyGameState::EquipItem(int32 position, UHeroStats *selectedHero)
// {
//   UItemClass *item = this->GameInstance->Inventory[position];

//   uint8 positionHeroEquipament = selectedHero->Equipaments.Num();

//   FItemStruct *itemStructPointer = this->GameInstance->ItemsDataTable->FindRow<FItemStruct>(FName(item->Name.Replace(TEXT(" "), TEXT(""))), "", true);

//   UItemClass *newItem = NewObject<UItemClass>(UItemClass::StaticClass());

//   newItem->Create(positionHeroEquipament, 1, itemStructPointer, this->GameInstance);

//   newItem->HeroEquipped = selectedHero;

//   item->Consume();

//   selectedHero->Equipaments.Emplace(newItem);

//   selectedHero->CalculateStats();
// }

// void AMyGameState::UnequipItem(int32 position, UHeroStats *selectedHero)
// {
//   UItemClass *item = selectedHero->Equipaments[position];

//   this->GameInstance->AddItem(FName(item->Name.Replace(TEXT(" "), TEXT(""))), 1);

//   selectedHero->Equipaments.RemoveAt(position);

//   for (uint8 i = 0; i < selectedHero->Equipaments.Num(); i++)
//   {
//     UItemClass *equipament = selectedHero->Equipaments[i];

//     equipament->PositionInInventory = i;
//   }
// }

AMyGameState::AMyGameState()
{
  this->gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

  this->gameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}