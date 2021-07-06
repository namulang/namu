#include "packMaker.hpp"

namespace wrd {

    WRD_DEF_ME(packMaker)

    const packMakings& me::_getMakings() {
        static packMakings* inner = nullptr;
        if(!inner) {
            inner = new packMakings();

            for(const type* sub : ttype<packMaking>::get().getSubs()) {
                packMaking* new1 = sub->makeAs<packMaking>();
                if(nul(new1)) {
                    WRD_E("fail to make packMaking named to %s", sub->getName().c_str());
                    continue;
                }

                inner->push_back(new1);
            }
        }

        return *inner;
    }

}
