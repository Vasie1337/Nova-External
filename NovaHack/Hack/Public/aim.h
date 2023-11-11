#pragma once
#include "engine.h"
#include "cache.h"
#include "cfg.h"

#include "../../Libs/Public/imgui.h"
#include "../../Libs/Public/imgui_impl_win32.h"
#include "../../Libs/Public/imgui_impl_dx9.h"

class aim
{
    inline static void MoveMouse(int deltaX, int deltaY);

public:
    static bool Tick();
};

