// GhostMintInterface.h
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BitcoinSSDInterface.generated.h"

USTRUCT(BlueprintType)
struct FTxInput {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GhostMint")
    FString TxId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GhostMint")
    int32 Index;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GhostMint")
    int64 Amount;
};

USTRUCT(BlueprintType)
struct FTxOutput {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GhostMint")
    FString Address;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GhostMint")
    int64 Amount;
};

UCLASS()
class UBitcoinSSDInterface : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Build a raw Bitcoin transaction hex from inputs, outputs and fee.
     */
    UFUNCTION(BlueprintCallable, Category="GhostMint")
    static FString BuildTransaction(const TArray<FTxInput>& Inputs,
                                     const TArray<FTxOutput>& Outputs,
                                     int64 FeeSatoshis);
};
