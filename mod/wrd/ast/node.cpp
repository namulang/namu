#include "node.inl"
#include "scope.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"
#include "params.hpp"

namespace wrd {

    WRD_DEF_ME(node)

    node& me::operator[](const std::string& name) const {
        return sub(name);
    }

    str me::run() {
        static narr empty;
        return run(empty);
    }

    str me::run(const std::string& name) {
        return run(name, narr());
    }

    str me::run(const std::string& name, const ucontainable& args) {
        if(name.empty()) return run(args);
        me& found = sub(name, args);
        if(nul(found)) return str();

        return _onRunSub(found, args);
    }

    WRD_VERIFY({ // no same variable.
        for(auto e=it.subs().begin(); e ;++e)
            if(it.subAll<obj>(e.getKey()).len() > 1)
                return _err(errCode::DUP_VAR, e.getKey().c_str());
    })
}
