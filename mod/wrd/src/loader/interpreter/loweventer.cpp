#include "loweventer.hpp"
#include "bison/lowparser.hpp"

namespace wrd {
    WRD_DEF_ME(loweventer)

    wint me::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t scanner) {
        return _mode->onScan(*this, yylval, yylloc, scanner);
    }

    wint me::onEndOfFile() {
        WRD_DI("tokenEvent: onEndOfFile()");
        // TODO:
        return 0; // 0 is yyterminate().
    }

    wint me::onIndent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onIndent(col: %d, tok: %d) indents.size()=%d", col, tok, _indents.size());
        _indents.push_back(col);
        _dispatcher.add(tok);
        return INDENT;
    }

    wint me::onDedent(wcnt col, wint tok) {
        WRD_DI("tokenEvent: onDedent(col: %d, tok: %d)", col, tok);

        _dispatcher.add(NEWLINE);
        _indents.pop_back();

        while(_indents.back() > col) {
            _dispatcher.add(DEDENT);
            _dispatcher.add(NEWLINE);
            WRD_DI("tokenEvent: onDedent: indentlv become %d -> %d", _indents.back(), _indents[_indents.size()-2]);
        }

        _dispatcher.add(tok);
        return DEDENT;
    }
}
