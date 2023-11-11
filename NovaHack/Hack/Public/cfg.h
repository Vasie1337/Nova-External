#pragma once


class cfg
{
public:
	// visuals
	inline static bool EspBox = true;
	inline static bool Snaplines = true;
	inline static bool ShowDistance = true;

	inline static bool Crosshair = true;
	inline static float CrosshairLength = 15.f;

	// aim
	inline static bool Aimbot = true;

	inline static float AimBotFOV = 200.f;
	inline static float AimSmoothness = 3.f;

	// exploits
    inline static bool Exploits = true;
	inline static bool RapidFire = true;
	inline static bool NoRecoil = true;
	inline static bool NoSpread = true;
	inline static bool ADSAir = true;

	inline static bool ChangeWeaponMesh = false;
	inline static bool ChangePlayerMesh = false;

	inline static float WeaponMeshScale = 1.f;
	inline static float PlayerMeshScale = 1.f;
};

