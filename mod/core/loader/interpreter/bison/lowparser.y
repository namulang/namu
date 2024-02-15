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
              (Current).start = YYRHSLOC (Rhs, 1).start; \
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
    namu::nchar asChar;
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
%expect 5
%require "3.8.1"

/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

// mode:
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT SCAN_MODE_INDENT_IGNORE SCAN_MODE_END

// terminal:
//  reserved-keyword:
//      use prefix '_' on some tokens for windows compatibility.
//      branch:
%token IF _ELSE_ RET NEXT BREAK
//      check:
%token _IN_ IS
//      loop:
%token _WHILE_ FOR
//      define:
%token DEF WITH AS ENUM ONLY GET SET END
//  predefined-type:
%token VOID INT STR BOOL FLT NUL BYTE CHAR ME SUPER IT CTOR PACK 
//  valueless-token:
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS DOUBLE_DOT ARROW TAB ASSIGN DEFASSIGN
%token OPEN_CLOSE_SQUARE_BRACKET GE LE EQ NE LOGICAL_AND LOGICAL_OR LSHIFT RSHIFT
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN OR_ASSIGN AND_ASSIGN XOR_ASSIGN
//  value-holding-token:
%token <asChar> CHARVAL
%token <asInt> INTVAL
%token <asFlt> FLTVAL
%token <asBool> BOOLVAL
%token <asStr> NAME STRVAL

// nonterminal:
//  basic component:
%type <asNode> compilation-unit unary postfix primary
//      expr:
//          inline:
%type <asNode> expr-line expr-line1 expr-line2 expr-line3 expr-line4 expr-line5 expr-line6 expr-line7 expr-line8 expr-line9
//          compound:
%type <asNode> expr-compound block indentblock 
%type <asDefBlock> defblock
//      stmt:
%type <asNode> allstmt stmt
%type <asNode> defstmt
//      access:
%type <asNarr> path
%type <asNode> func-access
//      func:
%type <asNode> func-call
//      tuple:
%type <asNarr> tuple tuple-items
%type <asNarr> func-call-tuple func-call-tuple-items
%type <asNode> func-call-tuple-item param-item
%type <asNarr> params param-items
//      type:
%type <asNode> type
%type <asArgs> typenames typeparams
//  keyword:
//      branch:
%type <asNode> if if-block ret next break
//      loop
%type <asNode> while for
//      define:
//          value:
%type <asNode> defvar defvar-without-initial-value defvar-initial-value defvar-getset defvar-getset-item
%type <asNode> defvar-compound
//          func:
%type <asNode> deffunc get set end
%type <asNode> lambda lambda-default lambda-deduction
//          obj:
%type <asNode> defobj defobj-default defobj-default-generic
//              container:
%type <asNode> defarray-initial-value
//              with:
%type <asNode> with-inline with-compound
//  predefined-type:
%type <asObj> pack

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
/*%right ?? ?? */
/*%left ?? ?? */






/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

// basic component:
compilation-unit: pack defblock {
                tstr<obj> pak(*$1);
                tstr<defBlock> lifeBlock($2);
                yyget_extra(scanner)->onCompilationUnit(*pak, *lifeBlock);
                _onEndParse(scanner);
              }

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
     } | postfix '[' expr-line ']' {
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
     } | CHARVAL {
       $$ = yyget_extra(scanner)->onPrimitive<nChar>($1);
     } | tuple {
        $$ = yyget_extra(scanner)->onParanthesisAsTuple(*$1);
     } | NUL {
       // ??
     } | NAME {
        $$ = yyget_extra(scanner)->onGet(*$1);
        free($1);
     } | defarray-initial-value { $$ = $1; }
       | func-access { $$ = $1; }

expr-line: expr-line9 { $$ = $1; }
         | expr-line9 DOUBLE_DOT expr-line9 {
            $$ = yyget_extra(scanner)->onDefSeq(*$1, *$3);
       }
expr-line9: expr-line8 {
    $$ = $1;
   } | expr-line9 LOGICAL_OR expr-line8 {
    $$ = yyget_extra(scanner)->onOr(*$1, *$3);
   } | expr-line9 LOGICAL_AND expr-line8 {
    $$ = yyget_extra(scanner)->onAnd(*$1, *$3);
   }
expr-line8: expr-line7 {
    $$ = $1;
   } | expr-line8 LSHIFT expr-line7 {
    $$ = yyget_extra(scanner)->onLShift(*$1, *$3);
   } | expr-line8 RSHIFT expr-line7 {
    $$ = yyget_extra(scanner)->onRShift(*$1, *$3);
   }
expr-line7: expr-line6 {
    $$ = $1;
   } | expr-line7 '>' expr-line6 {
    $$ = yyget_extra(scanner)->onGt(*$1, *$3);
   } | expr-line7 '<' expr-line6 {
    $$ = yyget_extra(scanner)->onLt(*$1, *$3);
   } | expr-line7 GE expr-line6 {
    $$ = yyget_extra(scanner)->onGe(*$1, *$3);
   } | expr-line7 LE expr-line6 {
    $$ = yyget_extra(scanner)->onLe(*$1, *$3);
   } | expr-line7 EQ expr-line6 {
    $$ = yyget_extra(scanner)->onEq(*$1, *$3);
   } | expr-line7 NE expr-line6 {
    $$ = yyget_extra(scanner)->onNe(*$1, *$3);
   }
expr-line6: expr-line5 {
     $$ = $1;
   } | expr-line6 '|' expr-line5 {
     $$ = yyget_extra(scanner)->onBitwiseOr(*$1, *$3);
   } | expr-line6 IS type {
        // ??
   } | expr-line6 _IN_ expr-line5 {
        // ??
   }
expr-line5: expr-line4 {
    $$ = $1;
   } | expr-line5 '^' expr-line4 {
    $$ = yyget_extra(scanner)->onBitwiseXor(*$1, *$3);
   }
expr-line4: expr-line3 {
    $$ = $1;
   } | expr-line4 '&' expr-line3 {
    $$ = yyget_extra(scanner)->onBitwiseAnd(*$1, *$3);
   }
expr-line3: expr-line2 {
    $$ = $1;
   } | expr-line3 '+' expr-line2 {
    $$ = yyget_extra(scanner)->onAdd(*$1, *$3);
   } | expr-line3 '-' expr-line2 {
    $$ = yyget_extra(scanner)->onSub(*$1, *$3);
   }
expr-line2: expr-line1 {
    $$ = $1;
   } | expr-line2 '*' expr-line1 {
    $$ = yyget_extra(scanner)->onMul(*$1, *$3);
   } | expr-line2 '/' expr-line1 {
    $$ = yyget_extra(scanner)->onDiv(*$1, *$3);
   } | expr-line2 '%' expr-line1 {
    $$ = yyget_extra(scanner)->onMod(*$1, *$3);
   }
expr-line1: unary { $$ = $1;
   } | expr-line1 AS type {
     $$ = yyget_extra(scanner)->onAs(*$1, *$3);
   }

//      compound:
expr-compound: if { $$ = $1; }
             | expr-line9 ASSIGN expr-compound {
                $$ = yyget_extra(scanner)->onAssign(*$1, *$3);
           } | for { $$ = $1; }
             | while { $$ = $1; }
             | end { $$ = $1; }

block: allstmt {
     $$ = yyget_extra(scanner)->onBlock();
   } | block allstmt {
     $$ = yyget_extra(scanner)->onBlock($1->cast<blockExpr>(), *$2);
   }

indentblock: NEWLINE INDENT block DEDENT { $$ = $3; }

defblock: defstmt {
        $$ = yyget_extra(scanner)->onDefBlock();
      } | defblock defstmt {
        str lifeStmt($2);
        $$ = yyget_extra(scanner)->onDefBlock(*$1, *lifeStmt);
      }

//  stmt:
allstmt: stmt { $$ = $1; }
       | defstmt { $$ = $1; }
stmt: expr-line NEWLINE { $$ = $1; }
    | ret { $$ = $1; }
    | break { $$ = $1; }
    | next { $$ = $1; }
    | expr-compound { $$ = $1; }
    | expr-line9 ASSIGN expr-line NEWLINE {
        $$ = yyget_extra(scanner)->onAssign(*$1, *$3);
  } | expr-line9 ADD_ASSIGN expr-line9 NEWLINE {
        $$ = yyget_extra(scanner)->onAddAssign(*$1, *$3);
  } | expr-line9 SUB_ASSIGN expr-line9 NEWLINE {
        $$ = yyget_extra(scanner)->onSubAssign(*$1, *$3);
  } | expr-line9 MUL_ASSIGN expr-line9 NEWLINE {
        $$ = yyget_extra(scanner)->onMulAssign(*$1, *$3);
  } | expr-line9 DIV_ASSIGN expr-line9 NEWLINE {
        $$ = yyget_extra(scanner)->onDivAssign(*$1, *$3);
  } | expr-line9 MOD_ASSIGN expr-line9 NEWLINE {
        $$ = yyget_extra(scanner)->onModAssign(*$1, *$3);
  }

defstmt: defvar NEWLINE { $$ = $1; }
       | with-inline NEWLINE { $$ = $1; }
       | deffunc { $$ = $1; }
       | with-compound { $$ = $1; }
       | defobj { $$ = $1; }
       | defvar-compound { $$ = $1; }

//  access:
path: NAME {
             $$ = yyget_extra(scanner)->onPath(std::string(*$1));
             free($1);
         } | path '.' NAME {
             $$ = yyget_extra(scanner)->onPath(*$1, std::string(*$3));
             free($3);
         }

func-access: type params {
         }

//  func:
func-call: type func-call-tuple {
        tstr<narr> argsLife($2);
        str typeLife($1);
        $$ = yyget_extra(scanner)->onRunExpr(*typeLife, *argsLife);
      }

//  tuple:
tuple: '(' tuple-items ')' {
    $$ = $2;
  } | '(' ')' {
    $$ = yyget_extra(scanner)->onTuple();
  }
tuple-items: expr-line {
            $$ = yyget_extra(scanner)->onTuple($1);
        } | tuple-items ',' expr-line {
            $$ = yyget_extra(scanner)->onTuple(*$1, $3);
        }
func-call-tuple: '(' func-call-tuple-items ')' { $$=$2; }
               | '(' ')' { $$ = yyget_extra(scanner)->onTuple(); }
func-call-tuple-item: expr-line {
                  } | lambda {
                  }
func-call-tuple-items: func-call-tuple-item {
                   } | func-call-tuple-items ',' func-call-tuple-item {
                   }
params: '(' VOID ')' {
    } | '(' param-items ')' {
    }
param-item: defvar-without-initial-value { $$ = $1; }
param-items: param-item {
         } | param-items ',' param-item {
         }

//  type:
type: VOID { $$ = yyget_extra(scanner)->onPrimitive<nVoid>(); }
    | INT { $$ = yyget_extra(scanner)->onPrimitive<nInt>(); }
    | BYTE { $$ = yyget_extra(scanner)->onPrimitive<nByte>(); }
    | CHAR { $$ = yyget_extra(scanner)->onPrimitive<nChar>(); }
    | STR { $$ = yyget_extra(scanner)->onPrimitive<nStr>(); }
    | BOOL { $$ = yyget_extra(scanner)->onPrimitive<nBool>(); }
    | FLT { $$ = yyget_extra(scanner)->onPrimitive<nFlt>(); }
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

typeparams: '<' typenames '>' { $$ = $2; }
typenames: type {
            $$ = yyget_extra(scanner)->onTypeNames(*$1);
       } | typenames ',' type {
            $$ = yyget_extra(scanner)->onTypeNames(*$1, *$3);
       }

//  keyword:
//      branch:
if: if-block {
    $$ = yyget_extra(scanner)->onEndOfIf();
} | if-block _ELSE_ indentblock {
    $$ = yyget_extra(scanner)->onElse($1->cast<ifExpr>(), $3->cast<blockExpr>());
} | if-block _ELSE_ if-block {
    $$ = $1; // TODO
}
if-block: IF expr-line indentblock {
    $$ = yyget_extra(scanner)->onIf(*$2, $3->cast<blockExpr>());
   }

ret: RET NEWLINE {
    $$ = yyget_extra(scanner)->onRet();
 } | RET expr-line NEWLINE {
    $$ = yyget_extra(scanner)->onRet(*$2);
 } | RET expr-compound {
    $$ = yyget_extra(scanner)->onRet(*$2);
 }

next: NEXT NEWLINE {
    $$ = yyget_extra(scanner)->onNext();
   }

break: BREAK NEWLINE {
    $$ = yyget_extra(scanner)->onBreak();
   } | BREAK expr-line NEWLINE {
    $$ = yyget_extra(scanner)->onBreak(*$2);
   } | BREAK expr-compound {
    $$ = yyget_extra(scanner)->onBreak(*$2);
   }

//      loop:
while: _WHILE_ expr-line indentblock {
     $$ = yyget_extra(scanner)->onWhile(*$2, $3->cast<blockExpr>());
   }

for: FOR NAME _IN_ expr-line indentblock {
    $$ = yyget_extra(scanner)->onFor(std::string(*$2), *$4, $5->cast<blockExpr>());
    free($2);
 }

//      define:
//          value:
defvar: defvar-without-initial-value defvar-getset {
        // ??
    } | defvar-initial-value defvar-getset {
        $$ = $1;
    }
defvar-without-initial-value: NAME type { // exp means 'explicitly'
                             $$ = yyget_extra(scanner)->onDefVar(*$1, *$2);
                             free($1);
                          }
defvar-initial-value: NAME DEFASSIGN expr-line {
                      $$ = yyget_extra(scanner)->onDefAssign(*$1, *$3);
                      free($1);
                  }
defvar-getset-item: get { $$ = $1; }
                  | set { $$ = $1; }
defvar-getset: %empty { $$ = nullptr; }
             | defvar-getset defvar-getset-item {
                // ??
           }

defvar-compound: NAME DEFASSIGN expr-compound {
                $$ = yyget_extra(scanner)->onDefAssign(*$1, *$3);
                free($1);
             }

//          func:
deffunc: func-access type indentblock {
        // TODO: verify func-access has T<> or T[].
        // take bind of exprs instance: because it's on heap. I need to free.
        /*TODO: tstr<narr> params($2);
        str typeLife($3);
        $$ = yyget_extra(scanner)->onFunc(*$1, *params, *typeLife, $4->cast<blockExpr>());
        free($1);*/
     }

get: GET indentblock {
    // ??
 }

set: SET indentblock {
    // ??
 }

end: END indentblock {
    // ??
 }

lambda: lambda-default {
        // ??
    } | lambda-deduction {
        // ??
    }
lambda-default: tuple type indentblock {
                // checks tuple that it's NAME.
                // ??
            } | params type indentblock {
                // ??
            }
lambda-deduction: tuple indentblock {
                // ??
                // checks tuple that it's NAME.
              } | params indentblock {
                // ??
              }

//          obj:
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

//              container:
defarray-initial-value: '{' tuple-items '}' {
                        $$ = yyget_extra(scanner)->onDefArray(*$2);
                    }

//              with:
with-inline: WITH expr-line {
            // ??
         }

with-compound: with-inline indentblock {
                // ??
           }

//  predefined-type:
pack: PACK path NEWLINE { $$ = yyget_extra(scanner)->onPack(*$2); }
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
    yysymbol_kind_t symbol = yypcontext_token(ctx);

    if(symbol != YYSYMBOL_YYUNDEF) {
        yyget_extra(scanner)->onSrcArea(*yypcontext_location(ctx));
        yyget_extra(scanner)->onParseErr(traceErr(ctx, scanner), yysymbol_name(symbol));
    }

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
