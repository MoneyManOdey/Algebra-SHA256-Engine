// GhostMintVolumeRenderer.cpp
#include "GhostMintVolumeRenderer.h"
#include "PrimitiveSceneProxy.h"

UGhostMintVolumeRenderer::UGhostMintVolumeRenderer() {
    PrimaryComponentTick.bCanEverTick = false;
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGhostMintVolumeRenderer::OnRegister() {
    Super::OnRegister();
    // Setup Nanite
    if (NodeMesh) {
        // NodeMesh->SetNaniteEnabled(true); // TODO: Enable via asset settings
    }
}

FPrimitiveSceneProxy* UGhostMintVolumeRenderer::CreateSceneProxy() {
    // TODO: implement custom scene proxy for volumetric/Nanite rendering
    return nullptr;
}

FBoxSphereBounds UGhostMintVolumeRenderer::CalcBounds(const FTransform& LocalToWorld) const {
    return Super::CalcBounds(LocalToWorld);
}
