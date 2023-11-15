#include "../Public/esp.h"

bool esp::IsVisible(uintptr_t Mesh)
{
    float LastSubmitTime = memory::ReadMemory<float>(Mesh + 0x28C);
    float LastRenderTimeOnScreen = memory::ReadMemory<float>(Mesh + 0x294);

    return LastRenderTimeOnScreen + 0.05f >= LastSubmitTime;
}

bool esp::Tick()
{
    ImDrawList* Draw = ImGui::GetForegroundDrawList();
    if (!Draw) return false;

    for (int i = 0; i < cache::EspDataArray.size(); i++)
    {
        ImColor Color;
        engine::drawdata Data = cache::EspDataArray[i];

        if (IsVisible(Data.Mesh)) // visible check
        {
            if (Data.FovDistance < cfg::AimBotFOV)
                Color = ImColor(255, 0, 0, 255);
            else
                Color = ImColor(255, 165, 0, 255);
        }
        else
        {
            Color = ImColor(0, 255, 0, 255);
        }

        engine::vec3 HeadPos3D = Data.RootPos3D + engine::vec3(0.f, 0.f, 90.f);
        engine::vec3 FootPos3D = Data.RootPos3D - engine::vec3(0.f, 0.f, 90.f);
        engine::vec3 AimPos3D = Data.RootPos3D + engine::vec3(0.f, 0.f, 60.f);

        engine::vec2 HeadPos2D{};
        engine::vec2 FootPos2D{};

        if (!engine::WorldToScreen(HeadPos3D, cache::LocalCamera, &HeadPos2D)) continue;
        if (!engine::WorldToScreen(FootPos3D, cache::LocalCamera, &FootPos2D)) continue;

        if (cfg::Snaplines) { // snaplines
            Draw->AddLine
            (
                ImVec2(FootPos2D.x, FootPos2D.y),
                ImVec2(engine::ScreenCenter.x, engine::ScreenCenter.y),
                Color,
                2.f
            );
        }

        if (cfg::EspBox) { // espboxes
            float Width = (HeadPos2D.y - FootPos2D.y) * 0.20f;

            Draw->AddRect
            (
                ImVec2(HeadPos2D.x - Width, HeadPos2D.y),
                ImVec2(FootPos2D.x + Width, FootPos2D.y),
                Color,
                0.f,
                0,
                2.f
            );
        }

        if (cfg::ShowDistance) {
            Draw->AddText({ FootPos2D.x, FootPos2D.y }, Color, std::string(std::to_string(Data.WorldDistance / 100) + 'm').c_str());
        }
    }

    cache::EspDataArray.clear();
    return true;
}
