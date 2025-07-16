// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BitcoinSSD/GhostMintDashboardHUD.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGhostMintDashboardHUD() {}

// Begin Cross Module References
BITCOINSSD_API UClass* Z_Construct_UClass_AGhostMintDashboardHUD();
BITCOINSSD_API UClass* Z_Construct_UClass_AGhostMintDashboardHUD_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AHUD();
UPackage* Z_Construct_UPackage__Script_BitcoinSSD();
// End Cross Module References

// Begin Class AGhostMintDashboardHUD
void AGhostMintDashboardHUD::StaticRegisterNativesAGhostMintDashboardHUD()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGhostMintDashboardHUD);
UClass* Z_Construct_UClass_AGhostMintDashboardHUD_NoRegister()
{
	return AGhostMintDashboardHUD::StaticClass();
}
struct Z_Construct_UClass_AGhostMintDashboardHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "GhostMintDashboardHUD.h" },
		{ "ModuleRelativePath", "GhostMintDashboardHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGhostMintDashboardHUD>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGhostMintDashboardHUD_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AHUD,
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGhostMintDashboardHUD_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGhostMintDashboardHUD_Statics::ClassParams = {
	&AGhostMintDashboardHUD::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGhostMintDashboardHUD_Statics::Class_MetaDataParams), Z_Construct_UClass_AGhostMintDashboardHUD_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGhostMintDashboardHUD()
{
	if (!Z_Registration_Info_UClass_AGhostMintDashboardHUD.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGhostMintDashboardHUD.OuterSingleton, Z_Construct_UClass_AGhostMintDashboardHUD_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGhostMintDashboardHUD.OuterSingleton;
}
template<> BITCOINSSD_API UClass* StaticClass<AGhostMintDashboardHUD>()
{
	return AGhostMintDashboardHUD::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGhostMintDashboardHUD);
AGhostMintDashboardHUD::~AGhostMintDashboardHUD() {}
// End Class AGhostMintDashboardHUD

// Begin Registration
struct Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintDashboardHUD_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGhostMintDashboardHUD, AGhostMintDashboardHUD::StaticClass, TEXT("AGhostMintDashboardHUD"), &Z_Registration_Info_UClass_AGhostMintDashboardHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGhostMintDashboardHUD), 1955467278U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintDashboardHUD_h_1765338683(TEXT("/Script/BitcoinSSD"),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintDashboardHUD_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintDashboardHUD_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
