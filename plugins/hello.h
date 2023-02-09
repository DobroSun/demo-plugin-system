#pragma once
#include "../registry.h"

struct hello_plugin {
    plugin_description super;

    static hello_plugin* get();

    void say_hello();
};
