/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GENERATED_PARSER_HH_INCLUDED
# define YY_YY_GENERATED_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LEFTPAR = 258,                 /* LEFTPAR  */
    RIGHTPAR = 259,                /* RIGHTPAR  */
    PDDL_DEFINE = 260,             /* PDDL_DEFINE  */
    PDDL_DOMAIN = 261,             /* PDDL_DOMAIN  */
    PDDL_DOMAINREF = 262,          /* PDDL_DOMAINREF  */
    PDDL_PROBLEM = 263,            /* PDDL_PROBLEM  */
    PDDL_CONSTANTS = 264,          /* PDDL_CONSTANTS  */
    PDDL_NAME = 265,               /* PDDL_NAME  */
    PDDL_VAR = 266,                /* PDDL_VAR  */
    PYTHON_CODE = 267,             /* PYTHON_CODE  */
    PDDL_NUMBER = 268,             /* PDDL_NUMBER  */
    PDDL_DNUMBER = 269,            /* PDDL_DNUMBER  */
    PDDL_REQUIREMENTS = 270,       /* PDDL_REQUIREMENTS  */
    PDDL_TYPES = 271,              /* PDDL_TYPES  */
    PDDL_HYPHEN = 272,             /* PDDL_HYPHEN  */
    PDDL_EITHER = 273,             /* PDDL_EITHER  */
    PDDL_STRIPS = 274,             /* PDDL_STRIPS  */
    PDDL_TYPING = 275,             /* PDDL_TYPING  */
    PDDL_NEGATIVE_PRECONDITIONS = 276, /* PDDL_NEGATIVE_PRECONDITIONS  */
    PDDL_DISJUNCTIVE_PRECONDITIONS = 277, /* PDDL_DISJUNCTIVE_PRECONDITIONS  */
    PDDL_EQUALITY = 278,           /* PDDL_EQUALITY  */
    PDDL_EXISTENTIAL_PRECONDITIONS = 279, /* PDDL_EXISTENTIAL_PRECONDITIONS  */
    PDDL_UNIVERSAL_PRECONDITIONS = 280, /* PDDL_UNIVERSAL_PRECONDITIONS  */
    PDDL_QUANTIFIED_PRECONDITIONS = 281, /* PDDL_QUANTIFIED_PRECONDITIONS  */
    PDDL_CONDITIONAL_EFFECTS = 282, /* PDDL_CONDITIONAL_EFFECTS  */
    PDDL_FLUENTS = 283,            /* PDDL_FLUENTS  */
    PDDL_ADL = 284,                /* PDDL_ADL  */
    PDDL_DURATIVE_ACTIONS = 285,   /* PDDL_DURATIVE_ACTIONS  */
    PDDL_DERIVED_PREDICATES = 286, /* PDDL_DERIVED_PREDICATES  */
    PDDL_TIMED_INITIAL_LITERALS = 287, /* PDDL_TIMED_INITIAL_LITERALS  */
    PDDL_PREDICATES = 288,         /* PDDL_PREDICATES  */
    PDDL_FUNCTIONS = 289,          /* PDDL_FUNCTIONS  */
    PDDL_ACTION = 290,             /* PDDL_ACTION  */
    PDDL_PARAMETERS = 291,         /* PDDL_PARAMETERS  */
    PDDL_NOT = 292,                /* PDDL_NOT  */
    PDDL_PRECONDITION = 293,       /* PDDL_PRECONDITION  */
    PDDL_IMPLY = 294,              /* PDDL_IMPLY  */
    PDDL_AND = 295,                /* PDDL_AND  */
    PDDL_OR = 296,                 /* PDDL_OR  */
    PDDL_EXISTS = 297,             /* PDDL_EXISTS  */
    PDDL_FORALL = 298,             /* PDDL_FORALL  */
    PLUS = 299,                    /* PLUS  */
    DIVIDE = 300,                  /* DIVIDE  */
    MULTIPLY = 301,                /* MULTIPLY  */
    POW = 302,                     /* POW  */
    ABS = 303,                     /* ABS  */
    SQRT = 304,                    /* SQRT  */
    GREATHER = 305,                /* GREATHER  */
    LESS = 306,                    /* LESS  */
    EQUAL = 307,                   /* EQUAL  */
    DISTINCT = 308,                /* DISTINCT  */
    GREATHER_EQUAL = 309,          /* GREATHER_EQUAL  */
    LESS_EQUAL = 310,              /* LESS_EQUAL  */
    PDDL_EFFECT = 311,             /* PDDL_EFFECT  */
    PDDL_ASSIGN = 312,             /* PDDL_ASSIGN  */
    PDDL_SCALE_UP = 313,           /* PDDL_SCALE_UP  */
    PDDL_SCALE_DOWN = 314,         /* PDDL_SCALE_DOWN  */
    PDDL_INCREASE = 315,           /* PDDL_INCREASE  */
    PDDL_DECREASE = 316,           /* PDDL_DECREASE  */
    PDDL_WHEN = 317,               /* PDDL_WHEN  */
    PDDL_GOAL = 318,               /* PDDL_GOAL  */
    PDDL_AT = 319,                 /* PDDL_AT  */
    PDDL_ATSTART = 320,            /* PDDL_ATSTART  */
    PDDL_ATEND = 321,              /* PDDL_ATEND  */
    PDDL_BETWEEN = 322,            /* PDDL_BETWEEN  */
    PDDL_OBJECT = 323,             /* PDDL_OBJECT  */
    PDDL_INIT = 324,               /* PDDL_INIT  */
    PDDL_OVERALL = 325,            /* PDDL_OVERALL  */
    PDDL_DURATIONVAR = 326,        /* PDDL_DURATIONVAR  */
    STARTVAR = 327,                /* STARTVAR  */
    ENDVAR = 328,                  /* ENDVAR  */
    PDDL_DERIVED = 329,            /* PDDL_DERIVED  */
    PDDL_CONDITION = 330,          /* PDDL_CONDITION  */
    PDDL_DURATION = 331,           /* PDDL_DURATION  */
    PDDL_DURATIVE_ACTION = 332,    /* PDDL_DURATIVE_ACTION  */
    HTN_EXPANSION = 333,           /* HTN_EXPANSION  */
    META_TAGS = 334,               /* META_TAGS  */
    META = 335,                    /* META  */
    TAG = 336,                     /* TAG  */
    HTN_TASK = 337,                /* HTN_TASK  */
    HTN_TASKS = 338,               /* HTN_TASKS  */
    HTN_ACHIEVE = 339,             /* HTN_ACHIEVE  */
    HTN_METHOD = 340,              /* HTN_METHOD  */
    HTN_TASKSGOAL = 341,           /* HTN_TASKSGOAL  */
    HTN_INLINE = 342,              /* HTN_INLINE  */
    HTN_INLINECUT = 343,           /* HTN_INLINECUT  */
    HTN_TEXT = 344,                /* HTN_TEXT  */
    LEFTBRAC = 345,                /* LEFTBRAC  */
    RIGHTBRAC = 346,               /* RIGHTBRAC  */
    EXCLAMATION = 347,             /* EXCLAMATION  */
    RANDOM = 348,                  /* RANDOM  */
    SORTBY = 349,                  /* SORTBY  */
    ASC = 350,                     /* ASC  */
    DESC = 351,                    /* DESC  */
    PDDL_BIND = 352,               /* PDDL_BIND  */
    MAINTAIN = 353,                /* MAINTAIN  */
    PPRINT = 354,                  /* PPRINT  */
    PDDL_AND_EVERY = 355,          /* PDDL_AND_EVERY  */
    CUSTOMIZATION = 356,           /* CUSTOMIZATION  */
    TIMEUNIT = 357,                /* TIMEUNIT  */
    TIMESTART = 358,               /* TIMESTART  */
    TIMEFORMAT = 359,              /* TIMEFORMAT  */
    TIMEHORIZON = 360,             /* TIMEHORIZON  */
    RELTIMEHORIZON = 361,          /* RELTIMEHORIZON  */
    THOURS = 362,                  /* THOURS  */
    TMINUTES = 363,                /* TMINUTES  */
    TSECONDS = 364,                /* TSECONDS  */
    TDAYS = 365,                   /* TDAYS  */
    TMONTHS = 366,                 /* TMONTHS  */
    TYEARS = 367,                  /* TYEARS  */
    PYTHON_INIT = 368,             /* PYTHON_INIT  */
    DBG_DEBUG = 369,               /* DBG_DEBUG  */
    DBG_QUIT = 370,                /* DBG_QUIT  */
    DBG_BREAKPOINT = 371,          /* DBG_BREAKPOINT  */
    DBG_WATCH = 372,               /* DBG_WATCH  */
    DBG_CONTINUE = 373,            /* DBG_CONTINUE  */
    DBG_HELP = 374,                /* DBG_HELP  */
    DBG_PATH = 375,                /* DBG_PATH  */
    DBG_PRINT = 376,               /* DBG_PRINT  */
    DBG_DISPLAY = 377,             /* DBG_DISPLAY  */
    DBG_DESCRIBE = 378,            /* DBG_DESCRIBE  */
    DBG_UNDISPLAY = 379,           /* DBG_UNDISPLAY  */
    DBG_STATE = 380,               /* DBG_STATE  */
    DBG_AGENDA = 381,              /* DBG_AGENDA  */
    DBG_PLAN = 382,                /* DBG_PLAN  */
    DBG_NEXT = 383,                /* DBG_NEXT  */
    DBG_NEXP = 384,                /* DBG_NEXP  */
    DBG_SET = 385,                 /* DBG_SET  */
    DBG_VIEWER = 386,              /* DBG_VIEWER  */
    DBG_DOTPATH = 387,             /* DBG_DOTPATH  */
    DBG_TMPDIR = 388,              /* DBG_TMPDIR  */
    DBG_PLOT = 389,                /* DBG_PLOT  */
    DBG_CAUSAL = 390,              /* DBG_CAUSAL  */
    DBG_MEM = 391,                 /* DBG_MEM  */
    DBG_SELECT = 392,              /* DBG_SELECT  */
    DBG_VERBOSE = 393,             /* DBG_VERBOSE  */
    DBG_ON = 394,                  /* DBG_ON  */
    DBG_OFF = 395,                 /* DBG_OFF  */
    DBG_OPTIONS = 396,             /* DBG_OPTIONS  */
    DBG_TERMTABLE = 397,           /* DBG_TERMTABLE  */
    DBG_PREDICATES = 398,          /* DBG_PREDICATES  */
    DBG_TASKS = 399,               /* DBG_TASKS  */
    DBG_ENABLE = 400,              /* DBG_ENABLE  */
    DBG_DISABLE = 401,             /* DBG_DISABLE  */
    DBG_EVAL = 402,                /* DBG_EVAL  */
    DBG_VERBOSITY = 403,           /* DBG_VERBOSITY  */
    DBG_APPLY = 404                /* DBG_APPLY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 203 "yacc/parser.yy"

        void * otype;
        const void * cotype;
        const char * type_string;
        double type_number;
        pair<int,float> * termtype;
        int type_int;

#line 222 "generated/parser.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GENERATED_PARSER_HH_INCLUDED  */
