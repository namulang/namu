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
    int integer;
    void* voidp;
    char* string;
}

%define api.pure
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%define api.location.type {lloc}




/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

// mode:
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT

// valueless-token:
%token NEWLINE INDENT DEDENT IF ENDOFFILE

// value-holding-token:
%token <integer> INT
%token <str> NAME STRING

// nonterminal:
%type <voidp> compilation-unit ifexpr lineexpr compoundexpr block indentblock

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

compilation-unit: block {
    // TODO:
    auto* eventer = yyget_extra(scanner);
    eventer->getRoot().bind(new wInt(5));
}

block: lineexpr NEWLINE {
   } | compoundexpr {
   } | block lineexpr NEWLINE {
   } | block compoundexpr {
   }

compoundexpr : ifexpr {
           }

lineexpr: INT ';' {
      } | STRING ';' {
      }

ifexpr: IF indentblock {
    // TODO:
    }

indentblock: NEWLINE INDENT block DEDENT {
         }



%%

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    // TODO:
}
