/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_WRDCBISON_H_INCLUDED
# define YY_YY_WRDCBISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tfor = 258,
    tdef = 259,
    twith = 260,
    tret = 261,
    tretfun = 262,
    tretif = 263,
    tretwith = 264,
    tretfor = 265,
    tif = 266,
    telse = 267,
    telif = 268,
    tfrom = 269,
    tagain = 270,
    tprop = 271,
    timport = 272,
    taka = 273,
    tthis = 274,
    tme = 275,
    tgot = 276,
    tnode = 277,
    tnull = 278,
    tsuper = 279,
    tout = 280,
    tin = 281,
    tindent = 282,
    tdedent = 283,
    tinteger = 284,
    teof = 285,
    tfloat = 286,
    tbool = 287,
    tchar = 288,
    tstr = 289,
    tidentifier = 290,
    tfuncname = 291,
    teol = 292,
    topDefAssign = 293,
    topMinusAssign = 294,
    topSquareAssign = 295,
    topDivideAssign = 296,
    topModAssign = 297,
    topPowAssign = 298,
    topLessEqual = 299,
    topMoreEqual = 300,
    topEqual = 301,
    topRefEqual = 302,
    topNotEqual = 303,
    topNotRefEqual = 304,
    topPlusAssign = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "wrdcBison.cpp" /* glr.c:197  */

    int typeId;
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;
    const char* strVal;
    Node* node;
    void* nodes;

#line 116 "wrdcBison.h" /* glr.c:197  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WRDCBISON_H_INCLUDED  */
