#include "../Public/menu.h"

bool menu::InitMenu()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
	ImGuiIO& io = ImGui::GetIO();

	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

	colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);

	colors[ImGuiCol_Border] = ImColor(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImColor(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);

	colors[ImGuiCol_CheckMark] = ImColor(51, 214, 255, 255);
	colors[ImGuiCol_SliderGrab] = ImColor(51, 214, 255, 255);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Separator] = ImColor(51, 214, 255, 255);
	colors[ImGuiCol_SeparatorHovered] = ImColor(51, 214, 255, 255);
	colors[ImGuiCol_SeparatorActive] = ImColor(51, 214, 255, 255);

	colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_TabActive] = ImColor(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

	style.WindowBorderSize = 3;
	style.ChildBorderSize = 2;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 2;

	style.WindowRounding = 3;
	style.FrameRounding = 3;
	style.TabRounding = 3;
	style.GrabRounding = 3;

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
			WindowSize = { 400.f, 220.f };

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
			WindowSize = { 400.f, 400.f };

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
