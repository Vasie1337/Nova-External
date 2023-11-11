#pragma once
#include <Windows.h>
#include <dwmapi.h>
#include <d3d9.h>
#include <chrono>

#pragma comment(lib, "d3d9.lib")

#include "../../Libs/Public/imgui.h"
#include "../../Libs/Public/imgui_impl_win32.h"
#include "../../Libs/Public/imgui_impl_dx9.h"

#include "../../Hack/Public/hack.h"

#include "cfg.h"
#include "menu.h"

class render
{
	inline static IDirect3D9Ex* object = nullptr;
	inline static IDirect3DDevice9Ex* device = nullptr;
	inline static D3DPRESENT_PARAMETERS params{};
    inline static MSG message{};
    inline static HWND overlay_hwnd = NULL;

public:
    inline static bool ShowMenu = true;
    inline static bool Running = true;

    static bool InitDirectX();
    static bool CreateOverlay();
    static bool Loop();
};

