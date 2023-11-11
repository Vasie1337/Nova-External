#include "../Public/aim.h"

inline void aim::MoveMouse(int deltaX, int deltaY)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = deltaX;
    input.mi.dy = deltaY;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

bool aim::Tick()
{
    if (!GetAsyncKeyState(VK_RBUTTON) || !cfg::Aimbot)
        return false;

    float x = cache::AimData.ClosestAimPos2D.x;
    float y = cache::AimData.ClosestAimPos2D.y;

    float TargetX = 0;
    if (x != 0) {
        TargetX = (x > engine::ScreenCenter.x) ? -(engine::ScreenCenter.x - x) : x - engine::ScreenCenter.x;
        TargetX /= cfg::AimSmoothness;
        if ((TargetX + engine::ScreenCenter.x) > (engine::ScreenCenter.x * 2.f) || (TargetX + engine::ScreenCenter.x) < 0)
            TargetX = 0;
    }

    float TargetY = 0;
    if (y != 0) {
        TargetY = (y > engine::ScreenCenter.y) ? -(engine::ScreenCenter.y - y) : y - engine::ScreenCenter.y;
        TargetY /= cfg::AimSmoothness;
        if ((TargetY + engine::ScreenCenter.y) > (engine::ScreenCenter.y * 2.f) || (TargetY + engine::ScreenCenter.y) < 0)
            TargetY = 0;
    }

    MoveMouse(static_cast<int>(TargetX), static_cast<int>(TargetY));
    return true;
}
