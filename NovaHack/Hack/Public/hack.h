#pragma once
#include "memory.h"
#include "engine.h"
#include "cache.h"
#include "offsets.h"
#include "exploits.h"
#include "aim.h"
#include "esp.h"

class hack
{
    static engine::camera GetCamera(engine::vec3 Rotation);
public:

    static bool Attach();
    static bool Tick();
};

