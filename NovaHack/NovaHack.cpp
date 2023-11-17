#include "Hack/Public/hack.h"
#include "Overlay/Public/render.h"

/*
Simple external cheat for Fortnite version 7.40

Features:

- Memory Aimbot
- Esp Box
- Esp Snaplines
- Visible check
- Rapid Fire
- No Spread
- Spinbot
- InstaRevive
- Airstuck
- ADS in Air
- No Recoil
- Crosshair
*/

int main()
{
    hack::Attach();

    render::CreateOverlay();
    render::InitDirectX();


    render::Loop();
}
