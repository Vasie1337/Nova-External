#include "../Public/aim.h"
#include "../Public/memory.h"

bool aim::Tick()
{
    float ViewPitchMin = -89.9999f;
    float ViewPitchMax = 89.9999f;
    float ViewYawMin = 0.0000f;
    float ViewYawMax = 359.9999f;

    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2454, ViewPitchMin);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2458, ViewPitchMax);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x245c, ViewYawMin);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2460, ViewYawMax);

    if (!GetAsyncKeyState(VK_RBUTTON) || !cfg::Aimbot || cache::AimData.ClosestFovDistance == FLT_MAX)
        return false;

    engine::vec3 VectorPos = cache::AimData.ClosestAimPos3D - cache::LocalCamera.Location;

    float distance = sqrtf(VectorPos.x * VectorPos.x + VectorPos.y * VectorPos.y + VectorPos.z * VectorPos.z);
    float x, y;
    x = -((acosf(VectorPos.z / distance) * (float)(180.0f / engine::M_PI)) - 90.f);
    y = atan2f(VectorPos.y, VectorPos.x) * (float)(180.0f / engine::M_PI);
    
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2454, x);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2458, x);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x245c, y);
    memory::WriteMemory<float>(cache::PlayerCameraManager + 0x2460, y);
    return true;
}
