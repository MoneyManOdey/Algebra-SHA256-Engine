// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BitcoinSSD/GhostMintVolumeRenderer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGhostMintVolumeRenderer() {}

// Begin Cross Module References
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintVolumeRenderer();
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintVolumeRenderer_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
UPackage* Z_Construct_UPackage__Script_BitcoinSSD();
// End Cross Module References

// Begin Class UGhostMintVolumeRenderer
void UGhostMintVolumeRenderer::StaticRegisterNativesUGhostMintVolumeRenderer()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGhostMintVolumeRenderer);
UClass* Z_Construct_UClass_UGhostMintVolumeRenderer_NoRegister()
{
	return UGhostMintVolumeRenderer::StaticClass();
}
struct Z_Construct_UClass_UGhostMintVolumeRenderer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
		{ "HideCategories", "Mobility VirtualTexture Trigger" },
		{ "IncludePath", "GhostMintVolumeRenderer.h" },
		{ "ModuleRelativePath", "GhostMintVolumeRenderer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VolumeMaterial_MetaData[] = {
		{ "Category", "Rendering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for volumetric rendering */" },
#endif
		{ "ModuleRelativePath", "GhostMintVolumeRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for volumetric rendering" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NodeMesh_MetaData[] = {
		{ "Category", "Rendering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Nanite mesh for block nodes */" },
#endif
		{ "ModuleRelativePath", "GhostMintVolumeRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Nanite mesh for block nodes" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VolumeMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NodeMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGhostMintVolumeRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::NewProp_VolumeMaterial = { "VolumeMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintVolumeRenderer, VolumeMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VolumeMaterial_MetaData), NewProp_VolumeMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::NewProp_NodeMesh = { "NodeMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintVolumeRenderer, NodeMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NodeMesh_MetaData), NewProp_NodeMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::NewProp_VolumeMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::NewProp_NodeMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UPrimitiveComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::ClassParams = {
	&UGhostMintVolumeRenderer::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::Class_MetaDataParams), Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGhostMintVolumeRenderer()
{
	if (!Z_Registration_Info_UClass_UGhostMintVolumeRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGhostMintVolumeRenderer.OuterSingleton, Z_Construct_UClass_UGhostMintVolumeRenderer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGhostMintVolumeRenderer.OuterSingleton;
}
template<> BITCOINSSD_API UClass* StaticClass<UGhostMintVolumeRenderer>()
{
	return UGhostMintVolumeRenderer::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGhostMintVolumeRenderer);
UGhostMintVolumeRenderer::~UGhostMintVolumeRenderer() {}
// End Class UGhostMintVolumeRenderer

// Begin Registration
struct Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintVolumeRenderer_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGhostMintVolumeRenderer, UGhostMintVolumeRenderer::StaticClass, TEXT("UGhostMintVolumeRenderer"), &Z_Registration_Info_UClass_UGhostMintVolumeRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGhostMintVolumeRenderer), 2130208876U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintVolumeRenderer_h_3988458711(TEXT("/Script/BitcoinSSD"),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintVolumeRenderer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_GhostMintVolumeRenderer_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
