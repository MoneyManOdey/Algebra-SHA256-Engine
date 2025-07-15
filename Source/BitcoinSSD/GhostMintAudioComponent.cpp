// GhostMintAudioComponent.cpp
#include "GhostMintAudioComponent.h"

UGhostMintAudioComponent::UGhostMintAudioComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UGhostMintAudioComponent::BeginPlay() {
    Super::BeginPlay();
}

void UGhostMintAudioComponent::PlayBuildTxSound() {
    if (BuildTxSound) {
        SetSound(BuildTxSound);
        Play();
    }
}

void UGhostMintAudioComponent::PlayInjectBlockSound() {
    if (InjectBlockSound) {
        SetSound(InjectBlockSound);
        Play();
    }
}
