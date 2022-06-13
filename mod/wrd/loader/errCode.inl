// common:
PAIRX(UNKNOWN,              "unknown")
PAIRX(MSG,                  "%s")
PAIRX(IS_NULL,              "%s is null")

// location:
PAIRX(NO_ROW_INFO,          "this expr doesn't have row info")
PAIRX(NO_COL_INFO,          "this expr doesn't have col info")

// node:
PAIRX(EVAL_NULL_TYPE,       "this expr evaluated as nulled type")
PAIRX(CANT_ACCESS,          "%s tried to access '%s' but nothing exist")
PAIRX(NOT_EXIST,            "%s not exist")
PAIRX(DUP_VAR,              "duplicated variable '%s' found")

// obj:
PAIRX(CANT_CAST_TO_NODE,    "obj can't be cast into node class")
PAIRX(OBJ_WRONG_ARGS,       "obj can't execute with this argument types")
PAIRX(OBJ_ALREADY_EXIST,    "\'%s\' object already exists at %s")

// parser:
PAIRX(SYNTAX_ERR,           "syntax error %s expected, but %s found")
PAIRX(UNEXPECTED_TOK,       "unexpected token '%s' found")
PAIRX(WRONG_INDENT_LV,      "invalid indentation level found. expected %d columns but it was %d. I'm assuming you were trying to give %d columns")
PAIRX(PARSING_HAS_ERR,      "parsing has done. but something went wrong: %d")
PAIRX(NO_SRC,               "source code not provided")

// pack:
PAIRX(NO_PACK_TRAY,         "pack tray hasn't been created before")
PAIRX(NO_PACK,              "no pack has been specified")
PAIRX(PACK_NOT_MATCH,       "pack %s expected, but it was %s")

// expr:
PAIRX(NOT_EXPR,             "\'%s\' isn't a expression")
PAIRX(EXPR_EVAL_NULL,       "expression evaluated as null type")
//  defVar:
PAIRX(CANT_DEF_VAR,         "definining variable '%s %s' wouldn't allowed here")
PAIRX(ALREADY_DEFINED_VAR,  "variable '%s %s' was already defined in this scope")
//  assign:
PAIRX(TYPE_NOT_COMPATIBLE,  "rhs type '%s' is not compatible to lhs '%s' of this assigment")
PAIRX(ASSIGN_TO_RVALUE,     "you can't assign %s to this unamed %s. please define it first")
//  casting:
PAIRX(CAST_NOT_AVAILABLE,   "couldn't cast %s type to %s")

// func:
PAIRX(PARAM_HAS_VAL,        "parameter shouldn't have a value")
PAIRX(FUNC_HAS_NO_NAME,     "a function should have a name")
PAIRX(WRONG_RET_TYPE,       "%s is not a valid return type")
PAIRX(NO_RET_TYPE,          "return type is not specified")
PAIRX(NO_FUNC_INFO,         "function info doesn't exist")
PAIRX(NO_STMT_IN_FUNC,      "function need to contain more than 1 statement inside")
PAIRX(RET_TYPE_NOT_MATCH,   "%s return type isn't valid to %s return type of func")

// block:
PAIRX(BLK_CANT_MAKE_FRAME,  "block statement failed to construct frame structure")
