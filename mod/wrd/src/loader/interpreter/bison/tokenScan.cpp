#include "tokenScan.hpp"
#include "lowscanner.hpp"
#include <iostream>

YY_DECL;

namespace wrd {

    wint tokenScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) {
        tokenDispatcher& disp = eventer.getDispatcher();
        wint tok;
        isBypass = disp.pop(tok);
        WRD_DI("%s: dispatcher[%d]%s(token: %c[%d])", getType().getName().c_str(), disp.len(), isBypass ? ".dispatch" : " lowscanner", (char) tok, tok);

        if(!isBypass)
            tok = yylexOrigin(val, loc, scanner);

        if(tok == ENDOFFILE)
            return eventer.onEndOfFile();
        return tok;
    }

    wint normalScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) {
        return super::onScan(eventer, val, loc, scanner, isBypass);
    }

    normalScan* normalScan::_instance = new normalScan();

    wint indentScan::onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner, wbool& isBypass) {
        wint tok = super::onScan(eventer, val, loc, scanner, isBypass);
        if(!isBypass && tok == NEWLINE) {
            WRD_DI("indentScan: ignore NEWLINE");
            return SCAN_AGAIN;
        }

        eventer.setScan<normalScan>();
        if(isBypass) return tok;

        wcnt cur = loc->first_column;
        std::vector<wcnt>& ind = eventer.getIndents();
        if(ind.size() == 0) { WRD_DI("indentScan: initial indent lv: %d", cur); ind.push_back(cur);
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
