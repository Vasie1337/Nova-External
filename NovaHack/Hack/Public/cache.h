#pragma once
#include <vector>

#include "engine.h"

class cache
{
public:
    inline static uintptr_t Uworld;
    inline static uintptr_t PersistentLevel;
    inline static uintptr_t GameState;
    inline static uintptr_t GameInstance;
    inline static uintptr_t LocalPlayers;
    inline static uintptr_t LocalPlayer;
    inline static uintptr_t PlayerController;
    inline static uintptr_t Character;
    inline static uintptr_t PlayerCameraManager;
    inline static uintptr_t CurrentVehicle;
    inline static uintptr_t AcknowledgedPawn;
    inline static uintptr_t PlayerState;
    inline static uintptr_t CurrentWeapon;
    inline static uintptr_t WeaponData;
    inline static uintptr_t WeaponMesh;
    inline static uintptr_t CharacterMovement;
    inline static uintptr_t Mesh;
    inline static uintptr_t RootComponent;
    inline static uintptr_t ViewMatrix;
    inline static uintptr_t PlayerArray;

    inline static int PlayerCount;
    inline static engine::uint8 TeamIndex;
    
    inline static engine::camera LocalCamera;
    inline static engine::vec3 LocalLocation;
    inline static engine::vec3 LocalRotation;
    
    inline static std::vector<engine::drawdata> EspDataArray;
    inline static engine::aimdata AimData;
};

