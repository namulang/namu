#include "../ast/obj.hpp"
#include "../ast/baseFunc.hpp"
#include "../ast/dumScope.hpp"
#include "../ast/slot.hpp"
#include "../ast/node.inl"
#include "starter.hpp"
#include "thread.hpp"

namespace namu {

    NAMU_DEF_ME(starter)

    nbicontainer& me::subs() {
        static dumScope inner;
        return inner;
    }

    priority me::prioritize(const args& a) const {
        return nul(a.getMe()) ? NO_MATCH : EXACT_MATCH;
    }

    str me::run(const args& a) {
        if(!canRun(a)) return NAMU_E("arguments doesn't have proper 'me'"), str();

        // TODO: don't use static variable '_cache':
        //  instead, put cache onto origin object, and if arr instance is origin, remove the cache.
        arr::_cache.clear();
        node& pak = a.getMe();
        NAMU_I("run a pack");
        node& main = _findMain(pak, args());
        if(nul(main))
            return NAMU_E("there is 0 or more than 2 main() found."), str();

        if(main.canRun(a)) {
            _prepareFrame(thread::get()._getFrames());
            NAMU_DI("============== START ================");
            str res = pak.run(MAIN);
            NAMU_DI("=====================================");
            return res;
        }

        // TODO: main(str[])

        return NAMU_E("couldn't run main func(). it doesn't match any argument"), str();
    }

    void me::_prepareFrame(frames& fr) {
        fr.rel();
    }

    node& me::_findMain(node& pak, const args& a) {
        // TODO: now, only find to main() but I need to find main(argc, argv) case, too.
        node& ret = pak.sub(MAIN);
        if(nul(ret))
            NAMU_E("couldn't find main().");

        return ret;
    }
}
