#include "tokenDispatcher.hpp"
#include "lowscanner.hpp"

YY_DECL;

int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner) {

    wrd::tokenDispatcher& disp = yyget_extra(yyscanner)->dispatcher;
    wrd::wint tok;
    if(!disp.pop(tok)) {
        WRD_DI("dispatcher is empty.");
        return yylexOrigin(yylval_param, yylloc_param, yyscanner);
    }

    WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
    return tok;
}
