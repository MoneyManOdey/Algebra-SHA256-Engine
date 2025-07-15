#include "BitcoinSSDInterface.h"
#include "Misc/FeedbackContext.h"
#include "Misc/CommandLine.h"

FString UBitcoinSSDInterface::BuildTransaction(const TArray<FTxInput>& Inputs,
                                               const TArray<FTxOutput>& Outputs,
                                               int64 FeeSatoshis)
{
    // TODO: call out to ghostmint_stage2.go or btcd RPC to build a real TX
    // For now, stub returns empty transaction hex
    return FString();
}
