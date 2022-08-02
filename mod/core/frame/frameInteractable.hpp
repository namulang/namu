#pragma once

#include "../common.hpp"

namespace namu {

    class node;
    template <typename K, typename V> class tbicontainable;
    typedef tbicontainable<std::string, node> bicontainable;

    class frameInteractable {
        friend class frameInteract;

    protected:
        virtual void _inFrame(const bicontainable& args) = 0;
        virtual void _outFrame() = 0;
    };
}
