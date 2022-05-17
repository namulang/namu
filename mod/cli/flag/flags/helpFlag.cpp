#include "helpFlag.hpp"
#include "../../cli.hpp"

namespace wrd {

    const wchar* helpFlag::getName() const {
        return "-h";
    }

    const wchar* helpFlag::getDescription() const {
        return R"DESC(
        show help documents.
        list all of available commands and description for how to use them.)DESC";
    }

    const wchar* helpFlag::_getRegExpr() const {
        return "^\\-h$";
    }

    wbool helpFlag::_onTake(const args& tray, cli& c, interpreter& ip) const {

        const flags& opts = c.getFlags();
        for(int n=0; n < opts.size() ;n++) {
            const flag& opt = opts[n].get();
            std::cout   << "   " << opt.getName()
                        << opt.getDescription() << "\n\n";
        }

        return true;
    }
}
