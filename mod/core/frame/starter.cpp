#include "../ast/obj.hpp"
#include "../ast/func.hpp"
#include "../ast/scope.inl"
#include "../ast/slot.hpp"
#include "../ast/node.inl"
#include "starter.hpp"
#include "thread.hpp"

namespace namu {

    NAMU_DEF_ME(starter)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

    nbool me::canRun(const args& a) const {
        return !nul(a.getMe());
    }

    str me::run(const args& a) {
        if(!canRun(a)) return NAMU_E("arguments doesn't have proper 'me'"), str();

        node& pak = a.getMe();
        NAMU_I("run a pack");
        node& main = _findMain(pak, args());
        if(nul(main))
            return NAMU_E("there is 0 or more than 2 main() found."), str();

        if(main.canRun(a)) {
            _prepareFrame(thread::get()._getFrames());
            NAMU_DI("============== START ================");
            str res = pak.run("main");
            NAMU_DI("=====================================");
            return res;
        }

        /* TODO: str[] args
        if(main.canRun(narr(k*/

        return NAMU_E("couldn't run main func(). it doesn't match any argument"), str();
    }

    void me::_prepareFrame(frames& fr) {
        fr.rel();
    }

    node& me::_findMain(node& pak, const args& a) {
        // TODO: now, only find to main() but I need to find main(argc, argv) case, too.
        node& ret = pak.sub("main");
        if(nul(ret))
            NAMU_E("couldn't find main().");

        return ret;
    }
}
