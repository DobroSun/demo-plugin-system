#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include "registry.h"
#include "plugins/hello.h"
#include "plugins/singleton_arena.h"


int main() {
    registry registry = create_registry(64 * 1024);

    register_plugin(&registry, hello_plugin::get());
    register_plugin(&registry, singleton_arena_plugin::get());
    load_all_plugins(&registry);

    {
        auto arena = singleton_arena_plugin::get();
        int *value = static_cast<int*>(arena->allocate(sizeof(int)));
            *value = 53;
        printf("Value := %d\n", *value);
    }

    unload_all_plugins(&registry);

    {
        auto hello = hello_plugin::get();
        hello->say_hello();
    }

    destroy_registry(&registry);
    return 0;
}
