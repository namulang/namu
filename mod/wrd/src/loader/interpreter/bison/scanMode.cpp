#include "scanMode.hpp"
#include "lowscanner.hpp"

YY_DECL;

namespace wrd {

    wint normalMode::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) {
        wint tok;
        if(!eventer.getDispatcher().pop(tok)) {
            WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
            tok = yylexOrigin(yylval, yylloc, yyscanner);
            if(tok == INDENT)
                eventer.setScanMode(new indentMode());
        }

        WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
        return tok;
    }

    wint indentMode::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) {
        // TODO:
        return yylexOrigin(yylval, yylloc, yyscanner);
    }
}
