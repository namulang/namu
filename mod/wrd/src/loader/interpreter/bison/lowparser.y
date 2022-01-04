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
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT SCAN_MODE_INDENT_IGNORE

// valueless-token:
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS IMPORT PACK ARROW
//  primitive-type:
%token VOID INT STR BOOL FLT NUL
//  reserved-keyword:
%token IF

// value-holding-token:
%token <integer> INTVAL
%token <str> NAME STRVAL

// nonterminal:
%type <voidp> compilation-unit block indentblock dotname
//  term:
%type <voidp> term unary postfix primary funcCall list list-items
//      tier:
%type <voidp> stmt expr expr-line expr-compound expr1 expr2 expr3 expr4 expr5 expr6 expr7 expr8 expr9 expr10

//  keyword:
%type <voidp> if import pack
//  def:
%type <voidp> defstmt defexpr-line defexpr-compound defblock
//      value:
%type <voidp> defvar defvar-exp-no-initial-value
//      func:
%type <voidp> deffunc-default
%type <voidp> deffunc-lambda deffunc-lambda-default deffunc-lambda-deduction
//      pack:
%type <voidp> defpack imports

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
/*%right ?? ?? */
/*%left ?? ?? */






/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

compilation-unit: defpack {
    // TODO:
    auto* eventer = yyget_extra(scanner);
    eventer->getRoot().bind(new wInt(5));
}

expr: expr-line {
  } | expr-compound {
  }

stmt: expr-line NEWLINE {
  } | expr-compound {
  }

block: %empty {
   } | block stmt {
   }

// term:
term: unary {
   }

unary: postfix {
   } | DOUBLE_PLUS unary { // prefix:
   } | DOUBLE_MINUS unary {
   } | '+' unary {
   } | '-' unary {
   }

funcCall: NAME list {
      }

import: IMPORT dotname NEWLINE {
    }

dotname: NAME {
    } | dotname '.' NAME {
    }

list-items: expr {
        } | list-items ',' expr {
        }

list: '(' list-items ')' {
  } | '(' ')' {
  }

postfix: primary {
     } | postfix DOUBLE_MINUS {
     } | postfix DOUBLE_PLUS {
     } | postfix '.' NAME {
     } | postfix '.' funcCall {
     } | funcCall {
     }

primary: INTVAL {
       WRD_DI("INTVAL(%d)", yylval.integer);
     } | STRVAL {
       WRD_DI("STRVAL(%s)", yylval.string);
     } | list {
       // TODO: list should contain 1 element.
     } | NAME {
     }


// expr:
//  structure:
expr-line: defexpr-line {
       } | expr10 {
       }
expr-compound: defexpr-compound {
           } | if {
           }

//  expr-line:
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
if: IF expr indentblock {
    // TODO:
    }

// defs:
//  structure:
defexpr-line: defvar {
          }
defexpr-compound: deffunc {
          }
defstmt: defexpr-line NEWLINE {
     } | defexpr-compound {
     }
defblock: %empty {
      } | defblock defstmt {
      }

//  type:
type: VOID {
  } | INT {
  } | STR {
  } | BOOL {
  } | FLT {
  } | NAME {
  }

//  variable:
defvar: defvar-exp-no-initial-value {
    }
defvar-exp-no-initial-value: NAME type { // exp means 'explicitly'
                         }

//  func:
deffunc: deffunc-default {
     } | deffunc-lambda {
     }
deffunc-default: NAME list type indentblock {
                // TODO: checks list that it's defvar
             }

deffunc-lambda: deffunc-lambda-default {
            } | deffunc-lambda-deduction {
            }

deffunc-lambda-default : list type indentblock {
                    // checks list that it's NAME.
                     }
deffunc-lambda-deduction: list indentblock {
                    // checks list that it's NAME.
                      }

indentblock: NEWLINE INDENT block DEDENT {
         }

//  pack:
imports: imports import {
     } | %empty {
     }
defpack: pack imports defblock {
     } | imports defblock {
     }
pack: PACK dotname NEWLINE {
  }



%%

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    // TODO:
}
