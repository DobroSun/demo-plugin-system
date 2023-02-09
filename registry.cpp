#include "registry.h"
#include <cstdlib>


registry create_registry(uint64_t amount_of_memory_used) {
    registry system = {};
    system.plugins = static_cast<void**>(malloc(amount_of_memory_used));
    system.count   = 0;
    return system;
}

void destroy_registry(registry* registry) {
    free(registry->plugins);
    *registry = {};
}


void* register_plugin(registry* registry, void* plugin) {
    registry->plugins[registry->count++] = plugin;
    return plugin;
}

plugins_array get_all_plugins_with_type(registry* registry, plugin_type type) {
    plugins_array result = {};

    uint32_t count = 0;
    for (uint32_t i = 0; i < registry->count; i++) {
        auto header = static_cast<plugin_description*>(registry->plugins[i]);

        if (header->type == type) {
            count++;
        }
    }

    if (count) {
        void** plugins = static_cast<void**>(malloc(sizeof(void*) * count));

        count = 0;
        for (uint32_t i = 0; i < registry->count; i++) {
            auto header = static_cast<plugin_description*>(registry->plugins[i]);

            if (header->type == type) {
                plugins[count++] = static_cast<void*>(header);
            }
        }

        result.plugins = plugins;
        result.count   = count;
    }
    return result;
}

static bool is_valid(plugins_array a) {
    return a.plugins && a.count;
}

void load_all_plugins(registry* registry) {
    plugins_array query = get_all_plugins_with_type(registry, TYPE_PLUGIN_SUPPORTS_RUNTIME_LOADING);

    if (is_valid(query)) {
        for (uint32_t i = 0; i < query.count; i++) {
            auto plugin = static_cast<void*>(query.plugins[i]);
            auto header = static_cast<plugin_description*>(plugin);
            auto vtable = static_cast<plugin_vtable_load*>(header->vtable);

            vtable->load(plugin);
        }

        free(query.plugins);
    }
}

void unload_all_plugins(registry* registry) {
    plugins_array query = get_all_plugins_with_type(registry, TYPE_PLUGIN_SUPPORTS_RUNTIME_LOADING);

    if (is_valid(query)) {
        for (uint32_t i = 0; i < query.count; i++) {
            auto plugin = static_cast<void*>(query.plugins[i]);
            auto header = static_cast<plugin_description*>(plugin);
            auto vtable = static_cast<plugin_vtable_load*>(header->vtable);

            vtable->unload(plugin);
        }

        free(query.plugins);
    }
}




