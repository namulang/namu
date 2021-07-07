#include <interp.hpp>
#include <iostream>
using namespace wrd;

struct helloWorld {
    void say() {
        std::cout << "hello world!\n";
    }
};

extern "C" void wrd_bridge_cpp_entrypoint(wrd_bridge_cpp_origins* tray) {
    tray->add(tcppBridge<helloWorld>::def()
        ->func("say", &helloWorld::say));
}
