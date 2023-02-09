#pragma once

#include "../registry.h"

struct singleton_arena_plugin {
    plugin_description super;

    static singleton_arena_plugin* get();

    void* allocate(uint64_t);

    void* memory = nullptr;
    uint32_t allocated = 0;
};

