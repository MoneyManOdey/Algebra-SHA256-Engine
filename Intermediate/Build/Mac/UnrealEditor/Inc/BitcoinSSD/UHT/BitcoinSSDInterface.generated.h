// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BitcoinSSDInterface.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FTxInput;
struct FTxOutput;
#ifdef BITCOINSSD_BitcoinSSDInterface_generated_h
#error "BitcoinSSDInterface.generated.h already included, missing '#pragma once' in BitcoinSSDInterface.h"
#endif
#define BITCOINSSD_BitcoinSSDInterface_generated_h

#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_9_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTxInput_Statics; \
	BITCOINSSD_API static class UScriptStruct* StaticStruct();


template<> BITCOINSSD_API UScriptStruct* StaticStruct<struct FTxInput>();

#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_20_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTxOutput_Statics; \
	BITCOINSSD_API static class UScriptStruct* StaticStruct();


template<> BITCOINSSD_API UScriptStruct* StaticStruct<struct FTxOutput>();

#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execBuildTransaction);


#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBitcoinSSDInterface(); \
	friend struct Z_Construct_UClass_UBitcoinSSDInterface_Statics; \
public: \
	DECLARE_CLASS(UBitcoinSSDInterface, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/BitcoinSSD"), NO_API) \
	DECLARE_SERIALIZER(UBitcoinSSDInterface)


#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBitcoinSSDInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UBitcoinSSDInterface(UBitcoinSSDInterface&&); \
	UBitcoinSSDInterface(const UBitcoinSSDInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBitcoinSSDInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBitcoinSSDInterface); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBitcoinSSDInterface) \
	NO_API virtual ~UBitcoinSSDInterface();


#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_27_PROLOG
#define FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_INCLASS_NO_PURE_DECLS \
	FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BITCOINSSD_API UClass* StaticClass<class UBitcoinSSDInterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_oliverodusanya_aci_pow_Source_BitcoinSSD_BitcoinSSDInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
