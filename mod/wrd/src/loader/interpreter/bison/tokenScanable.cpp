#include "tokenScanable.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) {
        wint tok;
        if(!eventer.getDispatcher().pop(tok)) {
            WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
            tok = yylexOrigin(yylval, yylloc, yyscanner);
            if(tok == NEWLINE)
                eventer.setScan<indentScan>();
        }

        WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
        return tok;
    }

    normalScan* normalScan::_instance = new normalScan();


    wint indentScan::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) {
        wcnt cur = yylloc->first_column;
        wcnt prev = eventer.getIndents().back();

        if(cur > prev)
            return _onIndent(eventer, cur);
        else if(cur < prev)
            return _onDedent(eventer, cur);

        eventer.setScan<normalScan>();
        return tokenScanable::DO_RESCAN;
    }

    indentScan* indentScan::_instance = new indentScan();

    wint indentScan::_onIndent(loweventer& ev, wcnt lv) {
        ev.getIndents().push_back(lv);
        return INDENT;
    }
    wint indentScan::_onDedent(loweventer& ev, wcnt lv) {
        // TODO:
        return 0;
    }
}
