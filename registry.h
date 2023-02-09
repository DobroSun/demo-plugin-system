#pragma once

#include <cstdint>

enum plugin_type {
    TYPE_NONE = 0,
    TYPE_PLUGIN_SIMPLE,
    TYPE_PLUGIN_SUPPORTS_RUNTIME_LOADING
};

struct plugin_description {
    const char* name;
    plugin_type type;
    void* vtable;
};

struct plugin_vtable_load {
    void (*load)(void*);
    void (*unload)(void*);
};

struct registry {
    void** plugins;
    uint32_t count;
};

struct plugins_array {
    void** plugins; 
    uint32_t count;
};

registry create_registry(uint64_t);
void     destroy_registry(registry*);

void*    register_plugin(registry*, void*);

plugins_array get_all_plugins_with_type(registry*, plugin_type);

void load_all_plugins(registry*);
void unload_all_plugins(registry*);








