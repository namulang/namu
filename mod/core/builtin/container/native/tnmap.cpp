#include "core/builtin/container/native/tnmap.inl"
#include "core/ast/node.hpp"

namespace nm {
    template class _nout tbicontainable<std::string, node>;
    template class _nout tnmap<std::string, node>;
}
