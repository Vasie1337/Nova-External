#include "../Public/render.h"

bool render::InitDirectX()
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object)))
        return false;

    ZeroMemory(&params, sizeof(params));
    params.Windowed = TRUE;
    params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    params.hDeviceWindow = overlay_hwnd;
    params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    params.BackBufferFormat = D3DFMT_A8R8G8B8;
    params.BackBufferWidth = static_cast<UINT>(engine::Screen.x);
    params.BackBufferHeight = static_cast<UINT>(engine::Screen.y);
    params.EnableAutoDepthStencil = TRUE;
    params.AutoDepthStencilFormat = D3DFMT_D16;
    params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlay_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, 0, &device)))
    {
        object->Release();
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplWin32_Init(overlay_hwnd);
    ImGui_ImplDX9_Init(device);

    menu::InitMenu();

    object->Release();

    return true;
}

bool render::CreateOverlay()
{
    WNDCLASSEXA wcex = {
     sizeof(WNDCLASSEXA),
     0,
     DefWindowProcA,
     0,
     0,
     nullptr,
     LoadIcon(nullptr, IDI_APPLICATION),
     LoadCursor(nullptr, IDC_ARROW),
     nullptr,
     nullptr,
     ("Overlay"),
     LoadIcon(nullptr, IDI_APPLICATION)
    };

    RECT rect{};
    if (!GetWindowRect(GetDesktopWindow(), &rect))
        return false;

    RegisterClassExA(&wcex);

    overlay_hwnd = CreateWindowExA(
        NULL,
        ("Overlay"),
        ("Overlay"),
        WS_POPUP,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom,
        NULL,
        NULL,
        wcex.hInstance,
        NULL
    );
    if (!overlay_hwnd) return false;

    SetWindowLong(overlay_hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED);
    MARGINS margin = { -1 };
    DwmExtendFrameIntoClientArea(overlay_hwnd, &margin);
    ShowWindow(overlay_hwnd, SW_SHOW);
    SetLayeredWindowAttributes(overlay_hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    UpdateWindow(overlay_hwnd);

    return true;
}

bool render::Loop()
{
    constexpr std::chrono::milliseconds SleepTime(10);

    while (Running)
    {
        std::this_thread::sleep_for(SleepTime);

        if (PeekMessage(&message, overlay_hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        if (message.message == WM_QUIT)
            Running = false;

        if (GetAsyncKeyState(VK_INSERT) & 0x01)
            ShowMenu = !ShowMenu;

        if (GetAsyncKeyState(VK_END) & 0x01)
            Running = false;

        if (!Running)
            break;

        HWND foreground_window = GetForegroundWindow();
        HWND prev_window = GetWindow(foreground_window, GW_HWNDPREV);

        SetWindowPos(overlay_hwnd, prev_window, 1, 1, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        UpdateWindow(overlay_hwnd);

        ImGuiIO& io = ImGui::GetIO();
        POINT p;
        GetCursorPos(&p);

        io.MousePos.x = static_cast<float>(p.x);
        io.MousePos.y = static_cast<float>(p.y);

        io.MouseDown[0] = (GetAsyncKeyState(0x1) & 0x8000) != 0;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        hack::Tick();

        ImGui::GetForegroundDrawList()->AddCircle(
            ImVec2(engine::Screen.x / 2.f, engine::Screen.y / 2.f),
            cfg::AimBotFOV,
            ImColor(51, 214, 255, 255),
            0,
            2.f
        );

        if (cfg::Crosshair)
        {
            ImGui::GetForegroundDrawList()->AddLine(
                ImVec2(engine::Screen.x / 2.f - cfg::CrosshairLength, engine::Screen.y / 2.f),
                ImVec2(engine::Screen.x / 2.f + cfg::CrosshairLength, engine::Screen.y / 2.f),
                ImColor(51, 214, 255, 255),
                2.f
            );

            ImGui::GetForegroundDrawList()->AddLine(
                ImVec2(engine::Screen.x / 2.f, engine::Screen.y / 2.f - cfg::CrosshairLength),
                ImVec2(engine::Screen.x / 2.f, engine::Screen.y / 2.f + cfg::CrosshairLength),
                ImColor(51, 214, 255, 255),
                2.f
            );
        }

        if (ShowMenu)
        {
            ImGui::GetForegroundDrawList()->AddCircleFilled(
                ImVec2(io.MousePos.x, io.MousePos.y),
                5.f,
                ImColor(51, 214, 255, 255)
            );
            menu::RenderMenu();
        }

        ImGui::EndFrame();

        device->SetRenderState(D3DRS_ZENABLE, false);
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
        device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

        if (device->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            device->EndScene();
        }

        HRESULT result = device->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            device->Reset(&params);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (device != NULL)
    {
        device->EndScene();
        device->Release();
    }

    if (object != NULL)
    {
        object->Release();
    }

    DestroyWindow(overlay_hwnd);

    return true;
}
