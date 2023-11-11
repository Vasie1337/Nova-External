#include "Hack/Public/hack.h"
#include "Overlay/Public/render.h"

int main()
{
    hack::Attach();

    render::CreateOverlay();
    render::InitDirectX();
    render::Loop();
}
