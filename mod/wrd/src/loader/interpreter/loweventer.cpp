#include "loweventer.hpp"
#include "bison/lowparser.hpp"

namespace wrd {
    WRD_DEF_ME(loweventer)

    wint me::onScan(loweventer& ev, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner) {
        int tok;
        do {
            tok = _mode->onScan(ev, val, loc, scanner);

            switch(tok) {
                case SCAN_MODE_NORMAL: setScan<normalScan>(); continue;
                case SCAN_MODE_INDENT: setScan<indentScan>(); continue;
            }
        } while(tok == SCAN_AGAIN);

        return tok;
    }

    wint me::onEndOfFile() {
        WRD_DI("tokenEvent: onEndOfFile() indents.size()=%d", _indents.size());
        if(_indents.size() > 1) {
            _dispatcher.addFront(onDedent(0, ENDOFFILE));
            return NEWLINE;
        }

        WRD_DI("tokenEvent: onEndOfFile: it's really end of file.");
        return 0;
    }

    wint me::onIndent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onIndent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());
        _indents.push_back(col);
        _dispatcher.add(tok);
        return INDENT;
    }

    wint me::onDedent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onDedent(col: %d, tok: %d) indents.size()=", col, tok, _indents.size());

        _indents.pop_back();

        while(_indents.back() > col) {
            WRD_DI("tokenEvent: onDedent: indentlv become %d -> %d", _indents.back(), _indents[_indents.size()-2]);
            _dispatcher.add(DEDENT);
            _indents.pop_back();
        }

        _dispatcher.add(tok);
        return DEDENT;
    }
}
