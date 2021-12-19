%code top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */
    #include <iostream>
    using std::cout;
    #include "../loweventer.hpp"
    #include "../../../builtin/primitive/wInt.hpp"
    using namespace wrd;
}

/*  ============================================================================================
    |                                          C++ DECLS                                       |
    ============================================================================================  */

%code requires {
    typedef void* yyscan_t;

    struct lloc {
        int first_line, first_column;
        int last_line, last_column;
        int colcnt;
    };
}

%code provides {
    //extern wrd::sobj* root;
    extern int yylineno;
    extern char* yytext;
    namespace wrd {
        class loweventer;
    }

    extern "C" {
        int yylex(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg);
        wrd::loweventer* yyget_extra(yyscan_t scanner);
    }
}

/*  ============================================================================================
    |                                         BISON FLAGS                                      |
    ============================================================================================  */

%union {
    int nint; // n means 'native'.
    void* voidp;
}

%define api.pure
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}




/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

%token <nint> INT
%token NEWLINE
%type <voidp> compilation-unit

/*%type ?? ?? */

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
/*%right ?? ?? */
/*%left ?? ?? */






/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

compilation-unit: INT ';' {
    // TODO:
    auto* eventer = yyget_extra(scanner);
    eventer->getRoot().bind(new wInt(5));
}





%%

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    // TODO:
}
