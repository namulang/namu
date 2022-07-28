#include <wrd.hpp>
#include <iostream>
using namespace wrd;

struct con {
    void say() {
        std::cout << "hello world!\n";
    }

    int add(int a, int b) {
        return a + b;
    }

    const string& print(const std::string& msg) {
        std::cout << msg;
        return msg;
    }

    std::string input() {
        std::string ret;
        std::cin >> ret;
        return ret;
    }
};

extern "C" void wrd_bridge_cpp_entrypoint(bicontainable* tray) {
    tray->add("con", tcppBridge<con>::def()
        ->func("say", &con::say)
        ->func("add", &con::add)
        ->func("print", &con::print)
        ->func("input", &con::input));
}
