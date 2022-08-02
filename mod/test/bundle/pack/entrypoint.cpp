#include <core.hpp>
#include <iostream>
#include "common.hpp"
using namespace namu;

struct con {
    void say() {
        std::cout << "hello world!\n";
    }

    int add(int a, int b) {
        return a + b;
    }

    const string& print(const std::string& msg) {
        WRD_W("=========================");
        for(int n = 0; n < 10; n++) {
            const wchar* c = msg.c_str();
            WRD_W("[%d]=%d", n, (int) c[n]);
        }
        WRD_W("=========================");
        std::cout << msg;
        return msg;
    }

    std::string input() {
        std::string ret;
        std::cin >> ret;
        return ret;
    }
};

extern "C" _wout void namu_bridge_cpp_entrypoint(bicontainable* tray) {
    tray->add("con", tcppBridge<con>::def()
        ->func("say", &con::say)
        ->func("add", &con::add)
        ->func("print", &con::print)
        ->func("input", &con::input));
}
