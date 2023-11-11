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

        if (cfg::Snaplines) { // snaplines
            Draw->AddLine
            (
                ImVec2(Data.FootPos2D.x, Data.FootPos2D.y),
                ImVec2(engine::ScreenCenter.x, engine::ScreenCenter.y),
                Color,
                2.f
            );
        }

        if (cfg::EspBox) { // espboxes
            float Width = (Data.HeadPos2D.y - Data.FootPos2D.y) * 0.20f;

            Draw->AddRect
            (
                ImVec2(Data.HeadPos2D.x - Width, Data.HeadPos2D.y),
                ImVec2(Data.FootPos2D.x + Width, Data.FootPos2D.y),
                Color,
                0.f,
                0,
                2.f
            );
        }

        if (cfg::ShowDistance) {
            Draw->AddText({ Data.FootPos2D.x, Data.FootPos2D.y }, Color, std::string(std::to_string(Data.WorldDistance / 100) + 'm').c_str());
        }
    }

    cache::EspDataArray.clear();
    return true;
}
