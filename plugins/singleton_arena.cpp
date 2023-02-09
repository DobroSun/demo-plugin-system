#include "singleton_arena.h"
#include <cstdlib>
#include <cstring>

static void singleton_arena_load(void* plugin) {
    auto arena = static_cast<singleton_arena_plugin*>(plugin);

    const uint32_t one_meg = 1024 * 1024;
    arena->memory    = malloc(one_meg);
    arena->allocated = 0;

    memset(arena->memory, 0, one_meg);
}

static void singleton_arena_unload(void* plugin) {
    auto arena = static_cast<singleton_arena_plugin*>(plugin);

    if (arena->memory) {
        free(arena->memory);
    }
    arena->allocated = 0;
}

static singleton_arena_plugin make_arena() {
    static plugin_vtable_load vtable = {};
    vtable.load   = singleton_arena_load;
    vtable.unload = singleton_arena_unload;

    singleton_arena_plugin result = {};
    result.super.name   = "Singleton Arena";
    result.super.type   = TYPE_PLUGIN_SUPPORTS_RUNTIME_LOADING;
    result.super.vtable = static_cast<void*>(&vtable);
    return result;
}


void* singleton_arena_plugin::allocate(uint64_t size) {
    void* result = static_cast<uint8_t*>(memory) + allocated;

    allocated += size;

    return result;
}

singleton_arena_plugin* singleton_arena_plugin::get() {
    static singleton_arena_plugin plugin = make_arena();
    return &plugin;
}

