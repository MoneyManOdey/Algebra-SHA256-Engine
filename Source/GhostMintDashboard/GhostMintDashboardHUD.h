// GhostMintDashboardHUD.h
#pragma once
#include "GameFramework/HUD.h"
#include "GhostMintDashboardHUD.generated.h"

UCLASS()
class AGhostMintDashboardHUD : public AHUD {
    GENERATED_BODY()
public:
    AGhostMintDashboardHUD();
    virtual void DrawHUD() override;
};
