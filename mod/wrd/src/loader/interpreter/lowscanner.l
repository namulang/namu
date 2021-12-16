%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "loweventer.hpp"
#include <iostream>

#define YY_DECL int yylexOrigin(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
}

/*  ============================================================================================
    |                                      FLEX DEFINITIONS                                    |
    ============================================================================================  */

%option reentrant bison-bridge bison-locations
%option extra-type="wrd::loweventer*"



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
    return yyget_extra(yyscanner)->onScanToken([&]() {
    });
}
