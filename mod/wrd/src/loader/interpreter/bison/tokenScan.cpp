#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok;
        if(!eventer.getDispatcher().pop(tok)) {
            tok = yylexOrigin(val, loc, scanner);
            WRD_DI("dispatcher[queue] == null. yylexOrigin() returns %c(%d)", (char) tok, tok);
        }

        switch(tok) {
            case NEWLINE:   eventer.setScan<indentScan>(); break;
            case ENDOFFILE: return eventer.onEndOfFile();
        }

        WRD_DI("%c(%d) token dispatched.", (wrd::wchar) tok, tok);
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
            return eventer.onIndent(cur, tok);
        else if(cur < prev)
            return eventer.onDedent(cur, tok);

        eventer.setScan<normalScan>();
        return tok;
    }

    indentScan* indentScan::_instance = new indentScan();

}
