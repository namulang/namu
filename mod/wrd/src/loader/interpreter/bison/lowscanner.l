%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "../loweventer.hpp"
#include <iostream>
#include <functional>

#define YY_DECL int yylexOrigin(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yyget_lineno(yyscanner); \
                       yylloc->first_column = yylloc->colcnt; yylloc->last_column = yylloc->colcnt+yyleng-1; \
                       yylloc->colcnt += yyleng;
}

/*  ============================================================================================
    |                                      FLEX DEFINITIONS                                    |
    ============================================================================================  */

%option reentrant bison-bridge bison-locations
%option extra-type="wrd::loweventer*"
%option yylineno



/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%




[[:digit:]]+ {
    yylval->nint = atoi(yytext);
    return INT;
}

";" {
    return yytext[0];
}

[[:space:]]+ ;

%%
/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

int yywrap(yyscan_t scanner) {
    // TODO:
    return 1;
}

int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner) {
    wrd::loweventer* eventer = yyget_extra(yyscanner);
    wrd::scanMode* mode = &eventer->getScanMode();
    if(!mode) // init: scanMode
        eventer->setScanMode(mode = new wrd::indentMode());

    return mode->onScan(*eventer, yylval_param, yylloc_param, yyscanner);
}
