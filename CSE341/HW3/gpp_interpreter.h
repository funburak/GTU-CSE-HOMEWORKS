/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_GPP_INTERPRETER_H_INCLUDED
# define YY_YY_GPP_INTERPRETER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    VALUEF = 259,
    KW_AND = 260,
    KW_OR = 261,
    KW_NOT = 262,
    KW_EQUAL = 263,
    KW_LESS = 264,
    KW_NIL = 265,
    KW_LIST = 266,
    KW_APPEND = 267,
    KW_CONCAT = 268,
    KW_SET = 269,
    KW_DEF = 270,
    KW_FOR = 271,
    KW_IF = 272,
    KW_EXIT = 273,
    KW_LOAD = 274,
    KW_DISPLAY = 275,
    KW_TRUE = 276,
    KW_FALSE = 277,
    OP_PLUS = 278,
    OP_MINUS = 279,
    OP_DIV = 280,
    OP_MULT = 281,
    OP_OP = 282,
    OP_CP = 283,
    OP_COMMA = 284,
    COMMENT = 285
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define VALUEF 259
#define KW_AND 260
#define KW_OR 261
#define KW_NOT 262
#define KW_EQUAL 263
#define KW_LESS 264
#define KW_NIL 265
#define KW_LIST 266
#define KW_APPEND 267
#define KW_CONCAT 268
#define KW_SET 269
#define KW_DEF 270
#define KW_FOR 271
#define KW_IF 272
#define KW_EXIT 273
#define KW_LOAD 274
#define KW_DISPLAY 275
#define KW_TRUE 276
#define KW_FALSE 277
#define OP_PLUS 278
#define OP_MINUS 279
#define OP_DIV 280
#define OP_MULT 281
#define OP_OP 282
#define OP_CP 283
#define OP_COMMA 284
#define COMMENT 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "gpp_interpreter.y"

    char *string; // For identifiers
    char *valuef;

#line 122 "gpp_interpreter.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GPP_INTERPRETER_H_INCLUDED  */
