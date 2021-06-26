#include <interp.hpp>
#include <iostream>
using namespace wrd;

struct helloWorld {
    void say() {
        std::cout << "hello world!\n";
    }
};

extern "C" struct wrd_bridge_cpp_origins* wrd_module_entrypoint(struct wrd_bridge_cpp_origins* packs) {

    packs->arr[packs->size++] = tcppBridge<helloWorld>::def()
        ->func("say", &helloWorld::say);

    return packs;
}
