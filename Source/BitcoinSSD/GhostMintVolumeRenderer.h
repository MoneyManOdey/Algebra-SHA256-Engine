// GhostMintVolumeRenderer.h
#pragma once
#include "Components/PrimitiveComponent.h"
#include "GhostMintVolumeRenderer.generated.h"

UCLASS(ClassGroup=Rendering, meta=(BlueprintSpawnableComponent))
class UGhostMintVolumeRenderer : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    UGhostMintVolumeRenderer();
    virtual void OnRegister() override;
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
public:
    /** Material for volumetric rendering */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rendering")
    UMaterialInterface* VolumeMaterial;
    /** Nanite mesh for block nodes */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rendering")
    UStaticMesh* NodeMesh;
};
