#pragma once
#include "data.h"
#include "../../Hack/Public/cfg.h"

#include "../../Libs/Public/imgui.h"
#include "../../Libs/Public/imgui_impl_win32.h"
#include "../../Libs/Public/imgui_impl_dx9.h"

class menu
{
	inline static ImFont* text_font;
	inline static ImFont* tab_font;
	inline static ImFont* title_font;

	inline static ImVec2 WindowSize = { 400.f, 200.f };
public:

	static bool InitMenu();
	static bool RenderMenu();
};

