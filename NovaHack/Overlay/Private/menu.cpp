#include "../Public/menu.h"

bool menu::InitMenu()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
	ImGuiIO& io = ImGui::GetIO();

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);

	style.WindowTitleAlign = { 0.5f, 0.5f };
	//style.FrameRounding = 0.0f;
	style.FrameBorderSize = 1.f;
	style.GrabRounding = 10.0f;
	style.WindowRounding = 10.0f;
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.ScrollbarRounding = 10.f;
	style.ScrollbarSize = 4.f;
	style.FramePadding = ImVec2(2, 4);

	text_font = io.Fonts->AddFontFromMemoryTTF(FontBytes, 18, 16.0f);
	title_font = io.Fonts->AddFontFromMemoryTTF(FontBytes, 22, 22.0f);

	return false;
}

bool menu::RenderMenu()
{
	ImGui::Begin("Vasie Nova", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowSize(WindowSize);

	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize("Vasie Nova").x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

	ImGui::PushFont(title_font);
	ImGui::Text("Vasie Nova");
	ImGui::PopFont();

	ImGui::NewLine();
	if (ImGui::BeginTabBar("TabBar", 0))
	{
		if (ImGui::BeginTabItem("Visuals"))
		{
			WindowSize = { 400.f, 200.f };

			ImGui::Checkbox("Esp Box", &cfg::EspBox);
			ImGui::Checkbox("Snap Lines", &cfg::Snaplines);

			ImGui::Checkbox("Crosshair", &cfg::Crosshair);
			ImGui::SliderFloat("Crosshair length", &cfg::CrosshairLength, 5.f, 20.f);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Aim"))
		{
			WindowSize = { 400.f, 170.f };

			ImGui::Checkbox("AimBot", &cfg::Aimbot);
			ImGui::SliderFloat("AimBot FOV", &cfg::AimBotFOV, 1.f, 200.f);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Exploits"))
		{
			WindowSize = { 400.f, 370.f };

			ImGui::Checkbox("Rapid Fire", &cfg::RapidFire);
			ImGui::Checkbox("No Recoil", &cfg::NoRecoil);
			ImGui::Checkbox("No Spread", &cfg::NoSpread);
			ImGui::Checkbox("ADS in Air", &cfg::ADSAir);
			ImGui::Checkbox("Spinbot", &cfg::Spinbot);
			ImGui::Checkbox("InstaRevive", &cfg::InstaRevive);
			ImGui::Checkbox("Airstuck", &cfg::Airstuck);

			ImGui::Checkbox("Change Weapon Mesh", &cfg::ChangeWeaponMesh);
			ImGui::SliderFloat("Weapon Mesh Scale", &cfg::WeaponMeshScale, 0.1f, 10.f);

			ImGui::Checkbox("Change Player Mesh", &cfg::ChangePlayerMesh);
			ImGui::SliderFloat("Player Mesh Scale", &cfg::PlayerMeshScale, 0.1f, 10.f);

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}


	ImGui::End();

	return true;
}
