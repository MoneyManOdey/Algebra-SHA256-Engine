// GhostMintDashboardHUD.cpp
#include "GhostMintDashboardHUD.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"

AGhostMintDashboardHUD::AGhostMintDashboardHUD() {
    // Constructor logic (e.g. load fonts/textures) if needed
}

void AGhostMintDashboardHUD::DrawHUD() {
    Super::DrawHUD();
    // Placeholder: draw background or debug text
    if (Canvas) {
        Canvas->DrawText(GEngine->GetSmallFont(), TEXT("GhostMint Dashboard"), 50, 50);
    }
}
