#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint tokenScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok;
        tokenDispatcher& disp = eventer.getDispatcher();
        if(!disp.pop(tok)) {
            tok = yylexOrigin(val, loc, scanner);
            WRD_DI("%s: dispatcher[null]. yylexOrigin() -> %c(%d)", getType().getName().c_str(), (char) tok, tok);
        } else
            WRD_DI("%s: dispatcher[%d].dispatch(token: %c(%d)", getType().getName().c_str(), disp.len(), (char) tok, tok);

        return tok;
    }

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok = super::onScan(eventer, val, loc, scanner);
        switch(tok) {
            case NEWLINE:   eventer.setScan<indentScan>(); break;
            case ENDOFFILE: return eventer.onEndOfFile();
        }

        return tok;
    }

    normalScan* normalScan::_instance = new normalScan();

    wint indentScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        wint tok = super::onScan(eventer, val, loc, scanner);
        if(tok == NEWLINE) {
            WRD_DI("indentScan: ignore NEWLINE");
            return SCAN_AGAIN;
        }

        wcnt cur = loc->first_column;
        std::vector<wcnt>& ind = eventer.getIndents();
        if(ind.size() == 0)
            ind.push_back(cur);

        wcnt prev = ind.back();
        WRD_DI("indentScan: column check: cur[%d] prev[%d]", cur, prev);

        if(cur > prev)
            return eventer.onIndent(cur, tok);
        else if(cur < prev)
            return eventer.onDedent(cur, tok);

        eventer.setScan<normalScan>();
        return tok;
    }

    indentScan* indentScan::_instance = new indentScan();

}
