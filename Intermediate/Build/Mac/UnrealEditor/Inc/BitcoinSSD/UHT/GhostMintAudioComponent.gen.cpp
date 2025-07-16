// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BitcoinSSD/GhostMintAudioComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGhostMintAudioComponent() {}

// Begin Cross Module References
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintAudioComponent();
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent();
ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
UPackage* Z_Construct_UPackage__Script_BitcoinSSD();
// End Cross Module References

// Begin Class UGhostMintAudioComponent Function PlayBuildTxSound
struct Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GhostMint|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Play build TX sound */" },
#endif
		{ "ModuleRelativePath", "GhostMintAudioComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Play build TX sound" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGhostMintAudioComponent, nullptr, "PlayBuildTxSound", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGhostMintAudioComponent::execPlayBuildTxSound)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayBuildTxSound();
	P_NATIVE_END;
}
// End Class UGhostMintAudioComponent Function PlayBuildTxSound

// Begin Class UGhostMintAudioComponent Function PlayInjectBlockSound
struct Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GhostMint|Audio" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Play block inject sound */" },
#endif
		{ "ModuleRelativePath", "GhostMintAudioComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Play block inject sound" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGhostMintAudioComponent, nullptr, "PlayInjectBlockSound", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGhostMintAudioComponent::execPlayInjectBlockSound)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PlayInjectBlockSound();
	P_NATIVE_END;
}
// End Class UGhostMintAudioComponent Function PlayInjectBlockSound

// Begin Class UGhostMintAudioComponent
void UGhostMintAudioComponent::StaticRegisterNativesUGhostMintAudioComponent()
{
	UClass* Class = UGhostMintAudioComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "PlayBuildTxSound", &UGhostMintAudioComponent::execPlayBuildTxSound },
		{ "PlayInjectBlockSound", &UGhostMintAudioComponent::execPlayInjectBlockSound },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGhostMintAudioComponent);
UClass* Z_Construct_UClass_UGhostMintAudioComponent_NoRegister()
{
	return UGhostMintAudioComponent::StaticClass();
}
struct Z_Construct_UClass_UGhostMintAudioComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Audio" },
		{ "HideCategories", "Object ActorComponent Physics Rendering Mobility LOD PhysicsVolume" },
		{ "IncludePath", "GhostMintAudioComponent.h" },
		{ "ModuleRelativePath", "GhostMintAudioComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildTxSound_MetaData[] = {
		{ "Category", "GhostMint|Audio" },
		{ "ModuleRelativePath", "GhostMintAudioComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InjectBlockSound_MetaData[] = {
		{ "Category", "GhostMint|Audio" },
		{ "ModuleRelativePath", "GhostMintAudioComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BuildTxSound;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InjectBlockSound;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGhostMintAudioComponent_PlayBuildTxSound, "PlayBuildTxSound" }, // 227864739
		{ &Z_Construct_UFunction_UGhostMintAudioComponent_PlayInjectBlockSound, "PlayInjectBlockSound" }, // 116391804
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGhostMintAudioComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintAudioComponent_Statics::NewProp_BuildTxSound = { "BuildTxSound", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintAudioComponent, BuildTxSound), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildTxSound_MetaData), NewProp_BuildTxSound_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintAudioComponent_Statics::NewProp_InjectBlockSound = { "InjectBlockSound", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintAudioComponent, InjectBlockSound), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InjectBlockSound_MetaData), NewProp_InjectBlockSound_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGhostMintAudioComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintAudioComponent_Statics::NewProp_BuildTxSound,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintAudioComponent_Statics::NewProp_InjectBlockSound,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintAudioComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGhostMintAudioComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAudioComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintAudioComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGhostMintAudioComponent_Statics::ClassParams = {
	&UGhostMintAudioComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGhostMintAudioComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintAudioComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintAudioComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGhostMintAudioComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGhostMintAudioComponent()
{
	if (!Z_Registration_Info_UClass_UGhostMintAudioComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGhostMintAudioComponent.OuterSingleton, Z_Construct_UClass_UGhostMintAudioComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGhostMintAudioComponent.OuterSingleton;
}
template<> BITCOINSSD_API UClass* StaticClass<UGhostMintAudioComponent>()
{
	return UGhostMintAudioComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGhostMintAudioComponent);
UGhostMintAudioComponent::~UGhostMintAudioComponent() {}
// End Class UGhostMintAudioComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintAudioComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGhostMintAudioComponent, UGhostMintAudioComponent::StaticClass, TEXT("UGhostMintAudioComponent"), &Z_Registration_Info_UClass_UGhostMintAudioComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGhostMintAudioComponent), 2110064981U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintAudioComponent_h_390488718(TEXT("/Script/BitcoinSSD"),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintAudioComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintAudioComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
