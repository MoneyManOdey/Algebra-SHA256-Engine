// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BitcoinSSD/Public/GhostMintWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGhostMintWidget() {}

// Begin Cross Module References
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintWidget();
BITCOINSSD_API UClass* Z_Construct_UClass_UGhostMintWidget_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UEditableTextBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_USlider_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_BitcoinSSD();
// End Cross Module References

// Begin Class UGhostMintWidget
void UGhostMintWidget::StaticRegisterNativesUGhostMintWidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGhostMintWidget);
UClass* Z_Construct_UClass_UGhostMintWidget_NoRegister()
{
	return UGhostMintWidget::StaticClass();
}
struct Z_Construct_UClass_UGhostMintWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "GhostMintWidget.h" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputsTable_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Inputs table widget reference */" },
#endif
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Inputs table widget reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputsTable_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Outputs table widget reference */" },
#endif
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Outputs table widget reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FeeSlider_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fee slider reference */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fee slider reference" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocktimeBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Locktime input */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Locktime input" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TxHexBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Raw TX hex preview */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Raw TX hex preview" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildTxButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Build TX button */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Build TX button" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InjectBlockButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "GhostMintWidget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Inject block button */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GhostMintWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Inject block button" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputsTable;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OutputsTable;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FeeSlider;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LocktimeBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TxHexBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BuildTxButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InjectBlockButton;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGhostMintWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_InputsTable = { "InputsTable", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, InputsTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputsTable_MetaData), NewProp_InputsTable_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_OutputsTable = { "OutputsTable", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, OutputsTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputsTable_MetaData), NewProp_OutputsTable_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_FeeSlider = { "FeeSlider", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, FeeSlider), Z_Construct_UClass_USlider_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FeeSlider_MetaData), NewProp_FeeSlider_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_LocktimeBox = { "LocktimeBox", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, LocktimeBox), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocktimeBox_MetaData), NewProp_LocktimeBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_TxHexBox = { "TxHexBox", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, TxHexBox), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TxHexBox_MetaData), NewProp_TxHexBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_BuildTxButton = { "BuildTxButton", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, BuildTxButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildTxButton_MetaData), NewProp_BuildTxButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_InjectBlockButton = { "InjectBlockButton", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGhostMintWidget, InjectBlockButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InjectBlockButton_MetaData), NewProp_InjectBlockButton_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGhostMintWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_InputsTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_OutputsTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_FeeSlider,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_LocktimeBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_TxHexBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_BuildTxButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGhostMintWidget_Statics::NewProp_InjectBlockButton,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGhostMintWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGhostMintWidget_Statics::ClassParams = {
	&UGhostMintWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGhostMintWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintWidget_Statics::PropPointers),
	0,
	0x00A010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGhostMintWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UGhostMintWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGhostMintWidget()
{
	if (!Z_Registration_Info_UClass_UGhostMintWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGhostMintWidget.OuterSingleton, Z_Construct_UClass_UGhostMintWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGhostMintWidget.OuterSingleton;
}
template<> BITCOINSSD_API UClass* StaticClass<UGhostMintWidget>()
{
	return UGhostMintWidget::StaticClass();
}
UGhostMintWidget::UGhostMintWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGhostMintWidget);
UGhostMintWidget::~UGhostMintWidget() {}
// End Class UGhostMintWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_Public_GhostMintWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGhostMintWidget, UGhostMintWidget::StaticClass, TEXT("UGhostMintWidget"), &Z_Registration_Info_UClass_UGhostMintWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGhostMintWidget), 3874344036U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_Public_GhostMintWidget_h_2942907127(TEXT("/Script/BitcoinSSD"),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_Public_GhostMintWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_Public_GhostMintWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
