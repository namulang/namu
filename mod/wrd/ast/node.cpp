#include "node.inl"
#include "../builtin/container/native/tnchain.inl"
#include "../builtin/container/native/tnarr.inl"
#include "../type/as.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(node)

    str me::run() {
        static narr empty;
        return run(empty);
    }

	WRD_VERIFY(node, {
		for(auto& elem : it.subs())
			_verify(elem, report);
		return false;
	})
}
