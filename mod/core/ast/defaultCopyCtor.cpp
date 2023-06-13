#include "defaultCopyCtor.hpp"
#include "../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(defaultCopyCtor), DEF_VISIT())

    str me::run(const args& a) {
        if (!canRun(a)) return str();

        const node& p = getParams()[0].getOrigin();
        return str((node*) a.begin()->as(p)->clone());
    }
}
