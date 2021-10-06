#include "node.hpp"
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

    node& me::sub(const std::string& name) const {
        return subs().get([&](const node& elem) {
            return elem.getName() == name;
        });
    }

    node& me::sub(const std::string& name, const ncontainer& args) {
        if(nul(args))
            return sub(name);

        return sub(name, createTypesFromArgs(args));
    }

    node& me::sub(const std::string& name, const wtypes& types) {
        return subs().get([&](const node& elem) {
            return elem.getName() == name && elem.canRun(types);
        });
    }

    node& me::sub(const std::string& name, const ncontainer& args) const WRD_UNCONST_FUNC(sub(name, args))
    node& me::sub(const std::string& name, const wtypes& types) const WRD_UNCONST_FUNC(sub(name, types))

    narr me::subAll(const std::string& name) const {
        return subs().getAll([&](const node& elem) {
            return elem.getName() == name;
        });
    }

    narr me::subAll(const std::string& name, const ncontainer& args) {
        if(nul(args))
            return subAll(name);

        return subAll(name, createTypesFromArgs(args));
    }

    narr me::subAll(const std::string& name, const wtypes& types) {
        return subs().getAll([&](const node& elem) {
            return elem.getName() == name && elem.canRun(types);
        });
    }

    narr me::subAll(const std::string& name, const ncontainer& args) const WRD_UNCONST_FUNC(subAll(name, args))
    narr me::subAll(const std::string& name, const wtypes& types) const WRD_UNCONST_FUNC(subAll(name, types))

	WRD_VERIFY(node, {
		for(auto& elem : it.subs())
			_verify(elem, report);
		return false;
	})
}
