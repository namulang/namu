%code top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */
    #include <iostream>
    #include <sstream>
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

        void rel() {
            first_line = first_column = last_line = last_column = colcnt = 0;
        }
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
        void yyset_lineno(int linenumber, yyscan_t scanner);
        wrd::loweventer* yyget_extra(yyscan_t scanner);
        char* yyget_text(yyscan_t scanner);
        void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg);
    }

    void _onEndParse(YYLTYPE* loc, yyscan_t scanner);
}

/*  ============================================================================================
    |                                         BISON FLAGS                                      |
    ============================================================================================  */

%union {
    int integer;
    char character;
    void* voidp;
    char* string;
}

%define api.pure
%define parse.error custom
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%define api.location.type {lloc}
%expect 1
%require "3.8.1"

/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

// mode:
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT SCAN_MODE_INDENT_IGNORE

// valueless-token:
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS IMPORT PACK
//  primitive-type:
%token VOID INT STR BOOL FLT NUL CHAR
//  reserved-keyword:
%token IF

// value-holding-token:
%token <integer> INTVAL
%token <character> CHARVAR
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
    _onEndParse(yylocp, scanner);
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
     } | CHARVAR {
        WRD_DI("CHARVAL(%c)", yylval.character);
     } | list %expect 1 {
        //  known shift/reduce conflict on the syntax:
        //      First example: list • NEWLINE INDENT block DEDENT block DEDENT $end
        //          e.g. (a) •
        //                  expectLambdaDoSometing()
        //      Second example: list • NEWLINE DEDENT $end
        //          e.g. (just_primary) •

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
  } | CHAR {
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

static std::string traceErr(const yypcontext_t* ctx, yyscan_t scanner) {
    constexpr wint TOKEN_MAX = 5;
    yysymbol_kind_t tokens[TOKEN_MAX];
    wcnt expected = yypcontext_expected_tokens(ctx, tokens, TOKEN_MAX);
    if(expected <= 0)
        return "nothing";

    std::stringstream ss;
    ss << "'" << yysymbol_name(tokens[0]) << "'";
    for(int n=1; n < expected ;n++)
        ss << ", '" << yysymbol_name(tokens[n]) << "'";
    return ss.str();

    // TODO: high quality error trace..
}

// when bison claims that it can't parse any further, this func will be called.
// it means that error recovery has been failed already.
static int yyreport_syntax_error(const yypcontext_t* ctx, yyscan_t scanner) {
    auto* eventer = yyget_extra(scanner);
    const YYLTYPE* loc = yypcontext_location(ctx);
    area srcArea = {{loc->first_line, loc->first_column}, {loc->last_line, loc->last_column}};
    yysymbol_kind_t symbol = yypcontext_token(ctx);

    if(symbol != YYSYMBOL_YYUNDEF)
        eventer->onErr(new srcErr(err::ERR, 7, srcArea, traceErr(ctx, scanner).c_str(), yysymbol_name(symbol)));
    _onEndParse((YYLTYPE*) loc, scanner);
    return 0;
}

void _onEndParse(YYLTYPE* loc, yyscan_t scanner) {
    yyset_lineno(0, scanner);
    loc->rel();
    yyget_extra(scanner)->onEndParse({loc->first_line, loc->first_column});
}

// errors except syntax will come here. for instance, when available memory doesn't exist.
void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    yyget_extra(scanner)->onErr(new err(err::ERR, 8, msg));
}
