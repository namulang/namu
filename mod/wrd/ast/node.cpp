#include "node.inl"
#include "../builtin/container/native/tnchain.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "ref.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(node)

    node& me::operator[](const std::string& name) const {
        return sub(name);
    }

    const params& me::getParams() const {
        static params inner;
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

        if(!found.doesNeedScope())
            return found.run(args);

        _inFrame();
        str ret = found.run(args);
        _outFrame();
        return ret;
    }

	WRD_VERIFY(node, {
		for(auto& elem : it.subs())
			_getVerifier().verify(elem);
		return false;
	})
}
