// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BitcoinSSD/BitcoinSSDInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBitcoinSSDInterface() {}

// Begin Cross Module References
BITCOINSSD_API UClass* Z_Construct_UClass_UBitcoinSSDInterface();
BITCOINSSD_API UClass* Z_Construct_UClass_UBitcoinSSDInterface_NoRegister();
BITCOINSSD_API UScriptStruct* Z_Construct_UScriptStruct_FTxInput();
BITCOINSSD_API UScriptStruct* Z_Construct_UScriptStruct_FTxOutput();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
UPackage* Z_Construct_UPackage__Script_BitcoinSSD();
// End Cross Module References

// Begin ScriptStruct FTxInput
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TxInput;
class UScriptStruct* FTxInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TxInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TxInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTxInput, (UObject*)Z_Construct_UPackage__Script_BitcoinSSD(), TEXT("TxInput"));
	}
	return Z_Registration_Info_UScriptStruct_TxInput.OuterSingleton;
}
template<> BITCOINSSD_API UScriptStruct* StaticStruct<FTxInput>()
{
	return FTxInput::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTxInput_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TxId_MetaData[] = {
		{ "Category", "GhostMint" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[] = {
		{ "Category", "GhostMint" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[] = {
		{ "Category", "GhostMint" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_TxId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Amount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTxInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_TxId = { "TxId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTxInput, TxId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TxId_MetaData), NewProp_TxId_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTxInput, Index), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Index_MetaData), NewProp_Index_MetaData) };
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTxInput, Amount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Amount_MetaData), NewProp_Amount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTxInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_TxId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_Index,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTxInput_Statics::NewProp_Amount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxInput_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTxInput_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
	nullptr,
	&NewStructOps,
	"TxInput",
	Z_Construct_UScriptStruct_FTxInput_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxInput_Statics::PropPointers),
	sizeof(FTxInput),
	alignof(FTxInput),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxInput_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTxInput_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTxInput()
{
	if (!Z_Registration_Info_UScriptStruct_TxInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TxInput.InnerSingleton, Z_Construct_UScriptStruct_FTxInput_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TxInput.InnerSingleton;
}
// End ScriptStruct FTxInput

// Begin ScriptStruct FTxOutput
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TxOutput;
class UScriptStruct* FTxOutput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TxOutput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TxOutput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTxOutput, (UObject*)Z_Construct_UPackage__Script_BitcoinSSD(), TEXT("TxOutput"));
	}
	return Z_Registration_Info_UScriptStruct_TxOutput.OuterSingleton;
}
template<> BITCOINSSD_API UScriptStruct* StaticStruct<FTxOutput>()
{
	return FTxOutput::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTxOutput_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Address_MetaData[] = {
		{ "Category", "GhostMint" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[] = {
		{ "Category", "GhostMint" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Address;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_Amount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTxOutput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTxOutput_Statics::NewProp_Address = { "Address", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTxOutput, Address), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Address_MetaData), NewProp_Address_MetaData) };
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FTxOutput_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTxOutput, Amount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Amount_MetaData), NewProp_Amount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTxOutput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTxOutput_Statics::NewProp_Address,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTxOutput_Statics::NewProp_Amount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxOutput_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTxOutput_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
	nullptr,
	&NewStructOps,
	"TxOutput",
	Z_Construct_UScriptStruct_FTxOutput_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxOutput_Statics::PropPointers),
	sizeof(FTxOutput),
	alignof(FTxOutput),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTxOutput_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTxOutput_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTxOutput()
{
	if (!Z_Registration_Info_UScriptStruct_TxOutput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TxOutput.InnerSingleton, Z_Construct_UScriptStruct_FTxOutput_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TxOutput.InnerSingleton;
}
// End ScriptStruct FTxOutput

// Begin Class UBitcoinSSDInterface Function BuildTransaction
struct Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics
{
	struct BitcoinSSDInterface_eventBuildTransaction_Parms
	{
		TArray<FTxInput> Inputs;
		TArray<FTxOutput> Outputs;
		int64 FeeSatoshis;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GhostMint" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * Build a raw Bitcoin transaction hex from inputs, outputs and fee.\n     */" },
#endif
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Build a raw Bitcoin transaction hex from inputs, outputs and fee." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Inputs_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Outputs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Inputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Inputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Outputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Outputs;
	static const UECodeGen_Private::FInt64PropertyParams NewProp_FeeSatoshis;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Inputs_Inner = { "Inputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTxInput, METADATA_PARAMS(0, nullptr) }; // 4059968986
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Inputs = { "Inputs", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BitcoinSSDInterface_eventBuildTransaction_Parms, Inputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Inputs_MetaData), NewProp_Inputs_MetaData) }; // 4059968986
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Outputs_Inner = { "Outputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTxOutput, METADATA_PARAMS(0, nullptr) }; // 2563818840
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Outputs = { "Outputs", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BitcoinSSDInterface_eventBuildTransaction_Parms, Outputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Outputs_MetaData), NewProp_Outputs_MetaData) }; // 2563818840
const UECodeGen_Private::FInt64PropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_FeeSatoshis = { "FeeSatoshis", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BitcoinSSDInterface_eventBuildTransaction_Parms, FeeSatoshis), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BitcoinSSDInterface_eventBuildTransaction_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Inputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Inputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Outputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_Outputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_FeeSatoshis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBitcoinSSDInterface, nullptr, "BuildTransaction", nullptr, nullptr, Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::BitcoinSSDInterface_eventBuildTransaction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::BitcoinSSDInterface_eventBuildTransaction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBitcoinSSDInterface::execBuildTransaction)
{
	P_GET_TARRAY_REF(FTxInput,Z_Param_Out_Inputs);
	P_GET_TARRAY_REF(FTxOutput,Z_Param_Out_Outputs);
	P_GET_PROPERTY(FInt64Property,Z_Param_FeeSatoshis);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UBitcoinSSDInterface::BuildTransaction(Z_Param_Out_Inputs,Z_Param_Out_Outputs,Z_Param_FeeSatoshis);
	P_NATIVE_END;
}
// End Class UBitcoinSSDInterface Function BuildTransaction

// Begin Class UBitcoinSSDInterface
void UBitcoinSSDInterface::StaticRegisterNativesUBitcoinSSDInterface()
{
	UClass* Class = UBitcoinSSDInterface::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "BuildTransaction", &UBitcoinSSDInterface::execBuildTransaction },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBitcoinSSDInterface);
UClass* Z_Construct_UClass_UBitcoinSSDInterface_NoRegister()
{
	return UBitcoinSSDInterface::StaticClass();
}
struct Z_Construct_UClass_UBitcoinSSDInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "BitcoinSSDInterface.h" },
		{ "ModuleRelativePath", "BitcoinSSDInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBitcoinSSDInterface_BuildTransaction, "BuildTransaction" }, // 3368066998
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBitcoinSSDInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBitcoinSSDInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_BitcoinSSD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBitcoinSSDInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBitcoinSSDInterface_Statics::ClassParams = {
	&UBitcoinSSDInterface::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBitcoinSSDInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UBitcoinSSDInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBitcoinSSDInterface()
{
	if (!Z_Registration_Info_UClass_UBitcoinSSDInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBitcoinSSDInterface.OuterSingleton, Z_Construct_UClass_UBitcoinSSDInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBitcoinSSDInterface.OuterSingleton;
}
template<> BITCOINSSD_API UClass* StaticClass<UBitcoinSSDInterface>()
{
	return UBitcoinSSDInterface::StaticClass();
}
UBitcoinSSDInterface::UBitcoinSSDInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBitcoinSSDInterface);
UBitcoinSSDInterface::~UBitcoinSSDInterface() {}
// End Class UBitcoinSSDInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTxInput::StaticStruct, Z_Construct_UScriptStruct_FTxInput_Statics::NewStructOps, TEXT("TxInput"), &Z_Registration_Info_UScriptStruct_TxInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTxInput), 4059968986U) },
		{ FTxOutput::StaticStruct, Z_Construct_UScriptStruct_FTxOutput_Statics::NewStructOps, TEXT("TxOutput"), &Z_Registration_Info_UScriptStruct_TxOutput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTxOutput), 2563818840U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBitcoinSSDInterface, UBitcoinSSDInterface::StaticClass, TEXT("UBitcoinSSDInterface"), &Z_Registration_Info_UClass_UBitcoinSSDInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBitcoinSSDInterface), 2805650588U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_2381136990(TEXT("/Script/BitcoinSSD"),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
