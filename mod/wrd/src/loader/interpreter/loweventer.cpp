#include "loweventer.hpp"
#include "bison/lowparser.hpp"

namespace wrd {
    WRD_DEF_ME(loweventer)

    wint me::onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t scanner) {
        return _mode->onScan(*this, yylval, yylloc, scanner);
    }
}
