#pragma once

#include "../tbicontainable.hpp"

namespace namu {

    template <typename K, typename V>
    class tnbicontainer : public instance, public tbicontainable<K, V>, public clonable {
        NAMU(ADT(tnbicontainer, instance))
    };

    typedef tnbicontainer<std::string, node> nbicontainer;
}
