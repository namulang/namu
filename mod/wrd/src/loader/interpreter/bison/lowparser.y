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
%token NEWLINE INDENT DEDENT IF ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS

// value-holding-token:
%token <integer> INT
%token <str> NAME STRING

// nonterminal:
%type <voidp> compilation-unit block indentblock

// term:
%type <voidp> term unary postfix primary
//  expr:
//      tier:
%type <voidp> expr expr1 expr2 expr3 expr4 expr5 expr6 expr7 expr8 expr9 expr10

//  keyword:
%type <voidp> if

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

block: expr NEWLINE {
   } | block expr NEWLINE {
   }
unary: primary {
   } | unary postfix {
   }
postfix: {
     }
primary: INT {
     } | STRING {
     } | '(' expr ')' {
     }

// term:
term: unary {
   }

// expr:
expr: expr10 {
  } | if {
  }

expr10: expr9 {
    }
expr9: expr8 {
   }
expr8: expr7 {
   }
expr7: expr6 {
   }
expr6: expr5 {
   }
expr5: expr4 {
   }
expr4: expr3 {
   }
expr3: expr2 {
   }
expr2: expr1 {
   } | expr1 '+' expr1 {
   }

expr1: term {
   } | term '*' term {
   } | term '/' term {
   }


// keyword:
if: IF indentblock {
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
