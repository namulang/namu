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
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS
//  primitive-type:
%token VOID INT STR BOOL FLT NUL
//  reserved-keyword:
%token IF

// value-holding-token:
%token <integer> INTVAL
%token <str> NAME STRVAL

// nonterminal:
%type <voidp> compilation-unit block indentblock
//  term:
%type <voidp> term unary postfix primary
//      tier:
%type <voidp> expr expr1 expr2 expr3 expr4 expr5 expr6 expr7 expr8 expr9 expr10

//  keyword:
%type <voidp> keywordexpr if
//  def:
%type <voidp> defexpr
//      value:
%type <voidp> defval-exp-no-initial-value
//      func:
%type <voidp> param params paramlist
%type <voidp> deffunc-default

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
postfix: DOUBLE_MINUS {
     } | DOUBLE_PLUS {
     }
primary: INTVAL {
       WRD_DI("INTVAL(%d)", yylval.integer);
     } | STRVAL {
       WRD_DI("STRVAL(%s)", yylval.string);
     } | '(' expr ')' {
     }

// term:
term: unary {
   }

// expr:
expr: expr10 {
  } | keywordexpr {
  } | defexpr {
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
   } | expr2 '+' expr1 {
   } | expr2 '-' expr1 {
   }

expr1: term {
   } | expr1 '*' term {
   } | expr1 '/' term {
   }


// keyword:
keywordexpr: if {
         }
if: IF expr indentblock {
    // TODO:
    }

// defs:
//      type:
type: VOID {
  } | INT {
  } | STR {
  } | BOOL {
  } | FLT {
  } | NAME {
  }

//      variable:
defexpr: defval-exp-no-initial-value {
     } | deffunc-default {
     }
defval-exp-no-initial-value: NAME type { // exp means 'explicitly'
                         }

//      param:
param: defval-exp-no-initial-value {
   }
params: param {
    } | params ',' param {
    }
paramlist: '(' params ')' {
       } | '(' ')' {
       }

//      func:
deffunc-default: NAME paramlist type indentblock {
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
