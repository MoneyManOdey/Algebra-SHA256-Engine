// GhostMintWidget.h
#pragma once
#include "Blueprint/UserWidget.h"
#include "GhostMintWidget.generated.h"

UCLASS()
class UGhostMintWidget : public UUserWidget {
    GENERATED_BODY()
public:
    /** Inputs table widget reference */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UDataTable* InputsTable;
    /** Outputs table widget reference */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UDataTable* OutputsTable;
    /** Fee slider reference */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class USlider* FeeSlider;
    /** Locktime input */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UEditableTextBox* LocktimeBox;
    /** Raw TX hex preview */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UEditableTextBox* TxHexBox;
    /** Build TX button */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UButton* BuildTxButton;
    /** Inject block button */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UButton* InjectBlockButton;
};
