// Copyright Eder


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApply);
}

void UAuraAbilitySystemComponent::EffectApply(UAbilitySystemComponent* AbilitySystemComponent,
                                              const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue,FString("Effect Applied"));
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);

	for(const FGameplayTag& Tag: GameplayTagContainer)
	{
		//TODO: Broadcast the tag to the widget controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,Msg);
	}
}
