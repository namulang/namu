%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "parser.hpp"
#include <iostream>

#define YY_DECL int yylexOrigin(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
}

/*  ============================================================================================
    |                                      FLEX DEFINITIONS                                    |
    ============================================================================================  */

%option reentrant bison-bridge bison-locations
%option extra-type="wrd::parser*"



/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%




[[:digit:]]+ {
    yylval->nint = atoi(yytext);
    std::cout << "INT: " << yytext << "\n";
    return INT;
}

";" {
    return yytext[0];
}

%%
/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

int yywrap(yyscan_t scanner) {
    // TODO:
    return 1;
}

int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner) {

    wrd::tokenDispatcher& disp = yyget_extra(yyscanner)->getDispatcher();
    wrd::wint tok;
    if(!disp.pop(tok)) {
        WRD_DI("dispatcher[queue] == null. route to yylexOrigin()");
        return yylexOrigin(yylval_param, yylloc_param, yyscanner);
    }

    WRD_DI("enqueued %c(%d) token dispatched.", (wrd::wchar) tok, tok);
    return tok;
}
