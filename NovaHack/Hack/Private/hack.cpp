#include "../Public/hack.h"

engine::camera hack::GetCamera(engine::vec3 Rotation)
{
    engine::camera cam;

    cam.Location = memory::ReadMemory<engine::vec3>(cache::ViewMatrix + 0x240);

    cam.Rotation.x = (memory::ReadMemory<float>(cache::ViewMatrix + 0x228)) * 180 / engine::M_PI;
    cam.Rotation.y = Rotation.y;
    cam.Rotation.z = 0.0f;

    if (cam.Rotation.x < 0)
        cam.Rotation.x = 360 + cam.Rotation.x;

    cam.FOV = 90.f;

    return cam;
}

bool hack::Attach()
{
    memory::GameProcessId = memory::GetProcessId(L"FortniteClient-Win64-Shipping.exe");
    if (!memory::GameProcessId) return false;

    memory::GameHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, memory::GameProcessId);
    if (!memory::GameHandle) return false;

    memory::GameBase = memory::GetModuleBaseAddress(memory::GameProcessId, L"FortniteClient-Win64-Shipping.exe");
    if (!memory::GameBase) return false;

    return true;
}

bool hack::Tick()
{
    cache::Uworld = memory::ReadMemory<uintptr_t>(memory::GameBase + offsets::Uworld);
    if (!cache::Uworld) return false;

    cache::PersistentLevel = memory::ReadMemory<uintptr_t>(cache::Uworld + offsets::PersistentLevel);
    if (!cache::PersistentLevel) return false;

    cache::GameState = memory::ReadMemory<uintptr_t>(cache::Uworld + offsets::GameState);
    if (!cache::GameState) return false;

    cache::GameInstance = memory::ReadMemory<uintptr_t>(cache::Uworld + offsets::GameInstance);
    if (!cache::GameInstance) return false;

    cache::LocalPlayers = memory::ReadMemory<uintptr_t>(cache::GameInstance + offsets::LocalPlayers);
    if (!cache::LocalPlayers) return false;

    cache::LocalPlayer = memory::ReadMemory<uintptr_t>(cache::LocalPlayers);
    if (!cache::LocalPlayer) return false;

    cache::PlayerController = memory::ReadMemory<uintptr_t>(cache::LocalPlayer + offsets::PlayerController);
    if (!cache::PlayerController) return false;

    cache::PlayerCameraManager = memory::ReadMemory<uintptr_t>(cache::PlayerController + offsets::PlayerCameraManager);
    if (!cache::PlayerCameraManager) return false;

    cache::Character = memory::ReadMemory<uintptr_t>(cache::PlayerController + offsets::Character);
    if (!cache::Character) return false;

    cache::Mesh = memory::ReadMemory<uintptr_t>(cache::Character + offsets::Mesh);
    if (!cache::Mesh) return false;

    cache::AcknowledgedPawn = memory::ReadMemory<uintptr_t>(cache::PlayerController + offsets::AcknowledgedPawn);
    if (!cache::AcknowledgedPawn) return false;

    cache::RootComponent = memory::ReadMemory<uintptr_t>(cache::AcknowledgedPawn + offsets::RootComponent);
    if (!cache::RootComponent) return false;

    cache::PlayerState = memory::ReadMemory<uintptr_t>(cache::AcknowledgedPawn + offsets::PlayerState);
    if (!cache::PlayerState) return false;

    cache::ViewMatrix = memory::ReadMemory<uintptr_t>(cache::LocalPlayer + offsets::ViewMatrix);
    if (!cache::ViewMatrix) return false;

    cache::PlayerArray = memory::ReadMemory<uintptr_t>(cache::GameState + offsets::PlayerArray);
    if (!cache::PlayerArray) return false;

    cache::PlayerCount = memory::ReadMemory<int>(cache::GameState + offsets::PlayerArray + sizeof(uintptr_t));
    if (!cache::PlayerCount) return false;

    cache::TeamIndex = memory::ReadMemory<engine::uint8>(cache::PlayerState + offsets::TeamIndex);
    cache::CurrentWeapon = memory::ReadMemory<uintptr_t>(cache::AcknowledgedPawn + offsets::CurrentWeapon);
    cache::WeaponMesh = memory::ReadMemory<uintptr_t>(cache::CurrentWeapon + offsets::WeaponMesh);
    cache::WeaponData = memory::ReadMemory<uintptr_t>(cache::CurrentWeapon + offsets::WeaponData);
    cache::CharacterMovement = memory::ReadMemory<uintptr_t>(cache::Character + offsets::CharacterMovement);

    cache::LocalLocation = memory::ReadMemory<engine::vec3>(cache::RootComponent + offsets::RelativeLocation);
    cache::LocalRotation = memory::ReadMemory<engine::vec3>(cache::RootComponent + offsets::RelativeRotation);

    cache::LocalCamera = GetCamera(cache::LocalRotation);

    cache::AimData.ClosestFovDistance = FLT_MAX;
    cache::AimData.ClosestAimPos2D = { 0.f, 0.f };

    for (int i = 0; i < cache::PlayerCount; i++)
    {
        uintptr_t PlayerState = memory::ReadMemory<uintptr_t>(cache::PlayerArray + (i * sizeof(uintptr_t)));
        if (!PlayerState) continue;

        uintptr_t PawnPrivate = memory::ReadMemory<uintptr_t>(PlayerState + offsets::PawnPrivate);
        if (!PawnPrivate) continue;

        engine::uint8 TeamIndex = memory::ReadMemory<engine::uint8>(PlayerState + 0xDA8);
        if (PawnPrivate == cache::AcknowledgedPawn || TeamIndex == cache::TeamIndex) continue;

        uintptr_t Mesh = memory::ReadMemory<uintptr_t>(PawnPrivate + offsets::Mesh);
        if (!Mesh) continue;

        uintptr_t RootComponent = memory::ReadMemory<uintptr_t>(PawnPrivate + offsets::RootComponent);
        if (!RootComponent) continue;

        engine::vec3 RootPos3D = memory::ReadMemory<engine::vec3>(RootComponent + offsets::RelativeLocation);
        engine::vec3 HeadPos3D = RootPos3D + engine::vec3(0.f, 0.f, 90.f);
        engine::vec3 FootPos3D = RootPos3D - engine::vec3(0.f, 0.f, 90.f);
        engine::vec3 AimPos3D = RootPos3D + engine::vec3(0.f, 0.f, 60.f);

        engine::vec2 RootPos2D{};
        engine::vec2 HeadPos2D{};
        engine::vec2 FootPos2D{};
        engine::vec2 AimPos2D{};

        if (!engine::WorldToScreen(RootPos3D, cache::LocalCamera, &RootPos2D)) continue;
        if (!engine::WorldToScreen(HeadPos3D, cache::LocalCamera, &HeadPos2D)) continue;
        if (!engine::WorldToScreen(FootPos3D, cache::LocalCamera, &FootPos2D)) continue;
        if (!engine::WorldToScreen(AimPos3D, cache::LocalCamera, &AimPos2D)) continue;

        int WorldDistance = HeadPos3D.DistanceInt(cache::LocalLocation);
        float FovDistance = HeadPos2D.Distance(engine::ScreenCenter);

        if (FovDistance < cfg::AimBotFOV)
        {
            if (FovDistance < cache::AimData.ClosestFovDistance)
            {
                cache::AimData.ClosestFovDistance = FovDistance;
                cache::AimData.ClosestAimPos2D = AimPos2D;
            }
        }
        engine::drawdata Data{ RootPos2D, HeadPos2D, FootPos2D, WorldDistance, FovDistance, Mesh };
        cache::EspDataArray.push_back(Data);
    }
    aim::Tick();
    esp::Tick();
    exploits::Tick();

    return true;
}
