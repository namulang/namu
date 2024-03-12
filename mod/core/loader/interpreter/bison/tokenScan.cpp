#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace namu {

    nint tokenScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        nbool dum;
        return onScan(eventer, val, loc, scanner, dum);
    }

    nint tokenScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, nbool& isBypass) {
        tokenDispatcher& disp = eventer.getDispatcher();
        nint tok;

        if(!(isBypass = disp.pop(tok)))
            tok = yylexOrigin(val, loc, scanner);
        if(tok == ENDOFFILE)
            tok = eventer.onTokenEndOfFile();

        NAMU_DI("%s: dispatcher[%d]%s(token: %c[%d]) at %d,%d", getType().getName().c_str(), disp.len(), isBypass ? ".dispatch" : " lowscanner", tok <= 127 ? (char) tok : '?', tok, loc->start.row, loc->start.col);
        return tok;
    }

    nint normalScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, nbool& isBypass) {
        nint tok = super::onScan(eventer, val, loc, scanner, isBypass);
        switch(tok) {
            case TAB:
                return SCAN_AGAIN;
        }

        return tok;
    }

    normalScan* normalScan::_instance = new normalScan();

    nint indentScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, nbool& isBypass) {
        nint tok = super::onScan(eventer, val, loc, scanner, isBypass);
        switch(tok) {
            case NEWLINE:
                if(!isBypass) {
                    NAMU_DI("indentScan: ignore NEWLINE");
                    return SCAN_AGAIN;
                }
                break;
        }

        eventer.setScan<normalScan>();
        if(isBypass) return tok;

        ncnt cur = loc->start.col;
        std::vector<ncnt>& ind = eventer.getIndents();
        if(ind.size() == 0) {
            NAMU_DI("indentScan: initial indent lv: %d", cur);
            ind.push_back(cur);
        }

        ncnt prev = ind.back();
        NAMU_DI("indentScan: column check: cur[%d] prev[%d]", cur, prev);

        if(cur > prev)
            return eventer.onIndent(cur, tok);
        else if(cur < prev)
            return eventer.onDedent(cur, tok);

        return tok;
    }

    indentScan* indentScan::_instance = new indentScan();

}
