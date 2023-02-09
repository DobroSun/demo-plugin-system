#include "hello.h"
#include <cstdio>


static hello_plugin make_hello_plugin() {
    hello_plugin result = {};
    result.super.name   = "Hello Plugin";
    result.super.type   = TYPE_PLUGIN_SIMPLE;
    result.super.vtable = nullptr;
    return result;
}


void hello_plugin::say_hello() {
    puts("Hello world!");
}

hello_plugin* hello_plugin::get() {
    static hello_plugin plugin = make_hello_plugin();
    return &plugin;
}

