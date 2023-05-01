%code top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */
    #include <iostream>
    #include <sstream>
    using std::cout;
    #include "../loweventer.hpp"
    #include "../../../builtin.hpp"
    using namespace namu;

    #define YYLLOC_DEFAULT(Current, Rhs, N) \
        do { \
          if(N) { \
              (Current).start = YYRHSLOC (Rhs, 1).start ; \
              (Current).end = YYRHSLOC (Rhs, N).end; \
          } else { \
              (Current).start.row = (Current).end.row = YYRHSLOC (Rhs, 0).end.row; \
              (Current).start.col = (Current).end.col = YYRHSLOC (Rhs, 0).end.col; \
          } \
          yyget_extra(scanner)->onSrcArea(Current); \
        } while(0)
}

/*  ============================================================================================
    |                                          C++ DECLS                                       |
    ============================================================================================  */

%code requires {
    #include "../../../ast/point.hpp"
    #include "../../../ast/args.hpp"
    #include "../defBlock.hpp"

    typedef void* yyscan_t;

    namespace namu {
        class node;
        class obj;
        class immutableTactic;
        template <typename K, typename V, typename TACTIC> class tnmap;
        typedef tnmap<std::string, node, immutableTactic> scope;
        typedef tstr<node> str;
        template <typename T, typename WRP> class tnarr;
        typedef tnarr<node> narr;
    }

    struct lloc : public namu::area {
        int colcnt;

        void rel() {
            colcnt = 0;
            namu::area::rel();
        }
    };
}

%code provides {
    extern int yylineno;
    extern char* yytext;
    namespace namu {
        class loweventer;
    }

    extern "C" {
        int yylex(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void yyset_lineno(int linenumber, yyscan_t scanner);
        namu::loweventer* yyget_extra(yyscan_t scanner);
        char* yyget_text(yyscan_t scanner);
        void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg);
    }

    void _onEndParse(yyscan_t scanner);
}

/*  ============================================================================================
    |                                         BISON FLAGS                                      |
    ============================================================================================  */

%union {
    char asChar;
    int asInt;
    std::string* asStr;
    bool asBool;
    float asFlt;
    namu::node* asNode;
    namu::obj* asObj;
    namu::narr* asNarr;
    namu::scope* asScope;
    namu::defBlock* asDefBlock;
    namu::args* asArgs;
}

%define api.pure
%define parse.error custom
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%define api.location.type {lloc}
%expect 9
%require "3.8.1"

/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

// mode:
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT SCAN_MODE_INDENT_IGNORE SCAN_MODE_END

// valueless-token:
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS DOUBLE_DOT PACK ARROW TAB ASSIGN DEFASSIGN
%token OPEN_CLOSE_SQUARE_BRACKET GE LE EQ NE LOGICAL_AND LOGICAL_OR LSHIFT RSHIFT
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN OR_ASSIGN AND_ASSIGN XOR_ASSIGN
//  primitive-type:
%token VOIDTYPE INTTYPE STRTYPE BOOLTYPE FLTTYPE NULTYPE CHARTYPE
//  reserved-keyword:
%token IF _ELSE_ AKA RET AS DEF FOR BREAK NEXT _IN_ /* use prefix '_' for windows compatibility.*/
%token _WHILE_ ELIF

// value-holding-token:
%token <asChar> CHARVAR
%token <asInt> INTVAL
%token <asFlt> FLTVAL
%token <asBool> BOOLVAL
%token <asStr> NAME STRVAL

// nonterminal:
%type <asNode> compilation-unit block indentblock
%type <asNarr> packDotname
%type <asNode> dotname dotname-item
//  term:
%type <asNode> term unary postfix primary func-call
%type <asNarr> list list-items
%type <asArgs> typenames typeparams
//  keyword:
%type <asNode> ret
%type <asNode> if ifing for break next while
%type <asNode> aka aka-default aka-deduced
%type <asObj> pack
//  expr:
%type <asNode> stmt expr expr-line expr-compound expr1 expr2 expr3 expr4 expr5 expr6 expr7 expr8 expr9 expr10 assign-compound assign-line
%type <asNode> type
%type <asNode> defstmt defexpr-line defexpr-line-except-aka defexpr-compound
%type <asDefBlock> defblock
//      value:
%type <asNode> defvar defvar-exp-no-initial-value defvar-exp-initial-value defarray-initial-value
%type <asNode> defvar-compound
%type <asNode> defseq
//      func:
%type <asNode> deffunc deffunc-default deffunc-deduction
%type <asNode> deffunc-lambda deffunc-lambda-default deffunc-lambda-deduction
//      obj:
%type <asNode> defobj defobj-default defobj-default-generic

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
/*%right ?? ?? */
/*%left ?? ?? */






/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

compilation-unit: pack defblock {
                tstr<obj> pak(*$1);
                tstr<defBlock> lifeBlock($2);
                yyget_extra(scanner)->onCompilationUnit(*pak, *lifeBlock);
                _onEndParse(scanner);
              }

expr: expr-line { $$ = $1; }
    | expr-compound { $$ = $1; }

stmt: expr-line NEWLINE { $$ = $1; }
    | ret { $$ = $1; }
    | break { $$ = $1; }
    | next { $$ = $1; }
    | expr-compound { $$ = $1; }

block: %empty {
     $$ = yyget_extra(scanner)->onBlock();
   } | block stmt {
     $$ = yyget_extra(scanner)->onBlock($1->cast<blockExpr>(), *$2);
   }

// term:
term: unary { $$ = $1; }

unary: postfix {
     $$ = $1;
   } | DOUBLE_PLUS unary {
     $$ = yyget_extra(scanner)->onUnaryDoublePlus(*$2);
   } | DOUBLE_MINUS unary {
     $$ = yyget_extra(scanner)->onUnaryDoubleMinus(*$2);
   } | '+' unary {
     $$ = $2;
   } | '-' unary {
     $$ = yyget_extra(scanner)->onUnaryMinus(*$2);
   } | '!' unary {
     $$ = yyget_extra(scanner)->onUnaryNot(*$2);
   } | '~' unary {
     $$ = yyget_extra(scanner)->onUnaryBitwiseNot(*$2);
   }

func-call: type list {
        tstr<narr> argsLife($2);
        str typeLife($1);
        $$ = yyget_extra(scanner)->onRunExpr(*typeLife, *argsLife);
      }

dotname-item: NAME {
            $$ = yyget_extra(scanner)->onDotname(std::string(*$1));
            free($1);
          } | func-call {
            // $$ = yyget_extra(scanner)->onFillFromOfFuncCall(*new getExpr("me"), $1->cast<runExpr>());
            // $1 is still on heap without binder
            // TODO: convert $1 into getExpr
          }


dotname: dotname-item {
       $$ = $1;
     } | dotname '.' dotname-item {
       $$ = yyget_extra(scanner)->onDotname($1->cast<getExpr>(), $3->cast<getExpr>());
     }

list-items: expr {
            $$ = yyget_extra(scanner)->onList($1);
        } | list-items ',' expr {
            $$ = yyget_extra(scanner)->onList(*$1, $3);
        }

list: '(' list-items ')' {
    $$ = $2;
  } | '(' ')' {
    $$ = yyget_extra(scanner)->onList();
  }

postfix: primary {
       $$ = $1;
     } | postfix DOUBLE_MINUS {
        $$ = yyget_extra(scanner)->onUnaryPostfixDoubleMinus(*$1);
     } | postfix DOUBLE_PLUS {
        $$ = yyget_extra(scanner)->onUnaryPostfixDoublePlus(*$1);
     } | postfix '.' NAME {
        $$ = yyget_extra(scanner)->onGet(*$1, *$3);
        free($3);
     } | postfix '.' func-call {
        $$ = yyget_extra(scanner)->onFillFromOfFuncCall(*$1, $3->cast<runExpr>());
     } | func-call {
        $$ = $1;
        // $1 is still on heap without binder
     } | postfix '[' expr ']' {
        $$ = yyget_extra(scanner)->onGetElem(*$1, *$3);
     }

primary: INTVAL {
       $$ = yyget_extra(scanner)->onPrimitive<nInt>($1);
     } | STRVAL {
       $$ = yyget_extra(scanner)->onPrimitive<nStr>(*$1);
       free($1);
     } | FLTVAL {
       $$ = yyget_extra(scanner)->onPrimitive<nFlt>($1);
     } | BOOLVAL {
       $$ = yyget_extra(scanner)->onPrimitive<nBool>($1);
     } | CHARVAR {
       $$ = yyget_extra(scanner)->onPrimitive<nChar>($1);
     } | '(' expr ')' {
        // TODO: list should contain 1 element.
        $$ = $2;
     } | NAME {
        $$ = yyget_extra(scanner)->onGet(*$1);
        free($1);
     }

// expr:
//  structure:
expr-line: defexpr-line { $$ = $1; }
         | expr10 { $$ = $1; }
         | assign-line { $$ = $1; }
         | defarray-initial-value { $$ = $1; }
         | defseq { $$ = $1; }

expr-compound: defexpr-compound { $$ = $1; }
             | if { $$ = $1; }
             | assign-compound { $$ = $1; }
             | for { $$ = $1; }
             | while { $$ = $1; }

assign-line: expr10 ASSIGN expr10 {
            $$ = yyget_extra(scanner)->onAssign(*$1, *$3);
         }
assign-compound: expr10 ASSIGN expr-compound {
                $$ = yyget_extra(scanner)->onAssign(*$1, *$3);
             }



//  expr-line:
expr10: expr9 {
        $$ = $1;
    } | expr10 ADD_ASSIGN expr9 {
        $$ = yyget_extra(scanner)->onAddAssign(*$1, *$3);
    } | expr10 SUB_ASSIGN expr9 {
        $$ = yyget_extra(scanner)->onSubAssign(*$1, *$3);
    } | expr10 MUL_ASSIGN expr9 {
        $$ = yyget_extra(scanner)->onMulAssign(*$1, *$3);
    } | expr10 DIV_ASSIGN expr9 {
        $$ = yyget_extra(scanner)->onDivAssign(*$1, *$3);
    } | expr10 MOD_ASSIGN expr9 {
        $$ = yyget_extra(scanner)->onModAssign(*$1, *$3);
    }

expr9: expr8 {
    $$ = $1;
   } | expr9 LOGICAL_OR expr8 {
    $$ = yyget_extra(scanner)->onOr(*$1, *$3);
   } | expr9 LOGICAL_AND expr8 {
    $$ = yyget_extra(scanner)->onAnd(*$1, *$3);
   }

expr8: expr7 {
    $$ = $1;
   } | expr8 LSHIFT expr7 {
    $$ = yyget_extra(scanner)->onLShift(*$1, *$3);
   } | expr8 RSHIFT expr7 {
    $$ = yyget_extra(scanner)->onRShift(*$1, *$3);
   }

expr7: expr6 {
    $$ = $1;
   } | expr7 '>' expr6 {
    $$ = yyget_extra(scanner)->onGt(*$1, *$3);
   } | expr7 '<' expr6 {
    $$ = yyget_extra(scanner)->onLt(*$1, *$3);
   } | expr7 GE expr6 {
    $$ = yyget_extra(scanner)->onGe(*$1, *$3);
   } | expr7 LE expr6 {
    $$ = yyget_extra(scanner)->onLe(*$1, *$3);
   } | expr7 EQ expr6 {
    $$ = yyget_extra(scanner)->onEq(*$1, *$3);
   } | expr7 NE expr6 {
    $$ = yyget_extra(scanner)->onNe(*$1, *$3);
   }

expr6: expr5 {
     $$ = $1;
   } | expr6 '|' expr5 {
     $$ = yyget_extra(scanner)->onBitwiseOr(*$1, *$3);
   }

expr5: expr4 {
    $$ = $1;
   } | expr5 '^' expr4 {
    $$ = yyget_extra(scanner)->onBitwiseXor(*$1, *$3);
   }

expr4: expr3 {
    $$ = $1;
   } | expr4 '&' expr3 {
    $$ = yyget_extra(scanner)->onBitwiseAnd(*$1, *$3);
   }

expr3: expr2 {
    $$ = $1;
   } | expr3 '+' expr2 {
    $$ = yyget_extra(scanner)->onAdd(*$1, *$3);
   } | expr3 '-' expr2 {
    $$ = yyget_extra(scanner)->onSub(*$1, *$3);
   }

expr2: expr1 {
    $$ = $1;
   } | expr2 '*' expr1 {
    $$ = yyget_extra(scanner)->onMul(*$1, *$3);
   } | expr2 '/' expr1 {
    $$ = yyget_extra(scanner)->onDiv(*$1, *$3);
   } | expr2 '%' expr1 {
    $$ = yyget_extra(scanner)->onMod(*$1, *$3);
   }

expr1: term { $$ = $1;
   } | expr1 AS type {
     $$ = yyget_extra(scanner)->onAs(*$1, *$3);
   }

ret: RET NEWLINE {
    $$ = yyget_extra(scanner)->onRet();
 } | RET expr-line NEWLINE {
    $$ = yyget_extra(scanner)->onRet(*$2);
 } | RET expr-compound {
    $$ = yyget_extra(scanner)->onRet(*$2);
 }

break: BREAK NEWLINE {
    $$ = yyget_extra(scanner)->onBreak();
   } | BREAK expr-line NEWLINE {
    $$ = yyget_extra(scanner)->onBreak(*$2);
   } | BREAK expr-compound {
    $$ = yyget_extra(scanner)->onBreak(*$2);
   }

next: NEXT NEWLINE {
    $$ = yyget_extra(scanner)->onNext();
   }

ifing: IF expr-line indentblock {
    $$ = yyget_extra(scanner)->onIf(*$2, $3->cast<blockExpr>());
   } | ifing ELIF expr-line indentblock {
    $$ = yyget_extra(scanner)->onElif($1->cast<ifExpr>(), *$3, $4->cast<blockExpr>());
   }

if: ifing {
    $$ = yyget_extra(scanner)->onEndOfIf();
} | ifing _ELSE_ indentblock {
    $$ = yyget_extra(scanner)->onElse($1->cast<ifExpr>(), $3->cast<blockExpr>());
  }


for: FOR NAME _IN_ expr-line indentblock {
    $$ = yyget_extra(scanner)->onFor(std::string(*$2), *$4, $5->cast<blockExpr>());
    free($2);
 }

while: _WHILE_ expr-line indentblock {
     $$ = yyget_extra(scanner)->onWhile(*$2, $3->cast<blockExpr>());
   }

aka: aka-default { $$ = $1; }
   | aka-deduced { $$ = $1; }
aka-default: AKA dotname NAME {
            // dotname only available getExpr. need to verify in akaExpr
            $$ = yyget_extra(scanner)->onAkaDefault($2->cast<getExpr>(), std::string(*$3));
            free($3);
         }
aka-deduced: AKA dotname {
            const getExpr& e = $2->cast<getExpr>();
            $$ = yyget_extra(scanner)->onAkaDefault(e, e.getSubName());
         }

// defs:
//  structure:
defexpr-line: defexpr-line-except-aka { $$ = $1; }
            | aka { $$ = $1; }
defexpr-line-except-aka: defvar { $$ = $1; }
defexpr-compound: deffunc { $$ = $1; }
                | defobj { $$ = $1; }
                | defvar-compound { $$ = $1; }
defstmt: defexpr-line NEWLINE { $$ = $1; }
       | defexpr-compound { $$ = $1; }
defblock: %empty {
        $$ = yyget_extra(scanner)->onDefBlock();
      } | defblock defstmt {
        str lifeStmt($2);
        $$ = yyget_extra(scanner)->onDefBlock(*$1, *lifeStmt);
      }

//  type:
type: VOIDTYPE { $$ = yyget_extra(scanner)->onPrimitive<nVoid>(); }
    | INTTYPE { $$ = yyget_extra(scanner)->onPrimitive<nInt>(); }
    | CHARTYPE { $$ = yyget_extra(scanner)->onPrimitive<nChar>(); }
    | STRTYPE { $$ = yyget_extra(scanner)->onPrimitive<nStr>(); }
    | BOOLTYPE { $$ = yyget_extra(scanner)->onPrimitive<nBool>(); }
    | FLTTYPE { $$ = yyget_extra(scanner)->onPrimitive<nFlt>(); }
    | NAME { // TODO: handle 'as' expr
        $$ = yyget_extra(scanner)->onGet(*$1);
        free($1);
  } | type OPEN_CLOSE_SQUARE_BRACKET {
        $$ = yyget_extra(scanner)->onGetArray(*$1);
  } | NAME typeparams {
        tstr<args> argsLife($2);
        $$ = yyget_extra(scanner)->onGetGeneric(*$1, *argsLife);
        free($1);
  }

//  typeparams:
typeparams: '<' typenames '>' { $$ = $2; }
typenames: type {
            $$ = yyget_extra(scanner)->onTypeNames(*$1);
       } | typenames ',' type {
            $$ = yyget_extra(scanner)->onTypeNames(*$1, *$3);
       }

//  variable:
defvar: defvar-exp-no-initial-value { $$ = $1; }
      | defvar-exp-initial-value { $$ = $1; }

defvar-exp-no-initial-value: NAME type { // exp means 'explicitly'
                             $$ = yyget_extra(scanner)->onDefVar(*$1, *$2);
                             free($1);
                         }
defvar-exp-initial-value: NAME DEFASSIGN expr-line {
                          $$ = yyget_extra(scanner)->onDefAssign(*$1, *$3);
                          free($1);
                      }

defvar-compound: NAME DEFASSIGN expr-compound {
                $$ = yyget_extra(scanner)->onDefAssign(*$1, *$3);
                free($1);
             }

defarray-initial-value: '{' list-items '}' {
                        $$ = yyget_extra(scanner)->onDefArray(*$2);
                    }
defseq: expr10 DOUBLE_DOT expr10 {
        $$ = yyget_extra(scanner)->onDefSeq(*$1, *$3);
    }

//  obj:
defobj: defobj-default { $$ = $1; }
      | defobj-default-generic { $$ = $1; }
defobj-default: DEF NAME NEWLINE INDENT defblock DEDENT {
            $$ = yyget_extra(scanner)->onDefObj(std::string(*$2), *$5);
            free($2);
            }
defobj-default-generic: DEF NAME typeparams NEWLINE INDENT defblock DEDENT {
                    tstr<args> argsLife($3);
                    $$ = yyget_extra(scanner)->onDefObjGeneric(*$2, *argsLife, *$6);
                    free($2);
                    }
//  func:
deffunc: deffunc-default { $$ = $1; }
       | deffunc-deduction { $$ = new blockExpr(); /* TODO: */ }
       | deffunc-lambda { $$ = new blockExpr(); /* TODO: */ }
deffunc-default: NAME list type indentblock {
                // take bind of exprs instance: because it's on heap. I need to free.
                tstr<narr> list($2);
                str typeLife($3);
                $$ = yyget_extra(scanner)->onFunc(*$1, *list, *typeLife, $4->cast<blockExpr>());
                free($1);
             }
deffunc-deduction: NAME list indentblock {
                // TODO: then free it
               }

deffunc-lambda: deffunc-lambda-default {
            } | deffunc-lambda-deduction {
            }

deffunc-lambda-default: list type indentblock {
                    // checks list that it's NAME.
                     }
deffunc-lambda-deduction: list indentblock {
                    // checks list that it's NAME.
                      }

indentblock: NEWLINE INDENT block DEDENT { $$ = $3; }

//  pack:
packDotname: NAME {
             $$ = yyget_extra(scanner)->onPackDotname(std::string(*$1));
             free($1);
         } | packDotname '.' NAME {
             $$ = yyget_extra(scanner)->onPackDotname(*$1, std::string(*$3));
             free($3);
         }
pack: PACK packDotname NEWLINE { $$ = yyget_extra(scanner)->onPack(*$2); }
    | %empty { $$ = yyget_extra(scanner)->onPack(); }


%%

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

static std::string traceErr(const yypcontext_t* ctx, yyscan_t scanner) {
    constexpr nint TOKEN_MAX = 5;
    yysymbol_kind_t tokens[TOKEN_MAX];
    ncnt expected = yypcontext_expected_tokens(ctx, tokens, TOKEN_MAX);
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
    yysymbol_kind_t symbol = yypcontext_token(ctx);

    if(symbol != YYSYMBOL_YYUNDEF)
        // this's similar to call 'onSrcErr', but loweventer._srcArea is invalid.
        // so I can't use it now.
        eventer->onErr(yypcontext_location(ctx)->start, errCode::SYNTAX_ERR, traceErr(ctx, scanner).c_str(), yysymbol_name(symbol));
    _onEndParse(scanner);
    return 0;
}

void _onEndParse(yyscan_t scanner) {
    yyget_extra(scanner)->onEndParse();
    yyset_lineno(0, scanner);
}

// errors except syntax will come here. for instance, when available memory doesn't exist.
void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    yyget_extra(scanner)->onErr(errCode::MSG, msg);
}
