// Copyright Eder


#include "AbilitySystem/ExecCalc/AuraExecCalcDamage.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor); //ThisCreate an ArmorPropertyPointer
	//(1) declare the attribute you need to capture
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target,false);
		//(2) define the attribute you need to capture using macros
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target,false);
	}
};

static const AuraDamageStatics DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UAuraExecCalcDamage::UAuraExecCalcDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	//(3) capture the attribute
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UAuraExecCalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Here we can decide how to change multiple attributes
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// GetDamage set by caller magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	//Capture Blockchance on target
	// If BLOCK, halve the damage
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance,0.f);

	const bool bBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	Damage = bBlocked ? Damage*0.5f : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

