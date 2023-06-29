// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};
/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
public:
	FORCEINLINE TArray<TSubclassOf<UGameplayAbility>> GetCommonAbilities() const { return CommonAbilities; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetSecondaryAttributes() const { return SecondaryAttributes; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetVitalAttributes() const { return VitalAttributes; }

	TSubclassOf<UGameplayEffect> GetPrimaryAttributes(const ECharacterClass CharacterClass);
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

	
	
};
