#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint tokenScan::onScan(loweventer& eventer, YYSTYPE* val, yyscan_t scanner, wbool& isBypass) {
        tokenDispatcher& disp = eventer.getDispatcher();
        wint tok;
        const area& loc = eventer.getArea();

        if(!(isBypass = disp.pop(tok)))
            tok = yylexOrigin(val, (YYLTYPE*) &loc, scanner);
        if(tok == ENDOFFILE)
            tok = eventer.onEndOfFile();

        WRD_DI("%s: dispatcher[%d]%s(token: %c[%d]) at %d,%d", getType().getName().c_str(), disp.len(), isBypass ? ".dispatch" : " lowscanner", tok <= 127 ? (char) tok : '?', tok, loc.start.row, loc.start.col);
        return tok;
    }

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* val, yyscan_t scanner, wbool& isBypass) {
        return super::onScan(eventer, val, scanner, isBypass);
    }

    normalScan* normalScan::_instance = new normalScan();

    wint indentScan::onScan(loweventer& eventer, YYSTYPE* val, yyscan_t scanner, wbool& isBypass) {
        wint tok = super::onScan(eventer, val, scanner, isBypass);
        if(!isBypass && tok == NEWLINE) {
            WRD_DI("indentScan: ignore NEWLINE");
            return SCAN_AGAIN;
        }

        eventer.setScan<normalScan>();
        if(isBypass) return tok;

        wcnt cur = eventer.getArea().start.col;
        std::vector<wcnt>& ind = eventer.getIndents();
        if(ind.size() == 0) {
            WRD_DI("indentScan: initial indent lv: %d", cur);
            ind.push_back(cur);
        }

        wcnt prev = ind.back();
        WRD_DI("indentScan: column check: cur[%d] prev[%d]", cur, prev);

        if(cur > prev)
            return eventer.onIndent(cur, tok);
        else if(cur < prev)
            return eventer.onDedent(cur, tok);

        return tok;
    }

    indentScan* indentScan::_instance = new indentScan();

}
