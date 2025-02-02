/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     DO = 262,
     BREAK = 263,
     INT = 264,
     CHAR = 265,
     FLOAT = 266,
     DOUBLE = 267,
     VOID = 268,
     RETURN = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     CONTINUE = 273,
     ADDOP = 274,
     MULOP = 275,
     RELOP = 276,
     LOGICOP = 277,
     INCOP = 278,
     DECOP = 279,
     ASSIGNOP = 280,
     NOT = 281,
     LPAREN = 282,
     RPAREN = 283,
     LCURL = 284,
     RCURL = 285,
     LSQUARE = 286,
     RSQUARE = 287,
     COMMA = 288,
     SEMICOLON = 289,
     CONST_INT = 290,
     CONST_FLOAT = 291,
     CONST_CHAR = 292,
     LOWER_THAN_ELSE = 293,
     ID = 294
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define ADDOP 274
#define MULOP 275
#define RELOP 276
#define LOGICOP 277
#define INCOP 278
#define DECOP 279
#define ASSIGNOP 280
#define NOT 281
#define LPAREN 282
#define RPAREN 283
#define LCURL 284
#define RCURL 285
#define LSQUARE 286
#define RSQUARE 287
#define COMMA 288
#define SEMICOLON 289
#define CONST_INT 290
#define CONST_FLOAT 291
#define CONST_CHAR 292
#define LOWER_THAN_ELSE 293
#define ID 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 286 "Parser.y"
{
  symbolInfo* symbol;
}
/* Line 1529 of yacc.c.  */
#line 131 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

