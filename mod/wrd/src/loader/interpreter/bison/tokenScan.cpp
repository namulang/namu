#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok;
        if(!eventer.getDispatcher().pop(tok)) {
            WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
            tok = yylexOrigin(val, loc, scanner);
            if(tok == NEWLINE)
                eventer.setScan<indentScan>();
        }

        WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
        return tok;
    }

    normalScan* normalScan::_instance = new normalScan();

    wint indentScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok = super::onScan(eventer, val, loc, scanner);
        if(tok == NEWLINE)
            return tokenScan::DO_RESCAN;

        wcnt cur = loc->first_column;
        wcnt prev = eventer.getIndents().back();
        WRD_DI("column check: cur[%d] prev[%d]", cur, prev);

        if(cur > prev)
            return _onIndent(eventer, cur, tok);
        else if(cur < prev)
            return _onDedent(eventer, cur, tok);

        eventer.setScan<normalScan>();
        return tok;
    }

    indentScan* indentScan::_instance = new indentScan();

    wint indentScan::_onIndent(loweventer& ev, wcnt col, wint tok) {
        WRD_DI("new indent(col: %d) of %d found.", col, ev.getIndents().size());
        ev.getIndents().push_back(col);
        return INDENT;
    }
    wint indentScan::_onDedent(loweventer& ev, wcnt col, wint tok) {
        // TODO:
        return 0;
    }
}
