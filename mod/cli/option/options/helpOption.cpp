#include "helpOption.hpp"
#include "../options.hpp"
#include "../../cli.hpp"

namespace wrd {

    const wchar* helpOption::getName() const {
        return "-h";
    }

    const wchar* helpOption::getDescription() const {
        return R"DESC(
        show help documents.
        list all of available commands and description for how to use them.)DESC";
    }

    const wchar* helpOption::_getRegExpr() const {
        return "^\\-h$";
    }

    wbool helpOption::_onTake(const args& tray, cli& c, interpreter& ip) const {

        const options& opts = c.getOptions();
        for(int n=0; n < opts.size() ;n++) {
            const option& opt = opts[n].get();
            std::cout   << "   " << opt.getName()
                        << opt.getDescription() << "\n\n";
        }

        return true;
    }
}
