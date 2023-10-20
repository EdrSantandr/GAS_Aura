// Copyright Eder


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApply);
}

void UAuraAbilitySystemComponent::EffectApply(UAbilitySystemComponent* AbilitySystemComponent,
                                              const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue,FString("Effect Applied"));
}
