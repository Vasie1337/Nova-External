#pragma once
#include <string>

#include "../../Libs/Public/imgui.h"
#include "../../Libs/Public/imgui_impl_win32.h"
#include "../../Libs/Public/imgui_impl_dx9.h"

#include "cfg.h"
#include "cache.h"
#include "memory.h"

class esp
{
    static bool IsVisible(uintptr_t Mesh);

public:
    static bool Tick();
};

