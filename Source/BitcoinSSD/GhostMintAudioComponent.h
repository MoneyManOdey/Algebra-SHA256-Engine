// GhostMintAudioComponent.h
#pragma once
#include "Components/AudioComponent.h"
#include "GhostMintAudioComponent.generated.h"

UCLASS(ClassGroup=Audio, meta=(BlueprintSpawnableComponent))
class UGhostMintAudioComponent : public UAudioComponent {
    GENERATED_BODY()
public:
    UGhostMintAudioComponent();
    /** Play build TX sound */
    UFUNCTION(BlueprintCallable, Category="GhostMint|Audio")
    void PlayBuildTxSound();
    /** Play block inject sound */
    UFUNCTION(BlueprintCallable, Category="GhostMint|Audio")
    void PlayInjectBlockSound();
protected:
    virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GhostMint|Audio")
    USoundWave* BuildTxSound;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GhostMint|Audio")
    USoundWave* InjectBlockSound;
};
