#include "flag.hpp"
#include "../cli.hpp"

namespace namu {

    NAMU_DEF_ME(flag)

    nbool me::take(interpreter& ip, cli& c, args& a) const {
        std::regex re(_getRegExpr());
        std::vector<int> del;
        args tray;
        for(int n=0; n < a.size() ;n++) {
            if(std::regex_match(a[n], re)) {
                tray.push_back(a[n]);
                del.push_back(n);
            }
        }
        if(tray.empty()) return false;

        nbool res = _onTake(tray, c, ip);
        if(!res) return false;

        _delArgs(a, del);
        return res;
    }
}
