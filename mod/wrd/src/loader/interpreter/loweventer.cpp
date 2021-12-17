#include "loweventer.hpp"
#include "lowparser.hpp"

namespace wrd {

    WRD_DEF_ME(loweventer)

    namespace {
        tokenScanMode normalScan = [](loweventer& eventer, tokenScan orgScanner) -> wint {
            wint tok;
            if(!eventer.getDispatcher().pop(tok)) {
                WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
                tok = orgScanner();
                if(tok == ::yytokentype::INT)
                    eventer.setTokenScanMode(normalScan); // TODO:
            }

            WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
            return tok;
        };
    }

    me::loweventer(): _mode(normalScan) {}
}
