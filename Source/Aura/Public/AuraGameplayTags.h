/**
 * Singleton to store all gameplay tags
 * Copyright Reaper XeS
 **/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FAuraGameplayTags
{
 static const FAuraGameplayTags& Get() { return Instance; }
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resilience;
 FGameplayTag Attributes_Primary_Vigor;

 FGameplayTag Attributes_Secondary_Armor;
 FGameplayTag Attributes_Secondary_ArmorPenetration;
 FGameplayTag Attributes_Secondary_BlockChance;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_CriticalHitResistance;
 FGameplayTag Attributes_Secondary_HealthRegeneration;
 FGameplayTag Attributes_Secondary_ManaRegeneration;
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxMana;

 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 FGameplayTag InputTag_5;

 /********************************/
 /* Meta Tags                    */
 /********************************/
 FGameplayTag MetaTag_Damage;

 /********************************/
 /* Effect Tags                  */
 /********************************/
 FGameplayTag Effects_HitReact;
private:
 static FAuraGameplayTags Instance;
};



