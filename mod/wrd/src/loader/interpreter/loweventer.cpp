#include "loweventer.hpp"

namespace wrd {

    WRD_DEF_ME(loweventer)

    wint me::onScanToken(std::function<wint()> originScanner) {
        wint tok;
        if(!_dispatcher.pop(tok)) {
            WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
            return originScanner();
        }

        WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
        return tok;
    }

}
