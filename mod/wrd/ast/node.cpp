#include "node.inl"
#include "../builtin/container/native/tnchain.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(node)

    const wtypes& me::getParams() const {
        static wtypes inner;
        return inner;
    }

    str me::run() {
        static narr empty;
        return run(empty);
    }

    str me::run(const std::string& name) {
        return run(name, narr());
    }

    str me::run(const std::string& name, const containable& args) {
        me& found = sub(name, args);
        if(nul(found)) return str();

        return found.run(args);
    }

	WRD_VERIFY(node, {
		for(auto& elem : it.subs())
			_getVerifier().verify(elem);
		return false;
	})
}
