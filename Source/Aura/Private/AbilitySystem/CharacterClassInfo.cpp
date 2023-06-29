// Copyright Reaper XeS


#include "AbilitySystem/CharacterClassInfo.h"

TSubclassOf<UGameplayEffect> UCharacterClassInfo::GetPrimaryAttributes(const ECharacterClass CharacterClass)
{
	return GetClassDefaultInfo(CharacterClass).PrimaryAttributes;
}

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
