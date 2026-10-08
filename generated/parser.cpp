/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc/parser.yy"

    using namespace std;

    #include "hpdl/common/constants.hh"
    #include <string>
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <vector>
    #include <math.h>
    #include <malloc.h>
    #include <ctype.h>
    #include "hpdl/parser/MyLexer.hh"
    #include "hpdl/domain/domain.hh"
    #include "hpdl/domain/problem.hh"
    #include "hpdl/common/type.hh"
    #include "hpdl/lang/goals/andGoal.hh"
    #include "hpdl/parser/papi.hh"
    #include "hpdl/lang/function.hh"
    #include "hpdl/py/pyDefFunction.hh"
    #include "hpdl/lang/goals/comparationGoal.hh"
    #include "hpdl/lang/fluentNumber.hh"
    #include "hpdl/lang/fluentOperator.hh"
    #include "hpdl/lang/fluentVar.hh"
    #include "hpdl/lang/goals/forallgoal.hh"
    #include "hpdl/lang/goals/existsgoal.hh"
    #include "hpdl/lang/effects/foralleffect.hh"
    #include "hpdl/lang/goals/cutgoal.hh"
    #include "hpdl/lang/goals/sortgoal.hh"
    #include "hpdl/undo/undoARLiteralState.hh"
    #include "hpdl/lang/effects/fluentEffect.hh"
    #include "hpdl/lang/effects/wheneffect.hh"
    #include "hpdl/lang/fluentLiteral.hh"
    #include "hpdl/lang/goals/literalgoal.hh"
    #include "hpdl/lang/goals/orGoal.hh"
    #include "hpdl/lang/goals/boundGoal.hh"
    #include "hpdl/lang/goals/implyGoal.hh"
    #include "hpdl/lang/fluentConstant.hh"
    #include "hpdl/constraints/timeInterval.hh"
    #include "hpdl/lang/goals/printGoal.hh"
    #include "hpdl/debug/debugger.hh"
    #include "hpdl/lang/effects/timeLineLitEffect.hh"
    #include "hpdl/planner/plan.hh"
    #include "hpdl/parser/textTag.hh"

    #define yytrue true
    #define yyfalse false
    #define DEBUG 0
    #define YYDEBUG 1
    #define YYMAXDEPTH INT_MAX

#ifdef PYTHON_FOUND
    #define PYTHON_FLAG 1
#else
    #define PYTHON_FLAG 0
#endif

// variables globales
// estas variables sirven para ir almacenando los valores
// que vamos capturando
ParameterContainer * container=0;
LDictionary * context=0;
LDictionary * oldContext=0;
vector<ContainerGoal *> gcontainer;
vector<ContainerEffect *> econtainer;
CompoundTask * cbuilding=0;
// Espera encontrar un n�mero
bool isNumber = false;
// Espera encontrar un at
bool AtExpected=false;
// determina si la acci�n que estamos parseando es o no durativa
bool isDurative = false;

// variable para construir los mensajes de error
char parerr[256];
// imprimir o no errores de tipos
bool errtypes=true;

int contador=0;

// Usar este objeto como interfaz con el debugger
extern Debugger * debugger;
// esperar o no tokens del debugger
bool inDebugContext= false;

// flags del parser
// evitar o no la mayor�a de los chequeos
bool fast_parsing = false;

inline int yylex(void)
{
    return lexer->yylex();
};

inline void yyerror(const char *s)
{
    lexer->LexerError(s);
};

inline void yywarning(const char *s)
{
    lexer->LexerWarning(s);
};

struct SearchLineInfo
{
    string fileName;
    int lineNumber;

    SearchLineInfo(const Type * t)
    {
        if(t->getFileId() != -1) {
        fileName = parser_api->files[t->getFileId()];
        lineNumber = t->getLineNumber();
        }
        else{
        fileName = "";
        lineNumber = 0;
        }
    }

    SearchLineInfo(const ConstantSymbol * c)
    {
        fileName = parser_api->files[c->getFileId()];
        lineNumber = c->getLineNumber();
    }

    SearchLineInfo(int mid) {
        Meta * m = parser_api->domain->metainfo[mid];
        fileName = parser_api->files[m->fileid];
        lineNumber = m->linenumber;
    }
};

// este operador verifica que no se dan definiciones
// de tipos redundantes
struct TestTypeTree {
    void operator()(Type * t) const {
        vector<Type *>::const_iterator i,e,j;
        e = t->getParentsEnd();
        if(t->getNumberOfParents() > 0)
        for(i = t->getParentsBegin(); i != e; i++){
                if((*i)->isSubTypeOf(t)){
                SearchLineInfo sli((*i));
                snprintf(parerr,256,"Ambiguous declaration type `%s' is subtype of `%s' near %d [%s].",(*i)->getName(),t->getName(),sli.lineNumber,sli.fileName.c_str());
                yyerror(parerr);
                }
                else{
                for(j = t->getParentsBegin(); j != e; j++)
                        if(i != j && (*i)->isSubTypeOf((*j))){
                        SearchLineInfo sli((*j));
                        snprintf(parerr,256,"Ambiguous declaration type `%s' is subtype of `%s' near %d [%s].",(*i)->getName(),(*j)->getName(),sli.lineNumber,sli.fileName.c_str());
                        yywarning(parerr);
                        }
                }
        }
    };

   void operator()(vector<Type *> * vt) const {
        vector<Type *>::const_iterator i,e,j;
        e = vt->end();
        for(i = vt->begin(); i != e; i++){
        for(j = vt->begin(); j != e; j++)
        if(i != j && (*i)->isSubTypeOf((*j))){
                SearchLineInfo sli((*j));
                snprintf(parerr,256,"Ambiguous declaration type `%s' is subtype of `%s' near %d [%s].",(*i)->getName(),(*j)->getName(),sli.lineNumber,sli.fileName.c_str());
                yywarning(parerr);
        }
        }
   };
};


// este operador verifica que un tipo est� correctamente
// definido
struct TestType {
   void operator()(Type * t) const {
       // Se trata del tipo number
       if(t->getId() == 0)
        return;

       SearchLineInfo sli(t);
       if(!sli.lineNumber) {
        snprintf(parerr,256,"Trying to use an undefined type `%s'.",t->getName());
        yyerror(parerr);
       }
       else{
        TestTypeTree()(t);
       }
   };
};


#line 266 "generated/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LEFTPAR = 3,                    /* LEFTPAR  */
  YYSYMBOL_RIGHTPAR = 4,                   /* RIGHTPAR  */
  YYSYMBOL_PDDL_DEFINE = 5,                /* PDDL_DEFINE  */
  YYSYMBOL_PDDL_DOMAIN = 6,                /* PDDL_DOMAIN  */
  YYSYMBOL_PDDL_DOMAINREF = 7,             /* PDDL_DOMAINREF  */
  YYSYMBOL_PDDL_PROBLEM = 8,               /* PDDL_PROBLEM  */
  YYSYMBOL_PDDL_CONSTANTS = 9,             /* PDDL_CONSTANTS  */
  YYSYMBOL_PDDL_NAME = 10,                 /* PDDL_NAME  */
  YYSYMBOL_PDDL_VAR = 11,                  /* PDDL_VAR  */
  YYSYMBOL_PYTHON_CODE = 12,               /* PYTHON_CODE  */
  YYSYMBOL_PDDL_NUMBER = 13,               /* PDDL_NUMBER  */
  YYSYMBOL_PDDL_DNUMBER = 14,              /* PDDL_DNUMBER  */
  YYSYMBOL_PDDL_REQUIREMENTS = 15,         /* PDDL_REQUIREMENTS  */
  YYSYMBOL_PDDL_TYPES = 16,                /* PDDL_TYPES  */
  YYSYMBOL_PDDL_HYPHEN = 17,               /* PDDL_HYPHEN  */
  YYSYMBOL_PDDL_EITHER = 18,               /* PDDL_EITHER  */
  YYSYMBOL_PDDL_STRIPS = 19,               /* PDDL_STRIPS  */
  YYSYMBOL_PDDL_TYPING = 20,               /* PDDL_TYPING  */
  YYSYMBOL_PDDL_NEGATIVE_PRECONDITIONS = 21, /* PDDL_NEGATIVE_PRECONDITIONS  */
  YYSYMBOL_PDDL_DISJUNCTIVE_PRECONDITIONS = 22, /* PDDL_DISJUNCTIVE_PRECONDITIONS  */
  YYSYMBOL_PDDL_EQUALITY = 23,             /* PDDL_EQUALITY  */
  YYSYMBOL_PDDL_EXISTENTIAL_PRECONDITIONS = 24, /* PDDL_EXISTENTIAL_PRECONDITIONS  */
  YYSYMBOL_PDDL_UNIVERSAL_PRECONDITIONS = 25, /* PDDL_UNIVERSAL_PRECONDITIONS  */
  YYSYMBOL_PDDL_QUANTIFIED_PRECONDITIONS = 26, /* PDDL_QUANTIFIED_PRECONDITIONS  */
  YYSYMBOL_PDDL_CONDITIONAL_EFFECTS = 27,  /* PDDL_CONDITIONAL_EFFECTS  */
  YYSYMBOL_PDDL_FLUENTS = 28,              /* PDDL_FLUENTS  */
  YYSYMBOL_PDDL_ADL = 29,                  /* PDDL_ADL  */
  YYSYMBOL_PDDL_DURATIVE_ACTIONS = 30,     /* PDDL_DURATIVE_ACTIONS  */
  YYSYMBOL_PDDL_DERIVED_PREDICATES = 31,   /* PDDL_DERIVED_PREDICATES  */
  YYSYMBOL_PDDL_TIMED_INITIAL_LITERALS = 32, /* PDDL_TIMED_INITIAL_LITERALS  */
  YYSYMBOL_PDDL_PREDICATES = 33,           /* PDDL_PREDICATES  */
  YYSYMBOL_PDDL_FUNCTIONS = 34,            /* PDDL_FUNCTIONS  */
  YYSYMBOL_PDDL_ACTION = 35,               /* PDDL_ACTION  */
  YYSYMBOL_PDDL_PARAMETERS = 36,           /* PDDL_PARAMETERS  */
  YYSYMBOL_PDDL_NOT = 37,                  /* PDDL_NOT  */
  YYSYMBOL_PDDL_PRECONDITION = 38,         /* PDDL_PRECONDITION  */
  YYSYMBOL_PDDL_IMPLY = 39,                /* PDDL_IMPLY  */
  YYSYMBOL_PDDL_AND = 40,                  /* PDDL_AND  */
  YYSYMBOL_PDDL_OR = 41,                   /* PDDL_OR  */
  YYSYMBOL_PDDL_EXISTS = 42,               /* PDDL_EXISTS  */
  YYSYMBOL_PDDL_FORALL = 43,               /* PDDL_FORALL  */
  YYSYMBOL_PLUS = 44,                      /* PLUS  */
  YYSYMBOL_DIVIDE = 45,                    /* DIVIDE  */
  YYSYMBOL_MULTIPLY = 46,                  /* MULTIPLY  */
  YYSYMBOL_POW = 47,                       /* POW  */
  YYSYMBOL_ABS = 48,                       /* ABS  */
  YYSYMBOL_SQRT = 49,                      /* SQRT  */
  YYSYMBOL_GREATHER = 50,                  /* GREATHER  */
  YYSYMBOL_LESS = 51,                      /* LESS  */
  YYSYMBOL_EQUAL = 52,                     /* EQUAL  */
  YYSYMBOL_DISTINCT = 53,                  /* DISTINCT  */
  YYSYMBOL_GREATHER_EQUAL = 54,            /* GREATHER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 55,                /* LESS_EQUAL  */
  YYSYMBOL_PDDL_EFFECT = 56,               /* PDDL_EFFECT  */
  YYSYMBOL_PDDL_ASSIGN = 57,               /* PDDL_ASSIGN  */
  YYSYMBOL_PDDL_SCALE_UP = 58,             /* PDDL_SCALE_UP  */
  YYSYMBOL_PDDL_SCALE_DOWN = 59,           /* PDDL_SCALE_DOWN  */
  YYSYMBOL_PDDL_INCREASE = 60,             /* PDDL_INCREASE  */
  YYSYMBOL_PDDL_DECREASE = 61,             /* PDDL_DECREASE  */
  YYSYMBOL_PDDL_WHEN = 62,                 /* PDDL_WHEN  */
  YYSYMBOL_PDDL_GOAL = 63,                 /* PDDL_GOAL  */
  YYSYMBOL_PDDL_AT = 64,                   /* PDDL_AT  */
  YYSYMBOL_PDDL_ATSTART = 65,              /* PDDL_ATSTART  */
  YYSYMBOL_PDDL_ATEND = 66,                /* PDDL_ATEND  */
  YYSYMBOL_PDDL_BETWEEN = 67,              /* PDDL_BETWEEN  */
  YYSYMBOL_PDDL_OBJECT = 68,               /* PDDL_OBJECT  */
  YYSYMBOL_PDDL_INIT = 69,                 /* PDDL_INIT  */
  YYSYMBOL_PDDL_OVERALL = 70,              /* PDDL_OVERALL  */
  YYSYMBOL_PDDL_DURATIONVAR = 71,          /* PDDL_DURATIONVAR  */
  YYSYMBOL_STARTVAR = 72,                  /* STARTVAR  */
  YYSYMBOL_ENDVAR = 73,                    /* ENDVAR  */
  YYSYMBOL_PDDL_DERIVED = 74,              /* PDDL_DERIVED  */
  YYSYMBOL_PDDL_CONDITION = 75,            /* PDDL_CONDITION  */
  YYSYMBOL_PDDL_DURATION = 76,             /* PDDL_DURATION  */
  YYSYMBOL_PDDL_DURATIVE_ACTION = 77,      /* PDDL_DURATIVE_ACTION  */
  YYSYMBOL_HTN_EXPANSION = 78,             /* HTN_EXPANSION  */
  YYSYMBOL_META_TAGS = 79,                 /* META_TAGS  */
  YYSYMBOL_META = 80,                      /* META  */
  YYSYMBOL_TAG = 81,                       /* TAG  */
  YYSYMBOL_HTN_TASK = 82,                  /* HTN_TASK  */
  YYSYMBOL_HTN_TASKS = 83,                 /* HTN_TASKS  */
  YYSYMBOL_HTN_ACHIEVE = 84,               /* HTN_ACHIEVE  */
  YYSYMBOL_HTN_METHOD = 85,                /* HTN_METHOD  */
  YYSYMBOL_HTN_TASKSGOAL = 86,             /* HTN_TASKSGOAL  */
  YYSYMBOL_HTN_INLINE = 87,                /* HTN_INLINE  */
  YYSYMBOL_HTN_INLINECUT = 88,             /* HTN_INLINECUT  */
  YYSYMBOL_HTN_TEXT = 89,                  /* HTN_TEXT  */
  YYSYMBOL_LEFTBRAC = 90,                  /* LEFTBRAC  */
  YYSYMBOL_RIGHTBRAC = 91,                 /* RIGHTBRAC  */
  YYSYMBOL_EXCLAMATION = 92,               /* EXCLAMATION  */
  YYSYMBOL_RANDOM = 93,                    /* RANDOM  */
  YYSYMBOL_SORTBY = 94,                    /* SORTBY  */
  YYSYMBOL_ASC = 95,                       /* ASC  */
  YYSYMBOL_DESC = 96,                      /* DESC  */
  YYSYMBOL_PDDL_BIND = 97,                 /* PDDL_BIND  */
  YYSYMBOL_MAINTAIN = 98,                  /* MAINTAIN  */
  YYSYMBOL_PPRINT = 99,                    /* PPRINT  */
  YYSYMBOL_PDDL_AND_EVERY = 100,           /* PDDL_AND_EVERY  */
  YYSYMBOL_CUSTOMIZATION = 101,            /* CUSTOMIZATION  */
  YYSYMBOL_TIMEUNIT = 102,                 /* TIMEUNIT  */
  YYSYMBOL_TIMESTART = 103,                /* TIMESTART  */
  YYSYMBOL_TIMEFORMAT = 104,               /* TIMEFORMAT  */
  YYSYMBOL_TIMEHORIZON = 105,              /* TIMEHORIZON  */
  YYSYMBOL_RELTIMEHORIZON = 106,           /* RELTIMEHORIZON  */
  YYSYMBOL_THOURS = 107,                   /* THOURS  */
  YYSYMBOL_TMINUTES = 108,                 /* TMINUTES  */
  YYSYMBOL_TSECONDS = 109,                 /* TSECONDS  */
  YYSYMBOL_TDAYS = 110,                    /* TDAYS  */
  YYSYMBOL_TMONTHS = 111,                  /* TMONTHS  */
  YYSYMBOL_TYEARS = 112,                   /* TYEARS  */
  YYSYMBOL_PYTHON_INIT = 113,              /* PYTHON_INIT  */
  YYSYMBOL_DBG_DEBUG = 114,                /* DBG_DEBUG  */
  YYSYMBOL_DBG_QUIT = 115,                 /* DBG_QUIT  */
  YYSYMBOL_DBG_BREAKPOINT = 116,           /* DBG_BREAKPOINT  */
  YYSYMBOL_DBG_WATCH = 117,                /* DBG_WATCH  */
  YYSYMBOL_DBG_CONTINUE = 118,             /* DBG_CONTINUE  */
  YYSYMBOL_DBG_HELP = 119,                 /* DBG_HELP  */
  YYSYMBOL_DBG_PATH = 120,                 /* DBG_PATH  */
  YYSYMBOL_DBG_PRINT = 121,                /* DBG_PRINT  */
  YYSYMBOL_DBG_DISPLAY = 122,              /* DBG_DISPLAY  */
  YYSYMBOL_DBG_DESCRIBE = 123,             /* DBG_DESCRIBE  */
  YYSYMBOL_DBG_UNDISPLAY = 124,            /* DBG_UNDISPLAY  */
  YYSYMBOL_DBG_STATE = 125,                /* DBG_STATE  */
  YYSYMBOL_DBG_AGENDA = 126,               /* DBG_AGENDA  */
  YYSYMBOL_DBG_PLAN = 127,                 /* DBG_PLAN  */
  YYSYMBOL_DBG_NEXT = 128,                 /* DBG_NEXT  */
  YYSYMBOL_DBG_NEXP = 129,                 /* DBG_NEXP  */
  YYSYMBOL_DBG_SET = 130,                  /* DBG_SET  */
  YYSYMBOL_DBG_VIEWER = 131,               /* DBG_VIEWER  */
  YYSYMBOL_DBG_DOTPATH = 132,              /* DBG_DOTPATH  */
  YYSYMBOL_DBG_TMPDIR = 133,               /* DBG_TMPDIR  */
  YYSYMBOL_DBG_PLOT = 134,                 /* DBG_PLOT  */
  YYSYMBOL_DBG_CAUSAL = 135,               /* DBG_CAUSAL  */
  YYSYMBOL_DBG_MEM = 136,                  /* DBG_MEM  */
  YYSYMBOL_DBG_SELECT = 137,               /* DBG_SELECT  */
  YYSYMBOL_DBG_VERBOSE = 138,              /* DBG_VERBOSE  */
  YYSYMBOL_DBG_ON = 139,                   /* DBG_ON  */
  YYSYMBOL_DBG_OFF = 140,                  /* DBG_OFF  */
  YYSYMBOL_DBG_OPTIONS = 141,              /* DBG_OPTIONS  */
  YYSYMBOL_DBG_TERMTABLE = 142,            /* DBG_TERMTABLE  */
  YYSYMBOL_DBG_PREDICATES = 143,           /* DBG_PREDICATES  */
  YYSYMBOL_DBG_TASKS = 144,                /* DBG_TASKS  */
  YYSYMBOL_DBG_ENABLE = 145,               /* DBG_ENABLE  */
  YYSYMBOL_DBG_DISABLE = 146,              /* DBG_DISABLE  */
  YYSYMBOL_DBG_EVAL = 147,                 /* DBG_EVAL  */
  YYSYMBOL_DBG_VERBOSITY = 148,            /* DBG_VERBOSITY  */
  YYSYMBOL_DBG_APPLY = 149,                /* DBG_APPLY  */
  YYSYMBOL_YYACCEPT = 150,                 /* $accept  */
  YYSYMBOL_pddl_root = 151,                /* pddl_root  */
  YYSYMBOL_problem_definition = 152,       /* problem_definition  */
  YYSYMBOL_domain_definition = 153,        /* domain_definition  */
  YYSYMBOL_domain_definition_2 = 154,      /* domain_definition_2  */
  YYSYMBOL_domain_definition_31 = 155,     /* domain_definition_31  */
  YYSYMBOL_domain_definition_32 = 156,     /* domain_definition_32  */
  YYSYMBOL_domain_definition_3 = 157,      /* domain_definition_3  */
  YYSYMBOL_domain_definition_4 = 158,      /* domain_definition_4  */
  YYSYMBOL_domain_definition_5 = 159,      /* domain_definition_5  */
  YYSYMBOL_domain_definition_6 = 160,      /* domain_definition_6  */
  YYSYMBOL_domain_definition_7 = 161,      /* domain_definition_7  */
  YYSYMBOL_domainName = 162,               /* domainName  */
  YYSYMBOL_problemName = 163,              /* problemName  */
  YYSYMBOL_domainRef = 164,                /* domainRef  */
  YYSYMBOL_require_def = 165,              /* require_def  */
  YYSYMBOL_require_key_list = 166,         /* require_key_list  */
  YYSYMBOL_require_key = 167,              /* require_key  */
  YYSYMBOL_term_name = 168,                /* term_name  */
  YYSYMBOL_types_def = 169,                /* types_def  */
  YYSYMBOL_constants_def = 170,            /* constants_def  */
  YYSYMBOL_typed_list = 171,               /* typed_list  */
  YYSYMBOL_172_1 = 172,                    /* $@1  */
  YYSYMBOL_173_2 = 173,                    /* $@2  */
  YYSYMBOL_constant_list = 174,            /* constant_list  */
  YYSYMBOL_constant_def_list = 175,        /* constant_def_list  */
  YYSYMBOL_type = 176,                     /* type  */
  YYSYMBOL_type_def_list = 177,            /* type_def_list  */
  YYSYMBOL_type_ref = 178,                 /* type_ref  */
  YYSYMBOL_type_ref_list = 179,            /* type_ref_list  */
  YYSYMBOL_predicates_def = 180,           /* predicates_def  */
  YYSYMBOL_atomic_formula_skeleton_list = 181, /* atomic_formula_skeleton_list  */
  YYSYMBOL_atomic_formula_skeleton = 182,  /* atomic_formula_skeleton  */
  YYSYMBOL_183_3 = 183,                    /* $@3  */
  YYSYMBOL_derived_formula_skeleton = 184, /* derived_formula_skeleton  */
  YYSYMBOL_185_4 = 185,                    /* $@4  */
  YYSYMBOL_variable_typed_list = 186,      /* variable_typed_list  */
  YYSYMBOL_187_5 = 187,                    /* $@5  */
  YYSYMBOL_var_typel = 188,                /* var_typel  */
  YYSYMBOL_functions_def = 189,            /* functions_def  */
  YYSYMBOL_function_typed_list = 190,      /* function_typed_list  */
  YYSYMBOL_function_def = 191,             /* function_def  */
  YYSYMBOL_192_6 = 192,                    /* $@6  */
  YYSYMBOL_opt_type = 193,                 /* opt_type  */
  YYSYMBOL_code = 194,                     /* code  */
  YYSYMBOL_structure_def_list = 195,       /* structure_def_list  */
  YYSYMBOL_structure_def = 196,            /* structure_def  */
  YYSYMBOL_action_def = 197,               /* action_def  */
  YYSYMBOL_198_7 = 198,                    /* @7  */
  YYSYMBOL_199_8 = 199,                    /* $@8  */
  YYSYMBOL_htn_task_def = 200,             /* htn_task_def  */
  YYSYMBOL_201_9 = 201,                    /* $@9  */
  YYSYMBOL_duration_constraints = 202,     /* duration_constraints  */
  YYSYMBOL_sdur_constraint = 203,          /* sdur_constraint  */
  YYSYMBOL_simple_duration_constraint = 204, /* simple_duration_constraint  */
  YYSYMBOL_sduration_constraint_list = 205, /* sduration_constraint_list  */
  YYSYMBOL_methods_def_body = 206,         /* methods_def_body  */
  YYSYMBOL_method_list = 207,              /* method_list  */
  YYSYMBOL_method_body = 208,              /* method_body  */
  YYSYMBOL_209_10 = 209,                   /* $@10  */
  YYSYMBOL_210_11 = 210,                   /* $@11  */
  YYSYMBOL_211_12 = 211,                   /* @12  */
  YYSYMBOL_meta_list = 212,                /* meta_list  */
  YYSYMBOL_tag_list = 213,                 /* tag_list  */
  YYSYMBOL_tag_element = 214,              /* tag_element  */
  YYSYMBOL_215_13 = 215,                   /* @13  */
  YYSYMBOL_task_def = 216,                 /* task_def  */
  YYSYMBOL_inlinetask = 217,               /* inlinetask  */
  YYSYMBOL_218_14 = 218,                   /* @14  */
  YYSYMBOL_219_15 = 219,                   /* @15  */
  YYSYMBOL_atomic_task_formula = 220,      /* atomic_task_formula  */
  YYSYMBOL_221_16 = 221,                   /* $@16  */
  YYSYMBOL_task_network = 222,             /* task_network  */
  YYSYMBOL_task_list = 223,                /* task_list  */
  YYSYMBOL_task_element = 224,             /* task_element  */
  YYSYMBOL_preconditions_def = 225,        /* preconditions_def  */
  YYSYMBOL_goal_def = 226,                 /* goal_def  */
  YYSYMBOL_227_17 = 227,                   /* @17  */
  YYSYMBOL_228_18 = 228,                   /* $@18  */
  YYSYMBOL_229_19 = 229,                   /* @19  */
  YYSYMBOL_230_20 = 230,                   /* @20  */
  YYSYMBOL_simple_goal_def = 231,          /* simple_goal_def  */
  YYSYMBOL_232_21 = 232,                   /* @21  */
  YYSYMBOL_233_22 = 233,                   /* $@22  */
  YYSYMBOL_234_23 = 234,                   /* @23  */
  YYSYMBOL_235_24 = 235,                   /* $@24  */
  YYSYMBOL_236_25 = 236,                   /* @25  */
  YYSYMBOL_237_26 = 237,                   /* $@26  */
  YYSYMBOL_238_27 = 238,                   /* @27  */
  YYSYMBOL_239_28 = 239,                   /* $@28  */
  YYSYMBOL_timed_goal = 240,               /* timed_goal  */
  YYSYMBOL_order = 241,                    /* order  */
  YYSYMBOL_v_list = 242,                   /* v_list  */
  YYSYMBOL_v_crit = 243,                   /* v_crit  */
  YYSYMBOL_goal_def_list = 244,            /* goal_def_list  */
  YYSYMBOL_atomic_formula_term_effect = 245, /* atomic_formula_term_effect  */
  YYSYMBOL_literal_effect = 246,           /* literal_effect  */
  YYSYMBOL_247_29 = 247,                   /* $@29  */
  YYSYMBOL_atomic_formula_term_goal = 248, /* atomic_formula_term_goal  */
  YYSYMBOL_249_30 = 249,                   /* $@30  */
  YYSYMBOL_term_list = 250,                /* term_list  */
  YYSYMBOL_term = 251,                     /* term  */
  YYSYMBOL_number = 252,                   /* number  */
  YYSYMBOL_var = 253,                      /* var  */
  YYSYMBOL_variable = 254,                 /* variable  */
  YYSYMBOL_f_comp = 255,                   /* f_comp  */
  YYSYMBOL_binary_comp = 256,              /* binary_comp  */
  YYSYMBOL_fluent_exp = 257,               /* fluent_exp  */
  YYSYMBOL_silly_exp = 258,                /* silly_exp  */
  YYSYMBOL_unary_op = 259,                 /* unary_op  */
  YYSYMBOL_binary_op = 260,                /* binary_op  */
  YYSYMBOL_f_head = 261,                   /* f_head  */
  YYSYMBOL_262_31 = 262,                   /* $@31  */
  YYSYMBOL_f_head_ref = 263,               /* f_head_ref  */
  YYSYMBOL_264_32 = 264,                   /* $@32  */
  YYSYMBOL_effect_def = 265,               /* effect_def  */
  YYSYMBOL_effect = 266,                   /* effect  */
  YYSYMBOL_267_33 = 267,                   /* $@33  */
  YYSYMBOL_timed_effect = 268,             /* timed_effect  */
  YYSYMBOL_c_effect = 269,                 /* c_effect  */
  YYSYMBOL_270_34 = 270,                   /* @34  */
  YYSYMBOL_271_35 = 271,                   /* $@35  */
  YYSYMBOL_c_effect_list = 272,            /* c_effect_list  */
  YYSYMBOL_p_effect = 273,                 /* p_effect  */
  YYSYMBOL_p_effect_list = 274,            /* p_effect_list  */
  YYSYMBOL_cond_effect = 275,              /* cond_effect  */
  YYSYMBOL_276_36 = 276,                   /* $@36  */
  YYSYMBOL_assign_op = 277,                /* assign_op  */
  YYSYMBOL_problemBody = 278,              /* problemBody  */
  YYSYMBOL_problemBody21 = 279,            /* problemBody21  */
  YYSYMBOL_problemBody22 = 280,            /* problemBody22  */
  YYSYMBOL_problemBody2 = 281,             /* problemBody2  */
  YYSYMBOL_problemBody3 = 282,             /* problemBody3  */
  YYSYMBOL_283_37 = 283,                   /* $@37  */
  YYSYMBOL_object_declaration = 284,       /* object_declaration  */
  YYSYMBOL_init = 285,                     /* init  */
  YYSYMBOL_init_el = 286,                  /* init_el  */
  YYSYMBOL_287_38 = 287,                   /* $@38  */
  YYSYMBOL_optional_repetition = 288,      /* optional_repetition  */
  YYSYMBOL_init_el_list = 289,             /* init_el_list  */
  YYSYMBOL_goal = 290,                     /* goal  */
  YYSYMBOL_literal_name = 291,             /* literal_name  */
  YYSYMBOL_atomic_formula_name = 292,      /* atomic_formula_name  */
  YYSYMBOL_293_39 = 293,                   /* $@39  */
  YYSYMBOL_durative_action_def = 294,      /* durative_action_def  */
  YYSYMBOL_295_40 = 295,                   /* @40  */
  YYSYMBOL_296_41 = 296,                   /* $@41  */
  YYSYMBOL_297_42 = 297,                   /* $@42  */
  YYSYMBOL_sdur_constraint_list = 298,     /* sdur_constraint_list  */
  YYSYMBOL_pduration_constraints = 299,    /* pduration_constraints  */
  YYSYMBOL_time_specifier = 300,           /* time_specifier  */
  YYSYMBOL_time_point = 301,               /* time_point  */
  YYSYMBOL_number_time_point = 302,        /* number_time_point  */
  YYSYMBOL_303_43 = 303,                   /* $@43  */
  YYSYMBOL_304_44 = 304,                   /* $@44  */
  YYSYMBOL_derived_def = 305,              /* derived_def  */
  YYSYMBOL_306_45 = 306,                   /* $@45  */
  YYSYMBOL_derived_body = 307,             /* derived_body  */
  YYSYMBOL_debug_sentence = 308,           /* debug_sentence  */
  YYSYMBOL_309_46 = 309,                   /* $@46  */
  YYSYMBOL_310_47 = 310,                   /* $@47  */
  YYSYMBOL_command = 311,                  /* command  */
  YYSYMBOL_help = 312,                     /* help  */
  YYSYMBOL_print = 313,                    /* print  */
  YYSYMBOL_314_48 = 314,                   /* $@48  */
  YYSYMBOL_315_49 = 315,                   /* $@49  */
  YYSYMBOL_display = 316,                  /* display  */
  YYSYMBOL_317_50 = 317,                   /* $@50  */
  YYSYMBOL_318_51 = 318,                   /* $@51  */
  YYSYMBOL_plot = 319,                     /* plot  */
  YYSYMBOL_undisplay = 320,                /* undisplay  */
  YYSYMBOL_set = 321,                      /* set  */
  YYSYMBOL_breakpoint = 322,               /* breakpoint  */
  YYSYMBOL_323_52 = 323,                   /* $@52  */
  YYSYMBOL_324_53 = 324,                   /* $@53  */
  YYSYMBOL_325_54 = 325,                   /* $@54  */
  YYSYMBOL_326_55 = 326,                   /* $@55  */
  YYSYMBOL_met_name = 327,                 /* met_name  */
  YYSYMBOL_eval = 328,                     /* eval  */
  YYSYMBOL_329_56 = 329,                   /* $@56  */
  YYSYMBOL_330_57 = 330,                   /* $@57  */
  YYSYMBOL_apply = 331,                    /* apply  */
  YYSYMBOL_332_58 = 332,                   /* $@58  */
  YYSYMBOL_333_59 = 333,                   /* $@59  */
  YYSYMBOL_describe = 334,                 /* describe  */
  YYSYMBOL_335_60 = 335,                   /* $@60  */
  YYSYMBOL_336_61 = 336,                   /* $@61  */
  YYSYMBOL_simple_formula_term_goal = 337, /* simple_formula_term_goal  */
  YYSYMBOL_338_62 = 338,                   /* $@62  */
  YYSYMBOL_customization_def = 339,        /* customization_def  */
  YYSYMBOL_customization_body = 340,       /* customization_body  */
  YYSYMBOL_customization_list = 341,       /* customization_list  */
  YYSYMBOL_customization_element = 342,    /* customization_element  */
  YYSYMBOL_python_init = 343,              /* python_init  */
  YYSYMBOL_time_unit = 344                 /* time_unit  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   954

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  150
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  195
/* YYNRULES -- Number of rules.  */
#define YYNRULES  434
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  774

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   404


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   435,   435,   436,   437,   440,   447,   452,   453,   456,
     457,   460,   461,   464,   465,   468,   469,   472,   473,   476,
     477,   480,   510,   513,   525,   528,   540,   550,   553,   556,
     557,   558,   561,   563,   565,   567,   569,   571,   573,   575,
     577,   579,   581,   583,   585,   587,   589,   591,   596,   602,
     619,   624,   625,   649,   649,   649,   680,   684,   685,   688,
     705,   726,   750,   754,   760,   766,   780,   797,   826,   832,
     840,   843,   844,   848,   847,   898,   902,   901,   960,   967,
     967,   970,   971,   986,  1014,  1024,  1026,  1030,  1029,  1099,
    1105,  1110,  1111,  1125,  1126,  1129,  1130,  1131,  1139,  1140,
    1145,  1171,  1143,  1200,  1198,  1252,  1259,  1264,  1271,  1277,
    1283,  1289,  1295,  1302,  1306,  1312,  1318,  1324,  1330,  1336,
    1342,  1348,  1354,  1360,  1368,  1374,  1382,  1383,  1387,  1392,
    1397,  1403,  1404,  1410,  1412,  1413,  1407,  1467,  1471,  1478,
    1481,  1490,  1489,  1518,  1520,  1522,  1527,  1526,  1556,  1555,
    1587,  1586,  1618,  1622,  1647,  1653,  1661,  1665,  1671,  1697,
    1713,  1736,  1749,  1772,  1788,  1789,  1793,  1795,  1802,  1808,
    1801,  1828,  1827,  1842,  1848,  1855,  1854,  1866,  1870,  1877,
    1883,  1876,  1892,  1898,  1891,  1906,  1922,  1932,  1938,  1931,
    1955,  1963,  1954,  1979,  1981,  1985,  2002,  2005,  2009,  2015,
    2016,  2019,  2027,  2028,  2038,  2040,  2050,  2049,  2113,  2112,
    2176,  2177,  2180,  2206,  2216,  2251,  2262,  2264,  2267,  2271,
    2275,  2279,  2285,  2323,  2335,  2341,  2347,  2353,  2359,  2365,
    2373,  2379,  2397,  2422,  2426,  2442,  2465,  2466,  2470,  2472,
    2474,  2478,  2483,  2488,  2493,  2564,  2563,  2682,  2681,  2744,
    2745,  2749,  2752,  2751,  2762,  2766,  2792,  2800,  2790,  2816,
    2826,  2828,  2832,  2833,  2842,  2852,  2859,  2863,  2864,  2874,
    2873,  2884,  2888,  2892,  2896,  2900,  2904,  2910,  2911,  2914,
    2915,  2918,  2919,  2922,  2923,  2926,  2926,  2940,  2943,  2947,
    2952,  2964,  2964,  2986,  3008,  3018,  3023,  3024,  3027,  3029,
    3065,  3067,  3076,  3075,  3138,  3165,  3180,  3136,  3201,  3207,
    3215,  3222,  3227,  3233,  3239,  3246,  3256,  3260,  3264,  3268,
    3268,  3268,  3281,  3280,  3292,  3307,  3325,  3325,  3325,  3329,
    3335,  3339,  3340,  3344,  3345,  3346,  3347,  3348,  3349,  3350,
    3351,  3352,  3353,  3357,  3361,  3366,  3370,  3374,  3380,  3390,
    3396,  3401,  3414,  3427,  3432,  3438,  3444,  3454,  3467,  3474,
    3481,  3488,  3495,  3504,  3509,  3518,  3522,  3522,  3522,  3530,
    3534,  3538,  3542,  3546,  3550,  3556,  3562,  3562,  3562,  3572,
    3578,  3584,  3588,  3592,  3600,  3604,  3609,  3616,  3620,  3624,
    3628,  3632,  3636,  3640,  3644,  3651,  3655,  3655,  3655,  3661,
    3665,  3669,  3673,  3673,  3673,  3691,  3694,  3699,  3699,  3699,
    3707,  3707,  3707,  3716,  3716,  3716,  3729,  3728,  3810,  3813,
    3814,  3817,  3818,  3821,  3825,  3829,  3833,  3837,  3846,  3857,
    3861,  3865,  3869,  3873,  3877
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LEFTPAR", "RIGHTPAR",
  "PDDL_DEFINE", "PDDL_DOMAIN", "PDDL_DOMAINREF", "PDDL_PROBLEM",
  "PDDL_CONSTANTS", "PDDL_NAME", "PDDL_VAR", "PYTHON_CODE", "PDDL_NUMBER",
  "PDDL_DNUMBER", "PDDL_REQUIREMENTS", "PDDL_TYPES", "PDDL_HYPHEN",
  "PDDL_EITHER", "PDDL_STRIPS", "PDDL_TYPING",
  "PDDL_NEGATIVE_PRECONDITIONS", "PDDL_DISJUNCTIVE_PRECONDITIONS",
  "PDDL_EQUALITY", "PDDL_EXISTENTIAL_PRECONDITIONS",
  "PDDL_UNIVERSAL_PRECONDITIONS", "PDDL_QUANTIFIED_PRECONDITIONS",
  "PDDL_CONDITIONAL_EFFECTS", "PDDL_FLUENTS", "PDDL_ADL",
  "PDDL_DURATIVE_ACTIONS", "PDDL_DERIVED_PREDICATES",
  "PDDL_TIMED_INITIAL_LITERALS", "PDDL_PREDICATES", "PDDL_FUNCTIONS",
  "PDDL_ACTION", "PDDL_PARAMETERS", "PDDL_NOT", "PDDL_PRECONDITION",
  "PDDL_IMPLY", "PDDL_AND", "PDDL_OR", "PDDL_EXISTS", "PDDL_FORALL",
  "PLUS", "DIVIDE", "MULTIPLY", "POW", "ABS", "SQRT", "GREATHER", "LESS",
  "EQUAL", "DISTINCT", "GREATHER_EQUAL", "LESS_EQUAL", "PDDL_EFFECT",
  "PDDL_ASSIGN", "PDDL_SCALE_UP", "PDDL_SCALE_DOWN", "PDDL_INCREASE",
  "PDDL_DECREASE", "PDDL_WHEN", "PDDL_GOAL", "PDDL_AT", "PDDL_ATSTART",
  "PDDL_ATEND", "PDDL_BETWEEN", "PDDL_OBJECT", "PDDL_INIT", "PDDL_OVERALL",
  "PDDL_DURATIONVAR", "STARTVAR", "ENDVAR", "PDDL_DERIVED",
  "PDDL_CONDITION", "PDDL_DURATION", "PDDL_DURATIVE_ACTION",
  "HTN_EXPANSION", "META_TAGS", "META", "TAG", "HTN_TASK", "HTN_TASKS",
  "HTN_ACHIEVE", "HTN_METHOD", "HTN_TASKSGOAL", "HTN_INLINE",
  "HTN_INLINECUT", "HTN_TEXT", "LEFTBRAC", "RIGHTBRAC", "EXCLAMATION",
  "RANDOM", "SORTBY", "ASC", "DESC", "PDDL_BIND", "MAINTAIN", "PPRINT",
  "PDDL_AND_EVERY", "CUSTOMIZATION", "TIMEUNIT", "TIMESTART", "TIMEFORMAT",
  "TIMEHORIZON", "RELTIMEHORIZON", "THOURS", "TMINUTES", "TSECONDS",
  "TDAYS", "TMONTHS", "TYEARS", "PYTHON_INIT", "DBG_DEBUG", "DBG_QUIT",
  "DBG_BREAKPOINT", "DBG_WATCH", "DBG_CONTINUE", "DBG_HELP", "DBG_PATH",
  "DBG_PRINT", "DBG_DISPLAY", "DBG_DESCRIBE", "DBG_UNDISPLAY", "DBG_STATE",
  "DBG_AGENDA", "DBG_PLAN", "DBG_NEXT", "DBG_NEXP", "DBG_SET",
  "DBG_VIEWER", "DBG_DOTPATH", "DBG_TMPDIR", "DBG_PLOT", "DBG_CAUSAL",
  "DBG_MEM", "DBG_SELECT", "DBG_VERBOSE", "DBG_ON", "DBG_OFF",
  "DBG_OPTIONS", "DBG_TERMTABLE", "DBG_PREDICATES", "DBG_TASKS",
  "DBG_ENABLE", "DBG_DISABLE", "DBG_EVAL", "DBG_VERBOSITY", "DBG_APPLY",
  "$accept", "pddl_root", "problem_definition", "domain_definition",
  "domain_definition_2", "domain_definition_31", "domain_definition_32",
  "domain_definition_3", "domain_definition_4", "domain_definition_5",
  "domain_definition_6", "domain_definition_7", "domainName",
  "problemName", "domainRef", "require_def", "require_key_list",
  "require_key", "term_name", "types_def", "constants_def", "typed_list",
  "$@1", "$@2", "constant_list", "constant_def_list", "type",
  "type_def_list", "type_ref", "type_ref_list", "predicates_def",
  "atomic_formula_skeleton_list", "atomic_formula_skeleton", "$@3",
  "derived_formula_skeleton", "$@4", "variable_typed_list", "$@5",
  "var_typel", "functions_def", "function_typed_list", "function_def",
  "$@6", "opt_type", "code", "structure_def_list", "structure_def",
  "action_def", "@7", "$@8", "htn_task_def", "$@9", "duration_constraints",
  "sdur_constraint", "simple_duration_constraint",
  "sduration_constraint_list", "methods_def_body", "method_list",
  "method_body", "$@10", "$@11", "@12", "meta_list", "tag_list",
  "tag_element", "@13", "task_def", "inlinetask", "@14", "@15",
  "atomic_task_formula", "$@16", "task_network", "task_list",
  "task_element", "preconditions_def", "goal_def", "@17", "$@18", "@19",
  "@20", "simple_goal_def", "@21", "$@22", "@23", "$@24", "@25", "$@26",
  "@27", "$@28", "timed_goal", "order", "v_list", "v_crit",
  "goal_def_list", "atomic_formula_term_effect", "literal_effect", "$@29",
  "atomic_formula_term_goal", "$@30", "term_list", "term", "number", "var",
  "variable", "f_comp", "binary_comp", "fluent_exp", "silly_exp",
  "unary_op", "binary_op", "f_head", "$@31", "f_head_ref", "$@32",
  "effect_def", "effect", "$@33", "timed_effect", "c_effect", "@34",
  "$@35", "c_effect_list", "p_effect", "p_effect_list", "cond_effect",
  "$@36", "assign_op", "problemBody", "problemBody21", "problemBody22",
  "problemBody2", "problemBody3", "$@37", "object_declaration", "init",
  "init_el", "$@38", "optional_repetition", "init_el_list", "goal",
  "literal_name", "atomic_formula_name", "$@39", "durative_action_def",
  "@40", "$@41", "$@42", "sdur_constraint_list", "pduration_constraints",
  "time_specifier", "time_point", "number_time_point", "$@43", "$@44",
  "derived_def", "$@45", "derived_body", "debug_sentence", "$@46", "$@47",
  "command", "help", "print", "$@48", "$@49", "display", "$@50", "$@51",
  "plot", "undisplay", "set", "breakpoint", "$@52", "$@53", "$@54", "$@55",
  "met_name", "eval", "$@56", "$@57", "apply", "$@58", "$@59", "describe",
  "$@60", "$@61", "simple_formula_term_goal", "$@62", "customization_def",
  "customization_body", "customization_list", "customization_element",
  "python_init", "time_unit", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-628)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-403)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,  -628,    37,    62,  -628,  -628,  -628,   -29,   311,  -628,
     675,  -628,   368,   195,   569,  -628,    42,  -628,  -628,   710,
     596,    21,  -628,    81,  -628,  -628,   -74,   -72,  -628,    95,
      10,   114,   141,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,   152,   152,   166,   159,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,   231,   357,
     431,   442,   471,   182,   484,  -628,  -628,  -628,  -628,   552,
     599,  -628,   206,   216,  -628,   227,   244,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
     227,  -628,  -628,  -628,  -628,  -628,   227,   227,  -628,   198,
     236,   239,   248,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
     244,   302,  -628,  -628,   327,   349,   325,   663,    83,   676,
    -628,   152,  -628,   152,   152,   318,   345,   169,  -628,   356,
    -628,   672,  -628,    -1,  -628,   320,  -628,  -628,  -628,  -628,
      31,  -628,   295,  -628,   152,    11,   395,   397,  -628,  -628,
    -628,  -628,   402,  -628,   417,   428,   152,   453,   374,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,   362,   372,   415,
     463,  -628,   486,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,   511,    65,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
     597,  -628,  -628,   515,   128,  -628,   152,   524,   604,   254,
    -628,   677,  -628,  -628,   506,   546,   318,  -628,  -628,   561,
     565,   325,  -628,   -30,  -628,  -628,   530,  -628,   603,   -15,
    -628,   200,  -628,  -628,  -628,  -628,  -628,   244,   244,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,   314,  -628,   244,  -628,   207,    29,  -628,   495,   609,
    -628,  -628,   606,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,   664,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,   244,   671,  -628,   695,   701,  -628,  -628,  -628,   251,
    -628,   692,   597,  -628,  -628,  -628,  -628,  -628,  -628,   152,
    -628,  -628,   694,  -628,   152,   185,   709,   696,   698,   531,
    -628,  -628,  -628,  -628,   727,   384,   -26,  -628,  -628,  -628,
     731,   244,  -628,  -628,   733,   749,   715,   759,   207,  -628,
    -628,  -628,  -628,  -628,  -628,   719,   771,  -628,   772,  -628,
     740,  -628,  -628,  -628,  -628,  -628,   495,  -628,   773,  -628,
      36,   774,  -628,   750,   776,   152,   777,  -628,   152,   495,
     473,   778,  -628,   762,  -628,   325,  -628,  -628,  -628,   251,
    -628,  -628,   780,  -628,  -628,  -628,  -628,   792,   797,   430,
     787,   717,   788,   793,  -628,   400,  -628,  -628,  -628,  -628,
     244,   728,   408,  -628,   806,   244,   244,  -628,  -628,   314,
    -628,  -628,   207,   359,   495,  -628,   575,  -628,   583,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,   495,   495,   810,
    -628,   495,  -628,   466,  -628,   517,  -628,   811,  -628,   600,
     812,  -628,   152,  -628,  -628,   813,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,   814,   815,
     819,   825,   826,   832,   833,   498,  -628,  -628,   837,   834,
     760,  -628,  -628,  -628,  -628,   828,  -628,  -628,   838,   842,
     843,   844,  -628,   244,  -628,  -628,  -628,  -628,   845,  -628,
    -628,  -628,   495,   495,  -628,  -628,   399,  -628,  -628,   846,
    -628,  -628,  -628,  -628,  -628,    57,    83,  -628,   490,   847,
     848,   849,   850,   854,  -628,  -628,  -628,  -628,  -628,   152,
     856,   152,   498,   821,  -628,   859,  -628,  -628,   226,   251,
    -628,  -628,  -628,  -628,   860,  -628,   628,  -628,   861,   862,
    -628,  -628,  -628,  -628,  -628,   251,  -628,   851,   728,  -628,
     728,   728,  -628,  -628,   863,   498,   639,    40,   865,   496,
     202,   272,   272,   867,  -628,  -628,  -628,   868,  -628,  -628,
     244,   244,  -628,  -628,  -628,  -628,   302,   500,  -628,   251,
     345,  -628,  -628,   870,  -628,  -628,   763,  -628,  -628,   790,
    -628,  -628,   316,  -628,   244,  -628,  -628,  -628,   303,  -628,
    -628,    45,  -628,   303,   130,   303,   173,   197,  -628,  -628,
     871,   872,   873,  -628,  -628,  -628,  -628,   836,   802,   124,
     875,   877,  -628,   647,   498,   859,   874,  -628,   878,   237,
     118,   378,   510,   519,   879,   244,   244,  -628,   211,   150,
    -628,  -628,   223,  -628,   242,  -628,  -628,  -628,  -628,   244,
     829,   883,   152,    26,    15,  -628,   803,  -628,  -628,  -628,
     885,  -628,   331,  -628,   627,   495,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   495,   495,   495,
    -628,   302,   302,   655,  -628,  -628,  -628,  -628,   302,   886,
     693,  -628,  -628,  -628,   877,   641,   877,   699,  -628,   798,
     591,  -628,  -628,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   902,   903,
    -628,  -628,  -628,  -628,   905,   839,   840,   841,   852,   853,
     807,   728,   705,  -628,   711,  -628,   909,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,   470,  -628,   713,   244,  -628,  -628,
    -628,  -628,  -628,  -628,   858,  -628,   302,   836,   911,   835,
    -628,   226,   912,  -628
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   329,     0,     0,     3,     2,     4,     0,     0,     1,
       0,    24,     0,     0,     0,   330,   395,   396,   332,   348,
     366,   376,   413,     0,   342,   343,     0,     0,   344,     0,
       0,     0,     0,   407,   410,   327,   331,   333,   334,   336,
     335,   337,   338,   340,   341,   339,     0,     0,    99,     0,
       6,     8,    10,    12,    14,    16,    18,    20,     0,     0,
       0,     0,     0,     0,     0,    95,    98,    96,    97,     0,
       0,    27,     0,     0,   399,     0,     0,   350,   362,   361,
     349,   351,   352,   358,   353,   354,   355,   357,   356,   359,
     360,   363,   364,   365,   369,   370,   371,   372,   374,   373,
       0,   382,   375,   379,   380,   383,     0,     0,   386,   387,
     391,   389,   393,   384,   385,   345,   346,   347,   400,   401,
       0,     0,   328,    48,     0,     0,    57,     0,     0,     0,
      85,     0,   322,     0,     0,   419,    91,     0,     7,     0,
      13,     0,    15,     0,    17,     0,    19,    21,    99,    94,
       0,     9,     0,    11,     0,     0,     0,     0,   278,   280,
     282,   284,     0,   285,     0,     0,     0,   405,   319,   397,
     177,   178,   194,   193,   367,   377,   414,     0,     0,     0,
       0,   408,   319,   266,   204,   411,   261,   254,   260,    23,
      25,    60,     0,    58,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    47,    46,
       0,    56,    65,     0,    52,    75,     0,     0,     0,     0,
     100,     0,   304,   103,     0,     0,   420,   421,    92,     0,
       0,    57,   296,     0,   277,     5,     0,   283,     0,     0,
     279,     0,   281,   416,   406,   403,   166,     0,     0,   179,
     182,   187,   190,   224,   225,   226,   229,   227,   228,   316,
     317,   319,   314,     0,   168,     0,   175,   208,     0,     0,
     313,   318,     0,   398,   368,   378,   415,   388,   392,   390,
     394,   409,   251,     0,   252,   256,   272,   273,   274,   275,
     276,     0,     0,   206,     0,     0,   412,    50,    61,     0,
      31,     0,     0,    49,    66,    53,    73,    70,    72,     0,
      84,    86,     0,    78,     0,    91,     0,     0,     0,     0,
     418,   422,   428,    26,     0,     0,     0,   286,   210,   404,
       0,     0,   202,   202,     0,     0,     0,     0,     0,   218,
     219,   220,   221,   222,   171,     0,     0,   210,     0,   210,
       0,   216,   217,   235,   230,   234,     0,   233,     0,   320,
       0,     0,   262,     0,     0,     0,     0,   210,     0,     0,
       0,     0,    64,     0,    67,    57,    63,    28,    30,     0,
      79,    87,     0,    76,   325,   324,   323,     0,     0,     0,
       0,     0,     0,     0,   287,   291,   288,   297,   289,   300,
       0,   137,     0,   185,     0,   180,   183,    79,    79,   319,
     167,   169,   199,   196,     0,   174,     0,   173,     0,   238,
     241,   243,   242,   244,   239,   240,   247,     0,     0,     0,
     195,     0,   265,     0,    79,     0,   271,     0,   205,     0,
       0,   255,     0,    59,    54,     0,    81,    79,    79,    79,
      79,    79,   429,   430,   431,   432,   434,   433,     0,     0,
       0,     0,     0,     0,     0,     0,   302,   319,     0,     0,
       0,   417,   212,   211,   215,   213,   186,   203,     0,     0,
       0,     0,   315,     0,   200,   197,   198,   201,     0,   176,
     209,   210,   236,     0,   223,   321,   319,   253,   263,     0,
     269,   259,   207,   264,    68,     0,     0,    74,    80,     0,
       0,     0,     0,     0,   423,   427,   424,   425,   426,     0,
       0,     0,     0,     0,   210,     0,   298,   139,     0,     0,
     181,   184,   188,   191,     0,   172,     0,   237,     0,     0,
     257,   267,    62,    69,    55,     0,    82,    89,   137,    77,
     137,   137,   301,   245,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,   145,   143,     0,   152,   214,
       0,     0,   170,   248,   232,   231,     0,     0,    83,     0,
      91,   101,   305,     0,   210,   290,   295,   303,   292,     0,
     138,   140,     0,   153,     0,   146,   148,   150,     0,   113,
     105,     0,   155,     0,     0,     0,     0,     0,   157,   299,
       0,     0,     0,   270,   268,    90,    88,   164,     0,     0,
       0,   126,   131,     0,     0,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   210,     0,     0,
     161,   154,     0,   159,     0,   163,   189,   192,   258,     0,
     249,     0,     0,     0,     0,   104,     0,   132,   246,   294,
       0,   141,     0,   124,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,     0,     0,     0,   160,   158,   162,   165,     0,     0,
       0,   310,   306,   133,     0,     0,     0,     0,   293,     0,
       0,   106,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,   250,   102,   312,     0,     0,     0,     0,     0,     0,
       0,   137,     0,   127,     0,   130,     0,   112,   118,   123,
     111,   117,   122,   108,   114,   119,   110,   116,   121,   109,
     115,   120,   147,   149,     0,   308,     0,     0,   134,   129,
     128,   142,   311,   309,     0,   135,     0,   164,     0,     0,
     307,     0,     0,   136
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -628,  -628,  -628,  -628,  -628,   864,   857,   855,   869,   876,
     866,   880,  -628,  -628,  -628,   881,   607,   794,   -43,  -628,
    -628,   411,  -628,  -628,  -218,  -628,  -368,  -628,  -374,  -628,
    -628,   702,  -628,  -628,  -628,  -628,   317,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -313,   882,  -628,  -628,  -628,  -628,
    -628,  -628,  -510,  -627,  -592,  -628,  -628,  -471,  -591,  -628,
    -628,  -628,  -536,  -628,  -628,  -628,   366,  -628,  -628,  -628,
    -628,  -628,   148,  -114,  -512,   163,   -76,  -628,  -628,  -628,
    -628,   -99,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,   520,  -628,   598,   650,   642,  -628,  -628,  -628,
    -340,  -628,  -396,  -628,  -260,  -628,  -628,  -328,  -628,  -628,
    -628,  -628,  -628,   643,  -628,  -628,  -566,  -628,  -628,   502,
    -628,  -628,  -628,  -294,  -628,  -628,  -628,  -628,  -628,   782,
     775,   779,   781,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -508,   477,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -160,   474,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,  -628,
    -628,  -628,  -628,  -628,  -628,  -628,  -628,   131,  -628,   -42,
    -628,  -628,   721,   -54,  -628
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     4,     5,    50,    51,    52,    53,    54,    55,
      56,    57,    13,    14,    73,    58,   301,   302,   353,    59,
      60,   213,   379,   506,   192,   193,   375,   214,   376,   505,
      61,   217,   218,   380,   315,   449,   445,   446,   508,    62,
     219,   311,   447,   580,   229,    63,    64,    65,   312,   617,
      66,   318,   598,   599,   600,   664,   620,   621,   622,   731,
     765,   767,   470,   559,   591,   699,   564,   565,   635,   636,
     566,   637,   567,   601,   602,   650,   477,   338,   483,   414,
     347,   170,   332,   478,   333,   479,   334,   570,   335,   571,
     171,   487,   411,   412,   405,   183,   184,   367,   172,   349,
     402,   473,   354,   343,   355,   173,   268,   356,   538,   427,
     428,   522,   584,   357,   491,   689,   185,   362,   186,   187,
     363,   576,   433,   188,   577,   437,   541,   294,   157,   158,
     159,   160,   161,   238,   162,   163,   397,   467,   625,   325,
     327,   398,   399,   524,    67,   317,   618,   730,   756,   692,
     269,   295,   271,   272,   431,    68,   221,   316,     6,     7,
     122,    35,    36,    37,   100,   274,    38,   106,   275,    39,
      40,    41,    42,    76,   273,    75,   329,   245,    43,   120,
     281,    44,   121,   296,    45,   107,   276,   167,   328,    69,
     225,   226,   227,    70,   458
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     169,   371,   384,   124,   125,   344,   474,   416,   270,   418,
     612,   444,   581,   324,   582,   583,   568,   558,   656,   165,
     474,  -381,   474,     1,   691,     2,   127,   439,   429,   656,
     657,   164,   345,   130,   131,   101,   663,   400,   231,   232,
     126,   440,     8,   474,   181,  -402,   123,   128,   638,   640,
     123,   603,   605,   231,   232,   113,    74,   109,   110,   111,
     401,   542,     9,   114,   129,   130,   131,   123,   504,   523,
     436,   135,   702,   132,   112,   298,   133,   463,   413,   231,
     232,   134,   299,   136,   211,    10,   488,   -51,   220,   641,
     222,   223,   641,   212,   641,   108,   561,   755,   136,   492,
     493,   336,   165,   495,   657,   132,   657,   696,   133,   115,
     165,   230,   135,   134,   164,   718,   719,   660,   346,   694,
     603,   592,   721,   243,   136,   267,   554,   641,   118,   763,
     641,   543,   641,   638,   292,   562,  -326,   563,   304,   293,
     474,   657,   475,   657,   136,   305,   102,   103,   104,   116,
     117,   536,   413,   638,   684,   119,   475,   443,   475,   586,
     474,   569,   123,   105,   537,   539,   -22,   348,   126,   561,
     358,   330,   331,   306,   127,   128,   638,   578,   126,   475,
     643,   561,   695,   697,   556,   128,   147,   337,   168,   668,
     669,   670,   129,   130,   131,   758,    48,   228,    49,   -93,
     768,   561,   129,   130,   131,   592,   593,   123,   562,   652,
     563,   615,   123,   154,   592,   364,   653,   654,   339,   155,
     562,   123,   563,   732,   561,   734,   638,   474,   659,   560,
     166,   174,    48,   132,   137,   -93,   133,   175,   176,   385,
     562,   134,   563,   132,   623,   638,   133,   168,   546,   482,
     177,   134,   372,   561,   373,   404,   374,   309,   310,   568,
     135,   123,   561,   562,   645,   563,   381,   616,   231,   232,
     135,   383,   136,   685,   561,   592,   475,   561,   340,   341,
     342,   594,   136,   614,   595,   596,   594,   474,   178,   595,
     596,   179,   562,   561,   563,   594,   475,   683,   595,   596,
     180,   562,   267,   563,   126,   182,   638,   426,   665,   666,
     667,   128,    11,   562,    12,   563,   562,   293,   563,   592,
     627,   224,   293,   561,   468,   426,   123,   293,   129,   130,
     131,   189,   562,   686,   563,   191,   374,   703,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   714,   715,
     716,   717,   466,   190,   561,   131,   628,   228,    48,   472,
     139,   -93,   562,   475,   563,   126,   629,   630,   631,   132,
     632,   633,   133,   472,    46,   472,    47,   134,   246,   259,
     260,   629,   700,   631,   123,   632,   633,   395,   396,   129,
     130,   131,   293,   562,   132,   563,   472,   133,   233,   374,
     594,   235,   134,   595,   596,   236,   562,   534,   563,   123,
     123,   247,   471,   248,   249,   250,   251,   252,   123,   339,
     239,   351,   352,   475,   253,   254,   255,   256,   257,   258,
     132,   241,    48,   133,   141,   -93,   283,   463,   134,   259,
     260,   261,   285,    48,   262,   143,   -93,   604,   606,   671,
     672,   673,   464,   293,   485,   486,   286,   287,   288,   289,
     290,   291,   374,   244,   259,   260,   263,   465,   264,   496,
     497,   265,    48,   266,   145,   -93,   466,   280,   553,   340,
     341,   342,   277,   123,   639,   148,   374,   145,   -93,   642,
     282,   644,   278,   472,   610,   611,   123,   292,   350,   589,
     590,   339,   374,   370,   613,   123,   339,   545,   351,   352,
     283,   351,   352,   472,   466,   297,   604,   597,   634,   303,
     725,   726,   727,   283,   728,   729,   284,   123,   307,   285,
     286,   287,   288,   289,   290,   279,   374,   452,   453,   454,
     455,   456,   457,   286,   287,   288,   289,   290,   291,   597,
     320,   259,   260,    48,   283,   150,   -93,   500,   319,   681,
     682,   340,   341,   342,   597,   322,   340,   341,   342,   323,
      71,   292,    72,   687,   286,   287,   288,   289,   290,   489,
     472,   674,   675,   676,   292,   123,   339,   490,   351,   352,
     677,   678,   679,   123,   339,   597,   351,   352,   300,   232,
      48,   -29,   152,   -93,   502,   215,   326,   216,   -71,   693,
     123,   339,   345,   351,   352,   292,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     662,   701,   573,   389,   390,   391,   392,   393,   123,   339,
     472,   351,   352,   587,   656,   733,   340,   341,   342,   123,
     339,   658,   351,   352,   340,   341,   342,   123,   339,   720,
     351,   352,   668,   669,   670,   123,   339,   360,   351,   352,
     359,   340,   341,   342,   365,   208,   209,   215,   313,   216,
     314,   764,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   377,   723,   368,   340,
     341,   342,   656,   735,   370,   129,   130,   131,   656,   759,
     340,   341,   342,   386,   656,   760,   754,   762,   340,   341,
     342,    93,    94,    95,   480,   481,   340,   341,   342,   123,
     382,   394,   387,   724,   388,   403,   407,    96,    97,    98,
      99,   208,   209,   725,   726,   727,   132,   728,   729,   133,
     123,   499,   408,   434,   134,   409,   247,   419,   248,   249,
     250,   251,   252,   410,   509,   510,   511,   512,   513,   253,
     254,   255,   256,   257,   258,   415,   417,   430,   432,   435,
     442,   438,   441,   448,   420,   421,   422,   423,   424,   425,
      15,    16,    17,    18,    19,   450,    20,    21,    22,    23,
     451,   459,   461,    24,    25,    26,   460,   462,   469,    27,
     476,    28,    29,    30,   494,   501,   503,   507,   514,   515,
      31,    32,    33,   516,    34,    77,    78,    79,    80,   517,
     518,    81,    82,    83,    84,   519,   521,   527,    85,    86,
      87,   526,   530,   528,    88,   529,   531,   532,   533,   535,
     540,   547,   548,   549,   550,    89,    90,    91,   551,    92,
     552,   555,   557,   624,   572,   574,   575,   585,   579,   588,
     607,   626,   609,   619,   649,   646,   647,   648,   651,   655,
     656,   662,   757,   680,   661,   688,   690,   736,   652,   698,
     722,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   378,
     665,   668,   671,   761,   766,   770,   773,   544,   771,   772,
     308,   210,   138,   674,   677,   153,   151,   144,   140,   608,
     769,   406,   484,   361,   366,   498,   142,   369,   234,   240,
     520,   525,   146,   237,   242,     0,   149,   321,     0,     0,
       0,     0,     0,     0,   156
};

static const yytype_int16 yycheck[] =
{
      76,   295,   315,    46,    47,   265,   402,   347,   168,   349,
     576,   379,   548,   231,   550,   551,   528,   525,     3,    73,
     416,     0,   418,     1,   651,     3,    15,   367,   356,     3,
     621,    73,     3,    34,    35,    14,   628,    63,    68,    69,
       9,   369,     5,   439,   120,     3,    10,    16,     3,     4,
      10,   561,   562,    68,    69,   127,    14,   131,   132,   133,
      86,     4,     0,   135,    33,    34,    35,    10,   442,   465,
     364,   101,   664,    74,   148,    10,    77,    37,   338,    68,
      69,    82,    17,   113,     1,   114,   414,     4,   131,   601,
     133,   134,   604,    10,   606,    14,    51,   724,   113,   427,
     428,   261,   156,   431,   695,    74,   697,    92,    77,    14,
     164,   154,   101,    82,   156,   681,   682,   625,    89,    93,
     630,     3,   688,   166,   113,   168,   522,   639,    14,   756,
     642,   505,   644,     3,    98,    90,   114,    92,    10,   182,
     536,   732,   402,   734,   113,    17,   125,   126,   127,   139,
     140,   491,   412,     3,     4,    14,   416,   375,   418,   555,
     556,   529,    10,   142,   492,   493,     0,   266,     9,    51,
     269,   247,   248,   216,    15,    16,     3,   545,     9,   439,
      50,    51,   653,   654,   524,    16,     4,   263,     3,    71,
      72,    73,    33,    34,    35,   731,     1,    12,     3,     4,
     766,    51,    33,    34,    35,     3,     4,    10,    90,    85,
      92,   579,    10,     7,     3,   291,    92,    93,    11,     3,
      90,    10,    92,   694,    51,   696,     3,   623,   624,     3,
       3,   100,     1,    74,     3,     4,    77,   106,   107,   315,
      90,    82,    92,    74,   584,     3,    77,     3,   508,   409,
      52,    82,     1,    51,     3,   331,   299,     3,     4,   771,
     101,    10,    51,    90,    91,    92,   309,   580,    68,    69,
     101,   314,   113,    50,    51,     3,   536,    51,    71,    72,
      73,    84,   113,   577,    87,    88,    84,   683,    52,    87,
      88,    52,    90,    51,    92,    84,   556,   637,    87,    88,
      52,    90,   345,    92,     9,     3,     3,   350,    71,    72,
      73,    16,     1,    90,     3,    92,    90,   360,    92,     3,
       4,     3,   365,    51,   400,   368,    10,   370,    33,    34,
      35,     4,    90,    91,    92,    10,   379,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   395,     4,    51,    35,    40,    12,     1,   402,
       3,     4,    90,   623,    92,     9,    50,    51,    52,    74,
      54,    55,    77,   416,     6,   418,     8,    82,     4,    65,
      66,    50,    51,    52,    10,    54,    55,     3,     4,    33,
      34,    35,   435,    90,    74,    92,   439,    77,     3,   442,
      84,     4,    82,    87,    88,     3,    90,   483,    92,    10,
      10,    37,     4,    39,    40,    41,    42,    43,    10,    11,
       3,    13,    14,   683,    50,    51,    52,    53,    54,    55,
      74,     3,     1,    77,     3,     4,    37,    37,    82,    65,
      66,    67,    43,     1,    70,     3,     4,   561,   562,    71,
      72,    73,    52,   496,    95,    96,    57,    58,    59,    60,
      61,    62,   505,    10,    65,    66,    92,    67,    94,     3,
       4,    97,     1,    99,     3,     4,   519,    14,   521,    71,
      72,    73,   120,    10,   598,     1,   529,     3,     4,   603,
       4,   605,   120,   536,   570,   571,    10,    98,     3,     3,
       4,    11,   545,     3,     4,    10,    11,    17,    13,    14,
      37,    13,    14,   556,   557,     4,   630,   560,   594,     4,
      50,    51,    52,    37,    54,    55,    40,    10,     4,    43,
      57,    58,    59,    60,    61,   120,   579,   107,   108,   109,
     110,   111,   112,    57,    58,    59,    60,    61,    62,   592,
       4,    65,    66,     1,    37,     3,     4,    40,    52,   635,
     636,    71,    72,    73,   607,     4,    71,    72,    73,     4,
       1,    98,     3,   649,    57,    58,    59,    60,    61,     4,
     623,    71,    72,    73,    98,    10,    11,     4,    13,    14,
      71,    72,    73,    10,    11,   638,    13,    14,     1,    69,
       1,     4,     3,     4,     4,     1,     3,     3,     4,   652,
      10,    11,     3,    13,    14,    98,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       3,     4,     4,   102,   103,   104,   105,   106,    10,    11,
     683,    13,    14,     4,     3,     4,    71,    72,    73,    10,
      11,     4,    13,    14,    71,    72,    73,    10,    11,     4,
      13,    14,    71,    72,    73,    10,    11,     3,    13,    14,
      64,    71,    72,    73,     3,    78,    79,     1,     1,     3,
       3,   757,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     4,     4,     3,    71,
      72,    73,     3,     4,     3,    33,    34,    35,     3,     4,
      71,    72,    73,     4,     3,     4,     3,     4,    71,    72,
      73,   125,   126,   127,   407,   408,    71,    72,    73,    10,
      36,     4,    36,    40,    36,     4,     3,   141,   142,   143,
     144,    78,    79,    50,    51,    52,    74,    54,    55,    77,
      10,   434,     3,     3,    82,    40,    37,    17,    39,    40,
      41,    42,    43,     4,   447,   448,   449,   450,   451,    50,
      51,    52,    53,    54,    55,     4,     4,     4,     4,     3,
      18,     4,     4,     3,    44,    45,    46,    47,    48,    49,
     115,   116,   117,   118,   119,     3,   121,   122,   123,   124,
       3,    14,    14,   128,   129,   130,    89,    14,    80,   134,
       4,   136,   137,   138,     4,     4,     4,     4,     4,     4,
     145,   146,   147,     4,   149,   115,   116,   117,   118,     4,
       4,   121,   122,   123,   124,     3,     3,     3,   128,   129,
     130,     4,     4,    83,   134,    17,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   145,   146,   147,     4,   149,
       4,    40,     3,   100,     4,     4,     4,     4,    17,     4,
       3,    81,     4,     3,    38,     4,     4,     4,    76,     4,
       3,     3,    75,     4,    10,    56,     3,    89,    85,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   302,
      71,    71,    71,     4,    56,     4,     4,   506,    83,   771,
     218,   127,    58,    71,    71,    70,    69,    61,    59,   563,
     767,   333,   412,   283,   292,   433,    60,   294,   156,   164,
     463,   467,    62,   162,   165,    -1,    64,   226,    -1,    -1,
      -1,    -1,    -1,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,     3,   151,   152,   153,   308,   309,     5,     0,
     114,     1,     3,   162,   163,   115,   116,   117,   118,   119,
     121,   122,   123,   124,   128,   129,   130,   134,   136,   137,
     138,   145,   146,   147,   149,   311,   312,   313,   316,   319,
     320,   321,   322,   328,   331,   334,     6,     8,     1,     3,
     154,   155,   156,   157,   158,   159,   160,   161,   165,   169,
     170,   180,   189,   195,   196,   197,   200,   294,   305,   339,
     343,     1,     3,   164,    14,   325,   323,   115,   116,   117,
     118,   121,   122,   123,   124,   128,   129,   130,   134,   145,
     146,   147,   149,   125,   126,   127,   141,   142,   143,   144,
     314,    14,   125,   126,   127,   142,   317,   335,    14,   131,
     132,   133,   148,   127,   135,    14,   139,   140,    14,    14,
     329,   332,   310,    10,   168,   168,     9,    15,    16,    33,
      34,    35,    74,    77,    82,   101,   113,     3,   155,     3,
     158,     3,   159,     3,   160,     3,   161,     4,     1,   195,
       3,   156,     3,   157,     7,     3,   165,   278,   279,   280,
     281,   282,   284,   285,   339,   343,     3,   337,     3,   226,
     231,   240,   248,   255,   337,   337,   337,    52,    52,    52,
      52,   226,     3,   245,   246,   266,   268,   269,   273,     4,
       4,    10,   174,   175,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    78,    79,
     167,     1,    10,   171,   177,     1,     3,   181,   182,   190,
     168,   306,   168,   168,     3,   340,   341,   342,    12,   194,
     168,    68,    69,     3,   279,     4,     3,   282,   283,     3,
     280,     3,   281,   168,    10,   327,     4,    37,    39,    40,
      41,    42,    43,    50,    51,    52,    53,    54,    55,    65,
      66,    67,    70,    92,    94,    97,    99,   168,   256,   300,
     301,   302,   303,   324,   315,   318,   336,   120,   120,   120,
      14,   330,     4,    37,    40,    43,    57,    58,    59,    60,
      61,    62,    98,   168,   277,   301,   333,     4,    10,    17,
       1,   166,   167,     4,    10,    17,   168,     4,   181,     3,
       4,   191,   198,     1,     3,   184,   307,   295,   201,    52,
       4,   342,     4,     4,   174,   289,     3,   290,   338,   326,
     226,   226,   232,   234,   236,   238,   301,   226,   227,    11,
      71,    72,    73,   253,   254,     3,    89,   230,   231,   249,
       3,    13,    14,   168,   252,   254,   257,   263,   231,    64,
       3,   245,   267,   270,   226,     3,   246,   247,     3,   263,
       3,   273,     1,     3,   168,   176,   178,     4,   166,   172,
     183,   168,    36,   168,   194,   226,     4,    36,    36,   102,
     103,   104,   105,   106,     4,     3,     4,   286,   291,   292,
      63,    86,   250,     4,   226,   244,   244,     3,     3,    40,
       4,   242,   243,   254,   229,     4,   250,     4,   250,    17,
      44,    45,    46,    47,    48,    49,   168,   259,   260,   257,
       4,   304,     4,   272,     3,     3,   273,   275,     4,   250,
     257,     4,    18,   174,   176,   186,   187,   192,     3,   185,
       3,     3,   107,   108,   109,   110,   111,   112,   344,    14,
      89,    14,    14,    37,    52,    67,   168,   287,   226,    80,
     212,     4,   168,   251,   252,   254,     4,   226,   233,   235,
     186,   186,   301,   228,   242,    95,    96,   241,   257,     4,
       4,   264,   257,   257,     4,   257,     3,     4,   269,   186,
      40,     4,     4,     4,   178,   179,   173,     4,   188,   186,
     186,   186,   186,   186,     4,     4,     4,     4,     4,     3,
     292,     3,   261,   252,   293,   302,     4,     3,    83,    17,
       4,     4,     4,     4,   226,     4,   250,   257,   258,   257,
       4,   276,     4,   178,   171,    17,   254,     4,     4,     4,
       4,     4,     4,   168,   252,    40,   250,     3,   291,   213,
       3,    51,    90,    92,   216,   217,   220,   222,   224,   176,
     237,   239,     4,     4,     4,     4,   271,   274,   176,    17,
     193,   212,   212,   212,   262,     4,   252,     4,     4,     3,
       4,   214,     3,     4,    84,    87,    88,   168,   202,   203,
     204,   223,   224,   202,   223,   202,   223,     3,   216,     4,
     226,   226,   266,     4,   273,   176,   194,   199,   296,     3,
     206,   207,   208,   250,   100,   288,    81,     4,    40,    50,
      51,    52,    54,    55,   226,   218,   219,   221,     3,   223,
       4,   224,   223,    50,   223,    91,     4,     4,     4,    38,
     225,    76,    85,    92,    93,     4,     3,   208,     4,   252,
     291,    10,     3,   204,   205,    71,    72,    73,    71,    72,
      73,    71,    72,    73,    71,    72,    73,    71,    72,    73,
       4,   226,   226,   250,     4,    50,    91,   226,    56,   265,
       3,   203,   299,   168,    93,   207,    92,   207,     4,   215,
      51,     4,   204,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   266,   266,
       4,   266,     4,     4,    40,    50,    51,    52,    54,    55,
     297,   209,   207,     4,   207,     4,    89,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   203,   298,    75,   212,     4,
       4,     4,     4,   203,   226,   210,    56,   211,   266,   225,
       4,    83,   222,     4
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   150,   151,   151,   151,   152,   153,   154,   154,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   162,   163,   164,   164,   165,   166,
     166,   166,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   168,   169,
     170,   171,   171,   172,   173,   171,   171,   174,   174,   174,
     175,   175,   176,   176,   176,   177,   177,   178,   179,   179,
     180,   181,   181,   183,   182,   182,   185,   184,   184,   187,
     186,   188,   188,   188,   189,   190,   190,   192,   191,   193,
     193,   194,   194,   195,   195,   196,   196,   196,   196,   196,
     198,   199,   197,   201,   200,   202,   202,   202,   203,   203,
     203,   203,   203,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   205,   205,   206,   206,   206,   206,
     206,   207,   207,   209,   210,   211,   208,   212,   212,   213,
     213,   215,   214,   216,   216,   216,   218,   217,   219,   217,
     221,   220,   222,   222,   223,   223,   224,   224,   224,   224,
     224,   224,   224,   224,   225,   225,   226,   226,   227,   228,
     226,   229,   226,   226,   226,   230,   226,   226,   226,   232,
     233,   231,   234,   235,   231,   231,   231,   236,   237,   231,
     238,   239,   231,   231,   231,   240,   241,   241,   241,   242,
     242,   243,   244,   244,   245,   245,   247,   246,   249,   248,
     250,   250,   251,   251,   251,   251,   252,   252,   253,   253,
     253,   253,   254,   255,   256,   256,   256,   256,   256,   256,
     257,   257,   257,   257,   257,   257,   258,   258,   259,   259,
     259,   260,   260,   260,   260,   262,   261,   264,   263,   265,
     265,   266,   267,   266,   266,   268,   270,   271,   269,   269,
     269,   269,   272,   272,   273,   273,   273,   274,   274,   276,
     275,   275,   277,   277,   277,   277,   277,   278,   278,   279,
     279,   280,   280,   281,   281,   283,   282,   284,   285,   286,
     286,   287,   286,   286,   288,   288,   289,   289,   290,   290,
     291,   291,   293,   292,   295,   296,   297,   294,   298,   298,
     299,   299,   299,   300,   300,   300,   301,   301,   301,   303,
     304,   302,   306,   305,   307,   307,   309,   310,   308,   308,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   313,   314,   315,   313,   313,
     313,   313,   313,   313,   313,   316,   317,   318,   316,   316,
     316,   316,   316,   316,   319,   319,   320,   321,   321,   321,
     321,   321,   321,   321,   321,   322,   323,   324,   322,   322,
     322,   322,   325,   326,   322,   327,   327,   329,   330,   328,
     332,   333,   331,   335,   336,   334,   338,   337,   339,   340,
     340,   341,   341,   342,   342,   342,   342,   342,   343,   344,
     344,   344,   344,   344,   344
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     6,     4,     2,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     4,     1,     4,     4,     1,     5,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     0,     1,     0,     0,     6,     1,     0,     1,     4,
       1,     2,     4,     1,     1,     1,     2,     1,     1,     2,
       4,     1,     2,     0,     5,     1,     0,     5,     1,     0,
       2,     0,     2,     3,     4,     0,     2,     0,     7,     0,
       2,     0,     1,     0,     2,     1,     1,     1,     1,     1,
       0,     0,    13,     0,    11,     1,     4,     2,     5,     5,
       5,     5,     5,     1,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     1,     2,     1,     4,     5,     5,
       4,     1,     2,     0,     0,     0,    11,     0,     4,     0,
       2,     0,     6,     1,     4,     1,     0,     6,     0,     6,
       0,     5,     1,     2,     2,     1,     1,     2,     4,     3,
       4,     3,     4,     3,     0,     2,     2,     4,     0,     0,
       7,     0,     6,     4,     4,     0,     5,     1,     1,     0,
       0,     6,     0,     0,     6,     4,     5,     0,     0,     9,
       0,     0,     9,     1,     1,     4,     0,     1,     1,     1,
       2,     2,     0,     2,     1,     4,     0,     5,     0,     5,
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     1,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     5,     0,     5,     0,
       2,     2,     0,     5,     1,     4,     0,     0,     9,     5,
       1,     1,     0,     2,     5,     4,     1,     0,     2,     0,
       5,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     2,     1,     2,     1,     0,     3,     4,     4,     1,
       5,     0,     5,     8,     2,     0,     0,     2,     4,     6,
       1,     4,     0,     5,     0,     0,     0,    18,     1,     2,
       1,     4,     2,     1,     1,     4,     1,     1,     1,     0,
       0,     4,     0,     5,     2,     2,     0,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     0,     0,     4,     2,
       2,     2,     2,     2,     2,     2,     0,     0,     4,     2,
       2,     1,     2,     2,     2,     2,     2,     2,     4,     2,
       4,     2,     4,     2,     4,     1,     0,     0,     4,     2,
       2,     2,     0,     0,     5,     0,     1,     0,     0,     4,
       0,     0,     4,     0,     0,     4,     0,     5,     4,     0,
       1,     1,     2,     5,     5,     5,     5,     5,     4,     1,
       1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* domain_definition_2: domain_definition_31  */
#line 454 "yacc/parser.yy"
                                {parser_api->domain->addRequirement("strips");}
#line 2528 "generated/parser.cpp"
    break;

  case 21: /* domain_definition_7: structure_def_list RIGHTPAR  */
#line 481 "yacc/parser.yy"
                                {
                                // tras la declaraci�n de acciones
                                // comprobar que las tareas definidad en la
                                // red de tareas realmente est�n definidas
                                tasktablecit i,e =parser_api->domain->getEndTask();
                                methodcit j, em;
                                bool errors=false;
                                bool changes = true;
                                while(changes){
                                        changes = false;
                                        for(i=parser_api->domain->getBeginTask(); i!= e; i++){
                                        errors = false;
                                        if((*i).second->isCompoundTask()){
                                                em = ((CompoundTask *)(*i).second)->getEndMethod();
                                                for(j=((CompoundTask *)(*i).second)->getBeginMethod();j!= em; j++) {
                                                if(!(*j)->getTaskNetwork()->isWellDefined(errflow,&changes))
                                                {
                                                        errors = true;
                                                };
                                                }
                                        }
                                        if(errors) {
                                                SearchLineInfo sli((*i).second->getMetaId());
                                                snprintf(parerr,256,"In the task network of task `%s' defined near %d [%s].",(*i).second->getName(),sli.lineNumber,sli.fileName.c_str());
                                                yyerror(parerr);
                                        }
                                        }
                                }
                                }
#line 2562 "generated/parser.cpp"
    break;

  case 23: /* domainName: LEFTPAR PDDL_DOMAIN term_name RIGHTPAR  */
#line 514 "yacc/parser.yy"
                                {
                                    if(parser_api->domain->loaded)
                                    {
                                        snprintf(parerr,256,"There is a domain [%s] already loaded.",parser_api->domain->getName());
                                        yyerror(parerr);
                                        YYABORT;
                                    }
                                    parser_api->domain->setDomainName(((string *)(yyvsp[-1].otype))->c_str());
                                parser_api->domain->loaded=true;
                                    delete (string *)(yyvsp[-1].otype);
                                }
#line 2578 "generated/parser.cpp"
    break;

  case 25: /* problemName: LEFTPAR PDDL_PROBLEM term_name RIGHTPAR  */
#line 529 "yacc/parser.yy"
                                {
                                    if(!parser_api->domain || !parser_api->problem)
                                    {
                                        yyerror("No domain loaded.");
                                        YYABORT;
                                    }
                                    parser_api->problem->setProblemName(((string *)(yyvsp[-1].otype))->c_str());
                                    delete (string *)(yyvsp[-1].otype);
                                }
#line 2592 "generated/parser.cpp"
    break;

  case 26: /* domainRef: LEFTPAR PDDL_DOMAINREF term_name RIGHTPAR  */
#line 541 "yacc/parser.yy"
                                {
                                    if(strcmp(parser_api->domain->getName(),((string *)(yyvsp[-1].otype))->c_str()))
                                    {
                                        snprintf(parerr,256,"The problem requires the domain [%s] and the domain loaded is [%s].",((string *)(yyvsp[-1].otype))->c_str(),parser_api->domain->getName());
                                        yyerror(parerr);
                                        YYABORT;
                                    }
                                    delete (string *)(yyvsp[-1].otype);
                                }
#line 2606 "generated/parser.cpp"
    break;

  case 32: /* require_key: PDDL_STRIPS  */
#line 562 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":strips");}
#line 2612 "generated/parser.cpp"
    break;

  case 33: /* require_key: PDDL_TYPING  */
#line 564 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":typing");}
#line 2618 "generated/parser.cpp"
    break;

  case 34: /* require_key: PDDL_NEGATIVE_PRECONDITIONS  */
#line 566 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":negative-preconditions");}
#line 2624 "generated/parser.cpp"
    break;

  case 35: /* require_key: PDDL_DISJUNCTIVE_PRECONDITIONS  */
#line 568 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":disjunctive-preconditions");}
#line 2630 "generated/parser.cpp"
    break;

  case 36: /* require_key: PDDL_EQUALITY  */
#line 570 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":equality");}
#line 2636 "generated/parser.cpp"
    break;

  case 37: /* require_key: PDDL_EXISTENTIAL_PRECONDITIONS  */
#line 572 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":existential-preconditions");}
#line 2642 "generated/parser.cpp"
    break;

  case 38: /* require_key: PDDL_UNIVERSAL_PRECONDITIONS  */
#line 574 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":universal-preconditions");}
#line 2648 "generated/parser.cpp"
    break;

  case 39: /* require_key: PDDL_QUANTIFIED_PRECONDITIONS  */
#line 576 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":quantified-preconditions");}
#line 2654 "generated/parser.cpp"
    break;

  case 40: /* require_key: PDDL_CONDITIONAL_EFFECTS  */
#line 578 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":conditional-effects");}
#line 2660 "generated/parser.cpp"
    break;

  case 41: /* require_key: PDDL_FLUENTS  */
#line 580 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":fluents");}
#line 2666 "generated/parser.cpp"
    break;

  case 42: /* require_key: PDDL_ADL  */
#line 582 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":adl");}
#line 2672 "generated/parser.cpp"
    break;

  case 43: /* require_key: PDDL_DURATIVE_ACTIONS  */
#line 584 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":durative-actions");}
#line 2678 "generated/parser.cpp"
    break;

  case 44: /* require_key: PDDL_DERIVED_PREDICATES  */
#line 586 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":derived-predicates");}
#line 2684 "generated/parser.cpp"
    break;

  case 45: /* require_key: PDDL_TIMED_INITIAL_LITERALS  */
#line 588 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":timed-initial-literals");}
#line 2690 "generated/parser.cpp"
    break;

  case 46: /* require_key: META_TAGS  */
#line 590 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":metatags");}
#line 2696 "generated/parser.cpp"
    break;

  case 47: /* require_key: HTN_EXPANSION  */
#line 592 "yacc/parser.yy"
                                { parser_api->domain->addRequirement(":htn-expansion");}
#line 2702 "generated/parser.cpp"
    break;

  case 48: /* term_name: PDDL_NAME  */
#line 597 "yacc/parser.yy"
                                {
                                (yyval.otype) = new string((yyvsp[0].type_string));
                                }
#line 2710 "generated/parser.cpp"
    break;

  case 49: /* types_def: LEFTPAR PDDL_TYPES typed_list RIGHTPAR  */
#line 603 "yacc/parser.yy"
                                {
                                    if(!parser_api->domain->errtyping && !parser_api->domain->hasRequirement(":typing"))
                                    {
                                        parser_api->domain->errtyping = true;
                                        yyerror("Using a clause that requires `:typing' and is not declared in requirements clause");
                                    }
                                // verificamos que los tipos han sido definidos correctamente
                                if(!fast_parsing){
                                        typetablecit b = parser_api->domain->getBeginType();
                                        typetablecit e = parser_api->domain->getEndType();
                                        for_each(b,e,TestType());
                                }
                                parser_api->domain->buildTypeRelations();
                                }
#line 2729 "generated/parser.cpp"
    break;

  case 51: /* typed_list: %empty  */
#line 624 "yacc/parser.yy"
                                {(yyval.otype) = 0;}
#line 2735 "generated/parser.cpp"
    break;

  case 52: /* typed_list: type_def_list  */
#line 626 "yacc/parser.yy"
                                {
                                vector<Type *> * ptrTypes = (vector<Type *> *) (yyvsp[0].otype);
                                vector<Type *>::iterator i,e;
                                const Type * tmp;
                                e = ptrTypes->end();
                                for(i=ptrTypes->begin(); i != e; i++){
                                        if((tmp=parser_api->domain->addType((*i))) != *i){
                                        SearchLineInfo sli(tmp);
                                        if(sli.lineNumber){
                                        snprintf(parerr,256,"The type `%s' is already defined. (previous definition near %d [%s].",tmp->getName(),sli.lineNumber,sli.fileName.c_str());
                                        yywarning(parerr);
                                        delete (*i);
                                        (*i) = 0;
                                        }
                                        else {
                                        Type * n = parser_api->domain->getModificableType(tmp->getId());
                                        n->setFileId(parser_api->fileid);
                                        n->setLineNumber(lexer->getLineNumber());
                                        }
                                        }
                                }
                                delete ptrTypes;
                                }
#line 2763 "generated/parser.cpp"
    break;

  case 53: /* $@1: %empty  */
#line 649 "yacc/parser.yy"
                                                            {errtypes=false;}
#line 2769 "generated/parser.cpp"
    break;

  case 54: /* $@2: %empty  */
#line 649 "yacc/parser.yy"
                                                                                   {errtypes=true;}
#line 2775 "generated/parser.cpp"
    break;

  case 55: /* typed_list: type_def_list PDDL_HYPHEN $@1 type $@2 typed_list  */
#line 650 "yacc/parser.yy"
                                {
                                vector<Type *> * ptrTypes = (vector<Type *> *) (yyvsp[-5].otype);
                                vector<Type *> * ptrParents = (vector<Type *> *) (yyvsp[-2].otype);
                                vector<Type *>::iterator i,e;
                                const Type * tmp;
                                e = ptrTypes->end();
                                for(i=ptrTypes->begin(); i != e; i++){
                                        if((tmp=parser_api->domain->addType((*i))) != *i){
                                        SearchLineInfo sli(tmp);
                                        if(sli.lineNumber){
                                        snprintf(parerr,256,"The type `%s' is already defined. (previous definition near %d [%s].",tmp->getName(),sli.lineNumber,sli.fileName.c_str());
                                        yywarning(parerr);
                                        delete (*i);
                                        (*i) = 0;
                                        }
                                        else {
                                        Type * n = parser_api->domain->getModificableType(tmp->getId());
                                        n->setFileId(parser_api->fileid);
                                        n->setLineNumber(lexer->getLineNumber());
                                        }
                                        }
                                        if(ptrParents) {
                                        Type * n = parser_api->domain->getModificableType((tmp)->getName());
                                        n->addSuperTypes(ptrParents);
                                        }
                                }
                                if(ptrParents)
                                        delete ptrParents;
                                delete ptrTypes;
                                }
#line 2810 "generated/parser.cpp"
    break;

  case 56: /* typed_list: error  */
#line 681 "yacc/parser.yy"
                                {(yyval.otype)=0;}
#line 2816 "generated/parser.cpp"
    break;

  case 58: /* constant_list: constant_def_list  */
#line 686 "yacc/parser.yy"
                                {delete (vector<ConstantSymbol *> *) (yyvsp[0].otype);}
#line 2822 "generated/parser.cpp"
    break;

  case 59: /* constant_list: constant_def_list PDDL_HYPHEN type constant_list  */
#line 689 "yacc/parser.yy"
                                {
                                vector<ConstantSymbol *> * ptr = (vector<ConstantSymbol *> *) (yyvsp[-3].otype);
                                vector<Type *> * types = (vector<Type *> *) (yyvsp[-1].otype);
                                if(types){
                                        // Definimos el tipo para cada una de las constantes
                                        for_each(ptr->begin(),ptr->end(),bind2nd(mem_fun1_t<void,Term,const vector<Type *> *>(&Term::addTypes),types));
                                        // Para cada tipo a�adimos referencias inversas a las constantes
                                        // Esto sirve para por ejemplo en un forall obtener todas las constantes
                                        // de un tipo dado.
                                        for_each(types->begin(),types->end(),bind2nd(mem_fun1_t<void,Type,const vector<ConstantSymbol *> *>(&Type::addRefsBy),ptr));
                                        delete types;
                                }
                                delete ptr;
                                }
#line 2841 "generated/parser.cpp"
    break;

  case 60: /* constant_def_list: PDDL_NAME  */
#line 706 "yacc/parser.yy"
                                { vector<ConstantSymbol *> * ptr = new vector<ConstantSymbol *>;
                                  ConstantSymbol * n = new ConstantSymbol((yyvsp[0].type_string));
                                  // comprobamos que la constante no se encuentre ya definida
                                  ConstantSymbol * f = parser_api->termtable->getConstantFromName(n->getName());
                                  if(f != 0){
                                    // Comprobar que los tipos sean iguales a la hora de generar un
                                    // error o bien un warning
                                    SearchLineInfo sli(f);
                                    snprintf(parerr,256,"Redefinition of the constant `%s'. (previous definition before or in line %d [%s]).",n->getName(),sli.lineNumber,sli.fileName.c_str());
                                    yywarning(parerr);
                                    delete n;
                                  }
                                  else{
                                      ptr->push_back(n);
                                      parser_api->termtable->addConstant(n);
                                      n->setFileId(parser_api->fileid);
                                      n->setLineNumber(lexer->getLineNumber());
                                  }
                                  (yyval.otype)=ptr;
                                }
#line 2866 "generated/parser.cpp"
    break;

  case 61: /* constant_def_list: constant_def_list PDDL_NAME  */
#line 727 "yacc/parser.yy"
                                { vector<ConstantSymbol *> * ptr = (vector<ConstantSymbol *> *) (yyvsp[-1].otype);
                                  ConstantSymbol * n = new ConstantSymbol((yyvsp[0].type_string));
                                  // comprobamos que la constante no se encuentre ya definida
                                  ConstantSymbol * f = parser_api->termtable->getConstantFromName(n->getName());
                                  if(f != 0){
                                      // Comprobar que los tipos sean iguales a la hora de generar un
                                      // error o bien un warning
                                      SearchLineInfo sli(f);
                                      snprintf(parerr,256,"Redefinition of the constant `%s'. (previous definition before or in line %d [%s]).",n->getName(),sli.lineNumber,sli.fileName.c_str());
                                      yywarning(parerr);
                                      delete n;
                                 }
                                 else{
                                        ptr->push_back(n);
                                        parser_api->termtable->addConstant(n);
                                        n->setFileId(parser_api->fileid);
                                        n->setLineNumber(lexer->getLineNumber());
                                }
                                  (yyval.otype)=ptr;
                                }
#line 2891 "generated/parser.cpp"
    break;

  case 62: /* type: LEFTPAR PDDL_EITHER type_ref_list RIGHTPAR  */
#line 751 "yacc/parser.yy"
                                {
                                (yyval.otype) = (yyvsp[-1].otype);
                                }
#line 2899 "generated/parser.cpp"
    break;

  case 63: /* type: type_ref  */
#line 755 "yacc/parser.yy"
                                { vector<Type *> * ptr = new vector<Type *> ;
                                if((yyvsp[0].otype))
                                ptr->push_back((Type *)(yyvsp[0].otype));
                                  (yyval.otype)=ptr;
                                }
#line 2909 "generated/parser.cpp"
    break;

  case 64: /* type: error  */
#line 761 "yacc/parser.yy"
                                { vector<Type *> * ptr = new vector<Type *> ;
                                  (yyval.otype)=ptr;
                                }
#line 2917 "generated/parser.cpp"
    break;

  case 65: /* type_def_list: PDDL_NAME  */
#line 767 "yacc/parser.yy"
                                { vector<Type *> * ptr = new vector<Type *>;
                                if(strcasecmp((yyvsp[0].type_string),"object")==0){
                                snprintf(parerr,256,"`object' is a built-in type and can't be redefined.");
                                yyerror(parerr);
                                }
                                else {
                                Type * t = new Type((yyvsp[0].type_string));
                                t->setFileId(parser_api->fileid);
                                t->setLineNumber(lexer->getLineNumber());
                                ptr->push_back(t);
                                }
                                  (yyval.otype)=ptr;
                                }
#line 2935 "generated/parser.cpp"
    break;

  case 66: /* type_def_list: type_def_list PDDL_NAME  */
#line 781 "yacc/parser.yy"
                                { vector<Type *> * ptr = (vector<Type *> *) (yyvsp[-1].otype);
                                if(strcasecmp((yyvsp[0].type_string),"object")==0){
                                snprintf(parerr,256,"`object' is a built-in type and can't be redefined.");
                                yyerror(parerr);
                                }
                                else {
                                Type * t = new Type((yyvsp[0].type_string));
                                t->setFileId(parser_api->fileid);
                                t->setLineNumber(lexer->getLineNumber());
                                ptr->push_back(t);
                                }
                                  (yyval.otype)=ptr;
                                }
#line 2953 "generated/parser.cpp"
    break;

  case 67: /* type_ref: term_name  */
#line 798 "yacc/parser.yy"
                                {
                                // buscamos la referencia al tipo en el dominio
                                string * s = (string *) (yyvsp[0].otype);
                                if(strcasecmp(s->c_str(),"object") == 0) {
                                delete s;
                                (yyval.otype) = 0;
                                }
                                else {
                                Type * t = parser_api->domain->getModificableType(s->c_str());
                                const Type * nt;
                                if(!t){
                                        // cuando ocurre esto el tipo se crea de todas las maneras
                                        // pero posiblemente se trate de un error que deber�n gestionar
                                        // las reglas padre. Observar que en caso de que se cree como
                                        // nuevo el tipo no tendr� ni fichero ni l�nea asociados.
                                        nt = parser_api->domain->addType(s->c_str());
                                        t = parser_api->domain->getModificableType(nt->getId());
                                        if(errtypes){
                                                snprintf(parerr,256,"Undeclared type `%s'.",s->c_str());
                                                yyerror(parerr);
                                        }
                                }
                                delete s;
                                    (yyval.otype)=t;
                                }
                                }
#line 2984 "generated/parser.cpp"
    break;

  case 68: /* type_ref_list: type_ref  */
#line 827 "yacc/parser.yy"
                                { vector<const Type *> * ptr = new vector<const Type *> ;
                                if((yyvsp[0].otype))
                                    ptr->push_back((const Type *)(yyvsp[0].otype));
                                  (yyval.otype)=ptr;
                                }
#line 2994 "generated/parser.cpp"
    break;

  case 69: /* type_ref_list: type_ref_list type_ref  */
#line 833 "yacc/parser.yy"
                                { vector<const Type *> * ptr = (vector<const Type *> *) (yyvsp[-1].otype);
                                  if((yyvsp[0].otype))
                                ptr->push_back((const Type *)(yyvsp[0].otype));
                                  (yyval.otype)=ptr;
                                }
#line 3004 "generated/parser.cpp"
    break;

  case 73: /* $@3: %empty  */
#line 848 "yacc/parser.yy"
                                {
                                  string * nameLit = (string *) (yyvsp[0].otype);
                                  LiteralEffect * lit=0;
                                  Meta * mt=0;
                                  // buscamos si el literal ya est� definido en el diccionario de
                                  // nombres de literales
                                  ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),(const char *) nameLit->c_str());
                                  if(posit != (parser_api->domain->ldictionary).end()) {
                                      lit = new LiteralEffect(posit->second,parser_api->domain->metainfo.size());
                                      mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                      parser_api->domain->metainfo.push_back(mt);
                                  }
                                  else {
                                      lit = new LiteralEffect(idCounter++,parser_api->domain->metainfo.size());
                                      mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                      parser_api->domain->metainfo.push_back(mt);
                                      (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                  }
                                  container = lit;
                                  delete nameLit;
                                }
#line 3030 "generated/parser.cpp"
    break;

  case 74: /* atomic_formula_skeleton: LEFTPAR term_name $@3 variable_typed_list RIGHTPAR  */
#line 870 "yacc/parser.yy"
                                {
                                  LiteralEffect * lit= (LiteralEffect *) container;
                                  container = 0;
                                  delete context;
                                  context=0;
                                  // buscar predicados duplicados
                                  int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                  bool duplicated=false;
                                  literaltablecit ite;
                                  for(ite = r.first; ite != r.second && !duplicated; ite++) {
                                      if(lit->sizep() == (*ite).second->sizep()) {
                                              // tenemos dos definiciones de predicado con el mismo nombre
                                              // y n�mero de argumentos ��No se como distinguirlos!!
                                              duplicated = true;
                                      }
                                  }

                                  if(!duplicated) {
                                      parser_api->domain->addLiteral(lit);
                                  }
                                  else {
                                      SearchLineInfo sli(lit->getMetaId());
                                      snprintf(parerr,256,"Conflicting predicate definition `%s' previous definition %d [%s].",lit->getName(),sli.lineNumber,sli.fileName.c_str());
                                      yyerror(parerr);
                                      delete lit;
                                  }
                                }
#line 3063 "generated/parser.cpp"
    break;

  case 76: /* $@4: %empty  */
#line 902 "yacc/parser.yy"
                                {
                                  string * nameLit = (string *) (yyvsp[0].otype);
                                  Axiom * lit=0;
                                  Meta * mt=0;
                                  // buscamos si el literal ya est� definido en el diccionario de
                                  // nombres de literales
                                  ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),(const char *) nameLit->c_str());
                                  if(posit != (parser_api->domain->ldictionary).end()) {
                                      lit = new Axiom(posit->second,parser_api->domain->metainfo.size());
                                      mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                      parser_api->domain->metainfo.push_back(mt);
                                  }
                                  else {
                                      lit = new Axiom(idCounter++,parser_api->domain->metainfo.size());
                                      mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                      parser_api->domain->metainfo.push_back(mt);
                                      (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                  }
                                  container = lit;
                                  delete nameLit;
                                }
#line 3089 "generated/parser.cpp"
    break;

  case 77: /* derived_formula_skeleton: LEFTPAR term_name $@4 variable_typed_list RIGHTPAR  */
#line 924 "yacc/parser.yy"
                                {
                                  Axiom * lit= (Axiom *) container;
                                  container = 0;
                                  // comprobaciones de correctitud
                                  // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                  int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                  bool unificacion=false;
                                  vector<Literal *> candidates;
                                  vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++) {
                                      candidates.push_back((*i).second);
                                      Unifier u;
                                      if(unify3(lit->getParameters(),(*i).second->getParameters(),&u)){
                                          u.applyTypeSubstitutions(0);
                                          unificacion=true;
                                       }
                                  }
                                  if(!unificacion){
                                          snprintf(parerr,256,"(1) No matching predicate for `%s'.",lit->toString());
                                          yyerror(parerr);
                                          if(candidates.size() > 0) {
                                          *errflow << "Possible candidates:" << endl;
                                            for(j=candidates.begin();j!=candidates.end();j++) {
                                          SearchLineInfo sli((*j)->getMetaId());
                                               *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                          (*j)->printL(errflow,1);
                                          *errflow << endl;
                                            }
                                          }
                                  }
                                  parser_api->domain->addAxiom(lit);
                                  (yyval.otype) = lit;
                                }
#line 3130 "generated/parser.cpp"
    break;

  case 78: /* derived_formula_skeleton: error  */
#line 961 "yacc/parser.yy"
                                {
                                  (yyval.otype) =0;
                                }
#line 3138 "generated/parser.cpp"
    break;

  case 79: /* $@5: %empty  */
#line 967 "yacc/parser.yy"
                                {contador = 0;}
#line 3144 "generated/parser.cpp"
    break;

  case 82: /* var_typel: var_typel variable  */
#line 972 "yacc/parser.yy"
                                {
                                  // si tenemos un contenedor donde meter la variable
                                  // la a�adimos
                                  if(!container)
                                      *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                  if(container){
                                      if(container->searchTermId((yyvsp[0].termtype)->first) != container->parametersEnd()){
                                          // es raro que se tenga una variable repetida
                                          snprintf(parerr,256,"Duplicated variable: `%s'.",parser_api->termtable->getVariable(*(yyvsp[0].termtype))->getName());
                                          yywarning(parerr);
                                      }
                                      container->addParameter(*(yyvsp[0].termtype));
                                  }
                                }
#line 3163 "generated/parser.cpp"
    break;

  case 83: /* var_typel: var_typel PDDL_HYPHEN type  */
#line 987 "yacc/parser.yy"
                                {
                                  if(!container)
                                      *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                  if(container && (yyvsp[0].otype)) {
                                      // recorremos hacia atr�s todas las variables insertadas anteriormente,
                                      // hasta encontrar la primera que no tiene tipo asignado.
                                      // A partir de este asignamos type
                                      vector<Type *> * vt = (vector<Type *> *)(yyvsp[0].otype);
                                      if(!vt->empty()) {
                                          TestTypeTree()(vt);
                                          KeyList * kl = container->getModificableParameters();
                                          KeyList::iterator i,e;
                                          e = kl->end();
                                          for(i=kl->begin() + contador;i!=e;i++) {
                                                  parser_api->termtable->getVariable(*i)->addTypes2(vt);
                                          }
                                      }
                                      delete vt;
                                      contador = container->getModificableParameters()->size();
                                  }
                                  else if(!(yyvsp[0].otype)) {
                                      snprintf(parerr,256,"Type expected after `-'.");
                                      yywarning(parerr);
                                  }
                                }
#line 3193 "generated/parser.cpp"
    break;

  case 84: /* functions_def: LEFTPAR PDDL_FUNCTIONS function_typed_list RIGHTPAR  */
#line 1015 "yacc/parser.yy"
                                {
                                    if(!parser_api->domain->errfluents && !parser_api->domain->hasRequirement(":fluents"))
                                    {
                                        parser_api->domain->errfluents = true;
                                        yyerror("Using a clause that requires `:fluents' and is not declared in requirements clause");
                                    }
                                }
#line 3205 "generated/parser.cpp"
    break;

  case 87: /* $@6: %empty  */
#line 1030 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                PyDefFunction * lit=0;
                                Meta * mt=0;
                                // buscamos si el literal ya est� definido en el diccionario de
                                // nombres de literales
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),(const char *) nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                lit = new PyDefFunction(posit->second,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new PyDefFunction(idCounter++,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                context = new LDictionary;
                                }
#line 3233 "generated/parser.cpp"
    break;

  case 88: /* function_def: LEFTPAR term_name $@6 variable_typed_list RIGHTPAR opt_type code  */
#line 1054 "yacc/parser.yy"
                                {
                                PyDefFunction * lit= (PyDefFunction *) container;
                                container = 0;
                                delete context;
                                context=0;
                                // buscar predicados duplicados
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool duplicated=false;
                                literaltablecit ite;
                                for(ite = r.first; ite != r.second && !duplicated; ite++)
                                {
                                if(lit->sizep() == (*ite).second->sizep())
                                        // tenemos dos definiciones de predicado con el mismo nombre
                                        // y n�mero de argumentos ��No se como distinguirlos!!
                                        duplicated = true;
                                }

                                if(!duplicated){
                                parser_api->domain->addLiteral(lit);
                                }
                                else {
                                SearchLineInfo sli(lit->getMetaId());
                                snprintf(parerr,256,"Conflicting function definition `%s' previous definition %d [%s].",lit->getName(),sli.lineNumber,sli.fileName.c_str());
                                yyerror(parerr);
                                delete lit;
                                }
                                if((yyvsp[0].type_string)){
                                if(!lit->setCode((yyvsp[0].type_string))){
                                snprintf(parerr,256,"Error in Python script code. Function: %s.",lit->getName());
                                yyerror(parerr);
                                }
                                }
                                vector<Type *> * types = (vector<Type *> *) (yyvsp[-1].otype);
                                if(types){
                                        // en pddl estandard se supone que el tipo es un n�mero
                                        // pero lo dejamos abierto para la extensi�n. De momento
                                        // se ignora el tipo en las funciones.
                                        lit->addTypes(types);
                                        delete types;
                                }
                                }
#line 3280 "generated/parser.cpp"
    break;

  case 89: /* opt_type: %empty  */
#line 1099 "yacc/parser.yy"
                                {
                                Type * number = parser_api->domain->getModificableType("number");
                                vector<Type *> * vt = new vector<Type *>;
                                vt->push_back(number);
                                (yyval.otype)=vt;
                                }
#line 3291 "generated/parser.cpp"
    break;

  case 90: /* opt_type: PDDL_HYPHEN type  */
#line 1106 "yacc/parser.yy"
                                {(yyval.otype)=(yyvsp[0].otype);}
#line 3297 "generated/parser.cpp"
    break;

  case 91: /* code: %empty  */
#line 1110 "yacc/parser.yy"
                                {(yyval.type_string) = 0;}
#line 3303 "generated/parser.cpp"
    break;

  case 92: /* code: PYTHON_CODE  */
#line 1112 "yacc/parser.yy"
                                {
                                    static string code = "";
                                code = (yyvsp[0].type_string);
                                    if(PYTHON_FLAG) {
                                        (yyval.type_string) = code.c_str();
                                    }
                                    else {
                                        yyerror("Parser compiled without Python support. Install python and recompile.");
                                        (yyval.type_string) = 0;
                                    }
                                 }
#line 3319 "generated/parser.cpp"
    break;

  case 97: /* structure_def: derived_def  */
#line 1132 "yacc/parser.yy"
                                {
                                  if(!parser_api->domain->errder && !parser_api->domain->hasRequirement(":derived-predicates"))
                                  {
                                        parser_api->domain->errhtn = true;
                                        yyerror("Using a clause that requires `:derived-predicates' and is not declared in requirements clause");
                                  }
                                }
#line 3331 "generated/parser.cpp"
    break;

  case 100: /* @7: %empty  */
#line 1145 "yacc/parser.yy"
                                {
                                context = new LDictionary;
                                string * name = (string *) (yyvsp[0].otype);
                                PrimitiveTask * priTask=0;
                                Meta * mt = 0;
                                // buscamos en el diccionario si la acci�n ya tiene un identificador
                                // asociado, en cuyo caso lo reutilizamos
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),name->c_str());
                                      if(posit != (parser_api->domain->ldictionary).end()) {
                                        priTask = new PrimitiveTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                      else
                                      {
                                        priTask = new PrimitiveTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(priTask->getName(),priTask->getId()));
                                      }
                                container = priTask;
                                delete name;
                                (yyval.otype) = priTask;
                                }
#line 3360 "generated/parser.cpp"
    break;

  case 101: /* $@8: %empty  */
#line 1171 "yacc/parser.yy"
                                {
                                        // si hay alg�n tag
                                        if((yyvsp[0].otype)){
                                        TagVector * tv = (TagVector *) (yyvsp[0].otype);
                                        tagv_ite tb, te = tv->end();
                                        int mid = ((PrimitiveTask *) container)->getMetaId();
                                        for(tb = tv->begin();tb!=te;tb++){
                                        parser_api->domain->metainfo[mid]->addTag(*tb);
                                        }
                                        tv->clear();
                                        delete tv;
                                        }
                                        container = 0;
                                }
#line 3379 "generated/parser.cpp"
    break;

  case 102: /* action_def: LEFTPAR PDDL_ACTION term_name @7 PDDL_PARAMETERS LEFTPAR variable_typed_list RIGHTPAR meta_list $@8 preconditions_def effect_def RIGHTPAR  */
#line 1188 "yacc/parser.yy"
                                {
                                PrimitiveTask * priTask= (PrimitiveTask *) (yyvsp[-9].otype);
                                priTask->setPrecondition((Goal *) (yyvsp[-2].otype));
                                priTask->setEffect((Effect *) (yyvsp[-1].otype));
                                parser_api->domain->addTask(priTask);
                                delete context;
                                context = 0;
                                }
#line 3392 "generated/parser.cpp"
    break;

  case 103: /* $@9: %empty  */
#line 1200 "yacc/parser.yy"
                                {
                                context = new LDictionary;
                                string * name = (string *) (yyvsp[0].otype);
                                CompoundTask * compTask=0;
                                Meta * mt=0;
                                // buscamos en el diccionario si la acci�n ya tiene un identificador
                                // asociado, en cuyo caso lo reutilizamos
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),name->c_str());
                                      if(posit != (parser_api->domain->ldictionary).end()) {
                                        compTask = new CompoundTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                      else
                                      {
                                        compTask = new CompoundTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(compTask->getName(),compTask->getId()));
                                      }
                                container = compTask;
                                delete name;
                                cbuilding = compTask;
                                }
#line 3421 "generated/parser.cpp"
    break;

  case 104: /* htn_task_def: LEFTPAR HTN_TASK term_name $@9 PDDL_PARAMETERS LEFTPAR variable_typed_list RIGHTPAR meta_list methods_def_body RIGHTPAR  */
#line 1228 "yacc/parser.yy"
                                {
                                if((yyvsp[-2].otype)){
                                        TagVector * tv = (TagVector *) (yyvsp[-2].otype);
                                        tagv_ite tb, te = tv->end();
                                        int mid = ((CompoundTask *) container)->getMetaId();
                                        for(tb = tv->begin();tb!=te;tb++)
                                        parser_api->domain->metainfo[mid]->addTag(*tb);
                                        tv->clear();
                                        delete tv;
                                }
                                if(!parser_api->domain->errhtn && !parser_api->domain->hasRequirement(":htn-expansion"))
                                {
                                        parser_api->domain->errhtn = true;
                                        yyerror("Using a clause that requires `:htn-expansion' and is not declared in requirements clause");
                                }
                                CompoundTask * compTask= cbuilding;
                                parser_api->domain->addTask(compTask);
                                delete context;
                                context = 0;
                                cbuilding=0;
                                }
#line 3447 "generated/parser.cpp"
    break;

  case 105: /* duration_constraints: simple_duration_constraint  */
#line 1253 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = new vector<TCTR>;
                                TCTR * ele = (TCTR *) (yyvsp[0].otype);
                                v->push_back(*ele);
                                (yyval.otype)= v;
                                }
#line 3458 "generated/parser.cpp"
    break;

  case 106: /* duration_constraints: LEFTPAR PDDL_AND sduration_constraint_list RIGHTPAR  */
#line 1260 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = (vector<TCTR> *) (yyvsp[-1].otype);
                                (yyval.otype)= v;
                                }
#line 3467 "generated/parser.cpp"
    break;

  case 107: /* duration_constraints: LEFTPAR RIGHTPAR  */
#line 1265 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = new vector<TCTR>;
                                (yyval.otype)= v;
                                }
#line 3476 "generated/parser.cpp"
    break;

  case 108: /* sdur_constraint: LEFTPAR EQUAL PDDL_DURATIONVAR fluent_exp RIGHTPAR  */
#line 1272 "yacc/parser.yy"
                                {
                                    static TCTR p;
                                    p = make_pair(EQ_DUR,(Evaluable *)(yyvsp[-1].otype));
                                    (yyval.otype) = &p;
                                }
#line 3486 "generated/parser.cpp"
    break;

  case 109: /* sdur_constraint: LEFTPAR LESS_EQUAL PDDL_DURATIONVAR fluent_exp RIGHTPAR  */
#line 1278 "yacc/parser.yy"
                                {
                                    static TCTR p;
                                    p = make_pair(LEQ_DUR,(Evaluable *)(yyvsp[-1].otype));
                                    (yyval.otype) = &p;
                                }
#line 3496 "generated/parser.cpp"
    break;

  case 110: /* sdur_constraint: LEFTPAR GREATHER_EQUAL PDDL_DURATIONVAR fluent_exp RIGHTPAR  */
#line 1284 "yacc/parser.yy"
                                {
                                    static TCTR p;
                                    p = make_pair(GEQ_DUR,(Evaluable *)(yyvsp[-1].otype));
                                    (yyval.otype) = &p;
                                }
#line 3506 "generated/parser.cpp"
    break;

  case 111: /* sdur_constraint: LEFTPAR LESS PDDL_DURATIONVAR fluent_exp RIGHTPAR  */
#line 1290 "yacc/parser.yy"
                                {
                                    static TCTR p;
                                    p = make_pair(LESS_DUR,(Evaluable *)(yyvsp[-1].otype));
                                    (yyval.otype) = &p;
                                }
#line 3516 "generated/parser.cpp"
    break;

  case 112: /* sdur_constraint: LEFTPAR GREATHER PDDL_DURATIONVAR fluent_exp RIGHTPAR  */
#line 1296 "yacc/parser.yy"
                                {
                                    static TCTR p;
                                    p = make_pair(GRE_DUR,(Evaluable *)(yyvsp[-1].otype));
                                    (yyval.otype) = &p;
                                }
#line 3526 "generated/parser.cpp"
    break;

  case 113: /* simple_duration_constraint: sdur_constraint  */
#line 1303 "yacc/parser.yy"
                                {
                                    (yyval.otype) = (yyvsp[0].otype);
                                }
#line 3534 "generated/parser.cpp"
    break;

  case 114: /* simple_duration_constraint: LEFTPAR EQUAL STARTVAR fluent_exp RIGHTPAR  */
#line 1307 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(EQ_START,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3544 "generated/parser.cpp"
    break;

  case 115: /* simple_duration_constraint: LEFTPAR LESS_EQUAL STARTVAR fluent_exp RIGHTPAR  */
#line 1313 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(LEQ_START,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3554 "generated/parser.cpp"
    break;

  case 116: /* simple_duration_constraint: LEFTPAR GREATHER_EQUAL STARTVAR fluent_exp RIGHTPAR  */
#line 1319 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(GEQ_START,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3564 "generated/parser.cpp"
    break;

  case 117: /* simple_duration_constraint: LEFTPAR LESS STARTVAR fluent_exp RIGHTPAR  */
#line 1325 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(LESS_START,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3574 "generated/parser.cpp"
    break;

  case 118: /* simple_duration_constraint: LEFTPAR GREATHER STARTVAR fluent_exp RIGHTPAR  */
#line 1331 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(GRE_START,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3584 "generated/parser.cpp"
    break;

  case 119: /* simple_duration_constraint: LEFTPAR EQUAL ENDVAR fluent_exp RIGHTPAR  */
#line 1337 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(EQ_END,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3594 "generated/parser.cpp"
    break;

  case 120: /* simple_duration_constraint: LEFTPAR LESS_EQUAL ENDVAR fluent_exp RIGHTPAR  */
#line 1343 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(LEQ_END,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3604 "generated/parser.cpp"
    break;

  case 121: /* simple_duration_constraint: LEFTPAR GREATHER_EQUAL ENDVAR fluent_exp RIGHTPAR  */
#line 1349 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(GEQ_END,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3614 "generated/parser.cpp"
    break;

  case 122: /* simple_duration_constraint: LEFTPAR LESS ENDVAR fluent_exp RIGHTPAR  */
#line 1355 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(LESS_END,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3624 "generated/parser.cpp"
    break;

  case 123: /* simple_duration_constraint: LEFTPAR GREATHER ENDVAR fluent_exp RIGHTPAR  */
#line 1361 "yacc/parser.yy"
                                {
                                static TCTR p;
                                p = make_pair(GRE_END,(Evaluable *)(yyvsp[-1].otype));
                                (yyval.otype) = &p;
                                }
#line 3634 "generated/parser.cpp"
    break;

  case 124: /* sduration_constraint_list: simple_duration_constraint  */
#line 1369 "yacc/parser.yy"
                                {
                                vector<pair<int,Evaluable *> > * v = new vector<pair<int,Evaluable *> >;
                                v->push_back(*((pair<int,Evaluable *> *) (yyvsp[0].otype)));
                                (yyval.otype)= v;
                                }
#line 3644 "generated/parser.cpp"
    break;

  case 125: /* sduration_constraint_list: sduration_constraint_list simple_duration_constraint  */
#line 1375 "yacc/parser.yy"
                                {
                                vector<pair<int,Evaluable *> > * v = (vector<pair<int,Evaluable *> > *) (yyvsp[-1].otype);
                                v->push_back(*((pair<int,Evaluable *> *) (yyvsp[0].otype)));
                                (yyval.otype)= v;
                                }
#line 3654 "generated/parser.cpp"
    break;

  case 127: /* methods_def_body: LEFTPAR EXCLAMATION method_list RIGHTPAR  */
#line 1384 "yacc/parser.yy"
                                {
                                cbuilding->setFirst();
                                }
#line 3662 "generated/parser.cpp"
    break;

  case 128: /* methods_def_body: LEFTPAR RANDOM EXCLAMATION method_list RIGHTPAR  */
#line 1388 "yacc/parser.yy"
                                {
                                cbuilding->setFirst();
                                cbuilding->setRandom();
                                }
#line 3671 "generated/parser.cpp"
    break;

  case 129: /* methods_def_body: LEFTPAR EXCLAMATION RANDOM method_list RIGHTPAR  */
#line 1393 "yacc/parser.yy"
                                {
                                cbuilding->setFirst();
                                cbuilding->setRandom();
                                }
#line 3680 "generated/parser.cpp"
    break;

  case 130: /* methods_def_body: LEFTPAR RANDOM method_list RIGHTPAR  */
#line 1398 "yacc/parser.yy"
                                {
                                cbuilding->setRandom();
                                }
#line 3688 "generated/parser.cpp"
    break;

  case 133: /* $@10: %empty  */
#line 1410 "yacc/parser.yy"
                                {container=cbuilding;}
#line 3694 "generated/parser.cpp"
    break;

  case 134: /* $@11: %empty  */
#line 1412 "yacc/parser.yy"
                                {container=0;}
#line 3700 "generated/parser.cpp"
    break;

  case 135: /* @12: %empty  */
#line 1413 "yacc/parser.yy"
                                {
                                string * name = (string *) (yyvsp[-3].otype);
                                // comprobar que el m�todo no se haya definido con anterioridad
                                methodcit i,e = cbuilding->getEndMethod();
                                bool definido=false;
                                for(i=cbuilding->getBeginMethod();i!=e && !definido;i++)
                                        if(!strcasecmp((*i)->getName(),name->c_str())){
                                        definido = true;
                                        break;
                                        }
                                if(definido){
                                        SearchLineInfo sli((*i)->getMetaId());
                                        snprintf(parerr,256,"The method `%s' is already defined for this task in or before %d [%s].",(*i)->getName(),sli.lineNumber,sli.fileName.c_str());
                                        yywarning(parerr);
                                }
                                Method * method=0;
                                      method = new Method(parser_api->domain->metainfo.size(),cbuilding);
                                Meta * mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                if((yyvsp[-1].otype)){
                                        TagVector * tv = (TagVector *) (yyvsp[-1].otype);
                                        tagv_ite tb, te = tv->end();
                                        int mid = method->getMetaId();
                                        for(tb = tv->begin();tb!=te;tb++)
                                        parser_api->domain->metainfo[mid]->addTag(*tb);
                                        tv->clear();
                                        delete tv;
                                }
                                delete name;

                                // forzamos a que cada m�todo tenga su propio contexto
                                oldContext = context;
                                context = new LDictionary();
                                // A�adimos al contexto las variables que tengo
                                keylistcit j, k = method->parametersEnd();
                                for(j=method->parametersBegin();j!=k;j++)
                                        context->insert(make_pair(parser_api->termtable->getVariable((*j))->getName(),(*j).first));
                                (yyval.otype) = method;
                                }
#line 3744 "generated/parser.cpp"
    break;

  case 136: /* method_body: LEFTPAR HTN_METHOD term_name $@10 meta_list $@11 @12 preconditions_def HTN_TASKS task_network RIGHTPAR  */
#line 1455 "yacc/parser.yy"
                                {
                                Method * method = (Method *) (yyvsp[-4].otype);
                                method->setPrecondition((Goal *) (yyvsp[-3].otype));
                                method->setTaskNetwork((TaskNetwork *) (yyvsp[-1].otype));
                                cbuilding->addMethod(method);
                                delete context;
                                context = oldContext;
                                oldContext = 0;
                                }
#line 3758 "generated/parser.cpp"
    break;

  case 137: /* meta_list: %empty  */
#line 1467 "yacc/parser.yy"
                                {
                                (yyval.otype) = 0;
                                }
#line 3766 "generated/parser.cpp"
    break;

  case 138: /* meta_list: META LEFTPAR tag_list RIGHTPAR  */
#line 1472 "yacc/parser.yy"
                                {
                                (yyval.otype) = (yyvsp[-1].otype);
                                }
#line 3774 "generated/parser.cpp"
    break;

  case 139: /* tag_list: %empty  */
#line 1478 "yacc/parser.yy"
                                {
                                (yyval.otype) = new TagVector();
                                }
#line 3782 "generated/parser.cpp"
    break;

  case 140: /* tag_list: tag_list tag_element  */
#line 1482 "yacc/parser.yy"
                                {
                                TagVector * tv = (TagVector *) (yyvsp[-1].otype);
                                tv->push_back((Tag *)(yyvsp[0].otype));
                                (yyval.otype) = tv;
                                }
#line 3792 "generated/parser.cpp"
    break;

  case 141: /* @13: %empty  */
#line 1490 "yacc/parser.yy"
                                {
                                const char * name = (const char *) (yyvsp[0].type_string);
                                TextTag * mt = new TextTag(name);
                                (yyval.otype) = mt;
                                }
#line 3802 "generated/parser.cpp"
    break;

  case 142: /* tag_element: LEFTPAR TAG PDDL_NAME @13 HTN_TEXT RIGHTPAR  */
#line 1496 "yacc/parser.yy"
                                {
                                TextTag * mt = (TextTag *) (yyvsp[-2].otype);
                                    string text = (const char *) (yyvsp[-1].type_string);

                                // Fijar el valor
                                if(container){
                                        string value = processTextTag(text, container);
                                        mt->setValue(value.c_str());
                                }
                                else{
                                        mt->setValue(text.c_str());
                                }

                                    (yyval.otype) = mt;
                                    if(!parser_api->domain->errmetatags && !parser_api->domain->hasRequirement(":metatags"))
                                    {
                                        parser_api->domain->errmetatags = true;
                                        yyerror("Using a clause that requires `:metatags' and is not declared in requirements clause");
                                    }
                                }
#line 3827 "generated/parser.cpp"
    break;

  case 143: /* task_def: atomic_task_formula  */
#line 1519 "yacc/parser.yy"
                                {(yyval.otype)=(yyvsp[0].otype);}
#line 3833 "generated/parser.cpp"
    break;

  case 144: /* task_def: LEFTPAR HTN_ACHIEVE goal_def RIGHTPAR  */
#line 1521 "yacc/parser.yy"
                                {(yyval.otype)=0; *errflow << "No implementado achieve" << endl;}
#line 3839 "generated/parser.cpp"
    break;

  case 145: /* task_def: inlinetask  */
#line 1523 "yacc/parser.yy"
                                {(yyval.otype) =(yyvsp[0].otype);}
#line 3845 "generated/parser.cpp"
    break;

  case 146: /* @14: %empty  */
#line 1527 "yacc/parser.yy"
                                {
                                PrimitiveTask * priTask=0;
                                Meta * mt = 0;
                                // buscamos en el diccionario si la acci�n ya tiene un identificador
                                // asociado, en cuyo caso lo reutilizamos
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),":inline");
                                      if(posit != (parser_api->domain->ldictionary).end()) {
                                        priTask = new PrimitiveTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(":inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                      else
                                      {
                                        priTask = new PrimitiveTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(":inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(priTask->getName(),priTask->getId()));
                                      }
                                priTask->setInline();
                                (yyval.otype) = priTask;
                                }
#line 3871 "generated/parser.cpp"
    break;

  case 147: /* inlinetask: LEFTPAR HTN_INLINE @14 goal_def effect RIGHTPAR  */
#line 1549 "yacc/parser.yy"
                                {
                                        PrimitiveTask * priTask= (PrimitiveTask *) (yyvsp[-3].otype);
                                        priTask->setPrecondition((Goal *) (yyvsp[-2].otype));
                                        priTask->setEffect((Effect *) (yyvsp[-1].otype));
                                        (yyval.otype) = priTask;
                                }
#line 3882 "generated/parser.cpp"
    break;

  case 148: /* @15: %empty  */
#line 1556 "yacc/parser.yy"
                                {
                                PrimitiveTask * priTask=0;
                                Meta * mt = 0;
                                // buscamos en el diccionario si la acci�n ya tiene un identificador
                                // asociado, en cuyo caso lo reutilizamos
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),":!inline");
                                      if(posit != (parser_api->domain->ldictionary).end()) {
                                        priTask = new PrimitiveTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(":!inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                      else
                                      {
                                        priTask = new PrimitiveTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(":!inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(priTask->getName(),priTask->getId()));
                                      }
                                priTask->setInline(2);
                                (yyval.otype) = priTask;
                                }
#line 3908 "generated/parser.cpp"
    break;

  case 149: /* inlinetask: LEFTPAR HTN_INLINECUT @15 goal_def effect RIGHTPAR  */
#line 1578 "yacc/parser.yy"
                                {
                                        PrimitiveTask * priTask= (PrimitiveTask *) (yyvsp[-3].otype);
                                        priTask->setPrecondition((Goal *) (yyvsp[-2].otype));
                                        priTask->setEffect((Effect *) (yyvsp[-1].otype));
                                        (yyval.otype) = priTask;
                                }
#line 3919 "generated/parser.cpp"
    break;

  case 150: /* $@16: %empty  */
#line 1587 "yacc/parser.yy"
                                {
                                string * name = (string *) (yyvsp[0].otype);
                                TaskHeader * th=0;
                                MetaTH * mt = 0;
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),name->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                th = new TaskHeader(posit->second,parser_api->domain->metainfo.size());
                                mt = new MetaTH(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back((Meta *)mt);
                                }
                                else
                                {
                                th = new TaskHeader(idCounter++,parser_api->domain->metainfo.size());
                                mt = new MetaTH(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back((Meta *)mt);
                                (parser_api->domain->ldictionary).insert(make_pair(th->getName(), th->getId()));
                                }
                                container = th;
                                delete name;
                                contador=0;
                                }
#line 3945 "generated/parser.cpp"
    break;

  case 151: /* atomic_task_formula: LEFTPAR term_name $@16 term_list RIGHTPAR  */
#line 1609 "yacc/parser.yy"
                                {
                                // se deja para una comprobaci�n posterior el ver
                                // si el th se corresponde con alguna tarea del dominio
                                TaskHeader * th= (TaskHeader *) container;
                                container = 0;
                                (yyval.otype) = th;
                                }
#line 3957 "generated/parser.cpp"
    break;

  case 152: /* task_network: task_element  */
#line 1619 "yacc/parser.yy"
                                {
                                (yyval.otype) = (yyvsp[0].otype);
                                }
#line 3965 "generated/parser.cpp"
    break;

  case 153: /* task_network: LEFTPAR RIGHTPAR  */
#line 1623 "yacc/parser.yy"
                                {
                                // esto es una noop
                                Meta * mt = 0;
                                PrimitiveTask * priTask;
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),":!inline");
                                    if(posit != (parser_api->domain->ldictionary).end()) {
                                        priTask = new PrimitiveTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(":inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                    else
                                    {
                                        priTask = new PrimitiveTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(":inline",lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(priTask->getName(),priTask->getId()));
                                    }
                                priTask->setInline();
                                TaskNetwork * tn = new TaskNetwork(priTask);
                                (yyval.otype) = tn;
                                }
#line 3991 "generated/parser.cpp"
    break;

  case 154: /* task_list: task_list task_element  */
#line 1648 "yacc/parser.yy"
                                {
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);
                                vt->push_back((TaskNetwork *) (yyvsp[0].otype));
                                (yyval.otype) = vt;
                                }
#line 4001 "generated/parser.cpp"
    break;

  case 155: /* task_list: task_element  */
#line 1654 "yacc/parser.yy"
                                {
                                vector<TaskNetwork *> * vt = new vector<TaskNetwork *>;
                                vt->push_back((TaskNetwork *) (yyvsp[0].otype));
                                (yyval.otype) = vt;
                                }
#line 4011 "generated/parser.cpp"
    break;

  case 156: /* task_element: task_def  */
#line 1662 "yacc/parser.yy"
                                {
                                (yyval.otype) = new TaskNetwork((Task *) (yyvsp[0].otype));
                                }
#line 4019 "generated/parser.cpp"
    break;

  case 157: /* task_element: EXCLAMATION task_def  */
#line 1666 "yacc/parser.yy"
                                {
                                TaskNetwork * tn = new TaskNetwork((Task *) (yyvsp[0].otype));
                                tn->setInmediate(0,true);
                                (yyval.otype) = tn;
                                }
#line 4029 "generated/parser.cpp"
    break;

  case 158: /* task_element: LESS duration_constraints task_list GREATHER  */
#line 1672 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = (vector<TCTR> *) (yyvsp[-2].otype);
                                vector<TCTR>::iterator iv, ev = v->end();
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->merge(*i);
                                        delete (*i);
                                }
                                delete vt;

                                if(v){
                                        for(iv = v->begin();iv!=ev;iv++){
                                        tn->addTConstraint((*iv));
                                        }
                                        delete v;
                                }

                                intvit j, je = tn->getSuccEnd(0);
                                for(j=tn->getSuccBegin(0);j!=je;j++)
                                        tn->setBTTask((*j)-1);
                                (yyval.otype) = tn;
                                }
#line 4059 "generated/parser.cpp"
    break;

  case 159: /* task_element: LESS task_list GREATHER  */
#line 1698 "yacc/parser.yy"
                                {
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->merge(*i);
                                        delete (*i);
                                }
                                delete vt;
                                intvit j, je = tn->getSuccEnd(0);
                                for(j=tn->getSuccBegin(0);j!=je;j++)
                                        tn->setBTTask((*j)-1);
                                (yyval.otype) = tn;
                                }
#line 4079 "generated/parser.cpp"
    break;

  case 160: /* task_element: LEFTPAR duration_constraints task_list RIGHTPAR  */
#line 1714 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = (vector<TCTR> *) (yyvsp[-2].otype);
                                vector<TCTR>::iterator iv, ev = v->end();
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->join(*i);
                                        delete (*i);
                                }
                                delete vt;

                                if(v){
                                        for(iv = v->begin();iv!=ev;iv++){
                                        tn->addTConstraint((*iv));
                                        }
                                        delete v;
                                }

                                (yyval.otype) = tn;
                                }
#line 4106 "generated/parser.cpp"
    break;

  case 161: /* task_element: LEFTPAR task_list RIGHTPAR  */
#line 1737 "yacc/parser.yy"
                                {
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->join(*i);
                                        delete (*i);
                                }
                                delete vt;
                                (yyval.otype) = tn;
                                }
#line 4123 "generated/parser.cpp"
    break;

  case 162: /* task_element: LEFTBRAC duration_constraints task_list RIGHTBRAC  */
#line 1750 "yacc/parser.yy"
                                {
                                vector<TCTR> * v = (vector<TCTR> *) (yyvsp[-2].otype);
                                vector<TCTR>::iterator iv, ev = v->end();
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->merge(*i);
                                        delete (*i);
                                }
                                delete vt;

                                if(v){
                                        for(iv = v->begin();iv!=ev;iv++){
                                        tn->addTConstraint((*iv));
                                        }
                                        delete v;
                                }

                                (yyval.otype) = tn;
                                }
#line 4150 "generated/parser.cpp"
    break;

  case 163: /* task_element: LEFTBRAC task_list RIGHTBRAC  */
#line 1773 "yacc/parser.yy"
                                {
                                vector<TaskNetwork *> * vt = (vector<TaskNetwork *> *) (yyvsp[-1].otype);

                                TaskNetwork * tn = vt->front();
                                vector<TaskNetwork *>::iterator i, e = vt->end();
                                for(i = vt->begin() + 1; i != e; i++) {
                                        tn->merge(*i);
                                        delete (*i);
                                }
                                delete vt;
                                (yyval.otype) = tn;
                                }
#line 4167 "generated/parser.cpp"
    break;

  case 164: /* preconditions_def: %empty  */
#line 1788 "yacc/parser.yy"
                                { (yyval.otype) = 0;}
#line 4173 "generated/parser.cpp"
    break;

  case 165: /* preconditions_def: PDDL_PRECONDITION goal_def  */
#line 1790 "yacc/parser.yy"
                                { (yyval.otype) = (yyvsp[0].otype);}
#line 4179 "generated/parser.cpp"
    break;

  case 166: /* goal_def: LEFTPAR RIGHTPAR  */
#line 1794 "yacc/parser.yy"
                                { (yyval.otype) = 0;}
#line 4185 "generated/parser.cpp"
    break;

  case 167: /* goal_def: LEFTPAR EXCLAMATION goal_def RIGHTPAR  */
#line 1796 "yacc/parser.yy"
                                {
                                CutGoal * cg = new CutGoal();
                                cg->setGoal((Goal *)(yyvsp[-1].otype));
                                (yyval.otype) = cg;
                                }
#line 4195 "generated/parser.cpp"
    break;

  case 168: /* @17: %empty  */
#line 1802 "yacc/parser.yy"
                                {
                                SortGoal * sg = new SortGoal();
                                container = sg;
                                (yyval.otype) = sg;
                                }
#line 4205 "generated/parser.cpp"
    break;

  case 169: /* $@18: %empty  */
#line 1808 "yacc/parser.yy"
                                {
                                container = 0;
                                }
#line 4213 "generated/parser.cpp"
    break;

  case 170: /* goal_def: LEFTPAR SORTBY @17 v_list $@18 goal_def RIGHTPAR  */
#line 1812 "yacc/parser.yy"
                                {
                                SortGoal * sg = (SortGoal *) (yyvsp[-4].otype);
                                Goal * g = (Goal *) (yyvsp[-1].otype);
                                sg->setGoal(g);
                                // Buscamos que la variable por la que queremos ordenar al menos
                                // aparezca en la precondicion.
                                keylistcit i, e = sg->endp();
                                for(i=sg->beginp();i!=e;i++){
                                        if(!g->hasTerm((*i).first)) {
                                        snprintf(parerr,256,"The variable you are trying to sort by (%s), doesn't appear in goal!.",parser_api->termtable->getVariable((*i))->getName());
                                        yyerror(parerr);
                                        }
                                }
                                (yyval.otype) = sg;
                                }
#line 4233 "generated/parser.cpp"
    break;

  case 171: /* @19: %empty  */
#line 1828 "yacc/parser.yy"
                                {
                                (yyval.otype) = new FluentVar((pkey *)(yyvsp[0].termtype));
                                }
#line 4241 "generated/parser.cpp"
    break;

  case 172: /* goal_def: LEFTPAR PDDL_BIND variable @19 fluent_exp RIGHTPAR  */
#line 1832 "yacc/parser.yy"
                                {
                                FluentVar * fv = (FluentVar *) (yyvsp[-2].otype);
                                BoundGoal * bg = new BoundGoal(fv,(Evaluable *)(yyvsp[-1].otype));
                                    if(!parser_api->domain->errfluents && !parser_api->domain->hasRequirement(":fluents"))
                                    {
                                        parser_api->domain->errfluents = true;
                                        yyerror("Using a clause that requires `:fluents' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = bg;
                                }
#line 4256 "generated/parser.cpp"
    break;

  case 173: /* goal_def: LEFTPAR PPRINT simple_goal_def RIGHTPAR  */
#line 1843 "yacc/parser.yy"
                                {
                                PrintGoal * pg = new PrintGoal();
                                pg->setGoal((Goal *) (yyvsp[-1].otype));
                                (yyval.otype) = pg;
                                }
#line 4266 "generated/parser.cpp"
    break;

  case 174: /* goal_def: LEFTPAR PPRINT HTN_TEXT RIGHTPAR  */
#line 1849 "yacc/parser.yy"
                                {
                                PrintGoal * pg = new PrintGoal();
                                pg->setStr((yyvsp[-1].type_string));
                                (yyval.otype) = pg;
                                }
#line 4276 "generated/parser.cpp"
    break;

  case 175: /* @20: %empty  */
#line 1855 "yacc/parser.yy"
                                {
                                PrintGoal * pg = new PrintGoal();
                                container = pg;
                                (yyval.otype) = pg;
                                contador = 0;
                                }
#line 4287 "generated/parser.cpp"
    break;

  case 176: /* goal_def: LEFTPAR PPRINT @20 term_list RIGHTPAR  */
#line 1862 "yacc/parser.yy"
                                {
                                container = 0;
                                (yyval.otype) = (yyvsp[-2].otype);
                                }
#line 4296 "generated/parser.cpp"
    break;

  case 177: /* goal_def: simple_goal_def  */
#line 1867 "yacc/parser.yy"
                                {
                                (yyval.otype) = (yyvsp[0].otype);
                                }
#line 4304 "generated/parser.cpp"
    break;

  case 178: /* goal_def: timed_goal  */
#line 1871 "yacc/parser.yy"
                                {
                                (yyval.otype) = (yyvsp[0].otype);
                                }
#line 4312 "generated/parser.cpp"
    break;

  case 179: /* @21: %empty  */
#line 1877 "yacc/parser.yy"
                                {
                                AndGoal * ag = new AndGoal();
                                gcontainer.push_back(ag);
                                (yyval.otype) = ag;
                                }
#line 4322 "generated/parser.cpp"
    break;

  case 180: /* $@22: %empty  */
#line 1883 "yacc/parser.yy"
                                {
                                gcontainer.pop_back();
                                }
#line 4330 "generated/parser.cpp"
    break;

  case 181: /* simple_goal_def: LEFTPAR PDDL_AND @21 goal_def_list $@22 RIGHTPAR  */
#line 1887 "yacc/parser.yy"
                                {
                                AndGoal * ag = (AndGoal *) (yyvsp[-3].otype);
                                (yyval.otype) = ag;
                                }
#line 4339 "generated/parser.cpp"
    break;

  case 182: /* @23: %empty  */
#line 1892 "yacc/parser.yy"
                                {
                                OrGoal * ag = new OrGoal();
                                gcontainer.push_back(ag);
                                (yyval.otype) = ag;
                                }
#line 4349 "generated/parser.cpp"
    break;

  case 183: /* $@24: %empty  */
#line 1898 "yacc/parser.yy"
                                {
                                gcontainer.pop_back();
                                }
#line 4357 "generated/parser.cpp"
    break;

  case 184: /* simple_goal_def: LEFTPAR PDDL_OR @23 goal_def_list $@24 RIGHTPAR  */
#line 1902 "yacc/parser.yy"
                                {
                                OrGoal * ag = (OrGoal *) (yyvsp[-3].otype);
                                (yyval.otype) = ag;
                                }
#line 4366 "generated/parser.cpp"
    break;

  case 185: /* simple_goal_def: LEFTPAR PDDL_NOT goal_def RIGHTPAR  */
#line 1907 "yacc/parser.yy"
                                { Goal * g = (Goal *) (yyvsp[-1].otype);
                                if(g){
                                if(g->getPolarity())
                                g->setPolarity(false);
                                else
                                g->setPolarity(true);
                                }
                                /* negative-preconditions */
                                if(!parser_api->domain->errnegative && !parser_api->domain->hasRequirement(":negative-preconditions"))
                                {
                                        parser_api->domain->errnegative = true;
                                yyerror("Using a clause that requires `:negative-preconditions' and is not declared in requirements clause");
                                }
                                (yyval.otype) = g;
                                }
#line 4386 "generated/parser.cpp"
    break;

  case 186: /* simple_goal_def: LEFTPAR PDDL_IMPLY goal_def goal_def RIGHTPAR  */
#line 1923 "yacc/parser.yy"
                                {
                                (yyval.otype) = new ImplyGoal((Goal *) (yyvsp[-2].otype), (Goal *) (yyvsp[-1].otype));
                                    if(!parser_api->domain->errdisjunctive && !parser_api->domain->hasRequirement(":disjunctive-preconditions"))
                                    {
                                        parser_api->domain->errdisjunctive = true;
                                        yyerror("Using a clause that requires `:disjunctive-preconditions' and is not declared in requirements clause");
                                    }
                                }
#line 4399 "generated/parser.cpp"
    break;

  case 187: /* @25: %empty  */
#line 1932 "yacc/parser.yy"
                                {
                                ExistsGoal * fag = new ExistsGoal();
                                container = fag;
                                (yyval.otype) = fag;
                                }
#line 4409 "generated/parser.cpp"
    break;

  case 188: /* $@26: %empty  */
#line 1938 "yacc/parser.yy"
                                {
                                container = 0;
                                }
#line 4417 "generated/parser.cpp"
    break;

  case 189: /* simple_goal_def: LEFTPAR PDDL_EXISTS @25 LEFTPAR variable_typed_list RIGHTPAR $@26 goal_def RIGHTPAR  */
#line 1942 "yacc/parser.yy"
                                {
                                ExistsGoal * fag = (ExistsGoal *) (yyvsp[-6].otype);
                                Goal * g = (Goal *) (yyvsp[-1].otype);
                                fag->setGoal(g);
                                /* universal-preconditions */
                                    if(!parser_api->domain->errexistential && !parser_api->domain->hasRequirement(":existential-preconditions"))
                                    {
                                        parser_api->domain->errexistential = true;
                                        yyerror("Using a clause that requires `:existential-preconditions' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = fag;
                                }
#line 4434 "generated/parser.cpp"
    break;

  case 190: /* @27: %empty  */
#line 1955 "yacc/parser.yy"
                                {
                                // creamos el forall, y lo ponemos como
                                // el elemento que va a contener a las variables
                                ForallGoal * fag = new ForallGoal();
                                container = fag;
                                (yyval.otype) = fag;
                                }
#line 4446 "generated/parser.cpp"
    break;

  case 191: /* $@28: %empty  */
#line 1963 "yacc/parser.yy"
                                {
                                container = 0;
                                }
#line 4454 "generated/parser.cpp"
    break;

  case 192: /* simple_goal_def: LEFTPAR PDDL_FORALL @27 LEFTPAR variable_typed_list RIGHTPAR $@28 goal_def RIGHTPAR  */
#line 1967 "yacc/parser.yy"
                                {
                                ForallGoal * fag = (ForallGoal *) (yyvsp[-6].otype);
                                Goal * g = (Goal *) (yyvsp[-1].otype);
                                fag->setGoal(g);
                                /* universal-preconditions */
                                    if(!parser_api->domain->erruniversal && !parser_api->domain->hasRequirement(":universal-preconditions"))
                                    {
                                        parser_api->domain->erruniversal = true;
                                        yyerror("Using a clause that requires `:universal-preconditions' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = fag;
                                }
#line 4471 "generated/parser.cpp"
    break;

  case 193: /* simple_goal_def: f_comp  */
#line 1980 "yacc/parser.yy"
                                { (yyval.otype) = (yyvsp[0].otype);}
#line 4477 "generated/parser.cpp"
    break;

  case 194: /* simple_goal_def: atomic_formula_term_goal  */
#line 1982 "yacc/parser.yy"
                                { (yyval.otype) = (LiteralGoal *) (yyvsp[0].otype);}
#line 4483 "generated/parser.cpp"
    break;

  case 195: /* timed_goal: LEFTPAR time_specifier simple_goal_def RIGHTPAR  */
#line 1986 "yacc/parser.yy"
                                {
                                Goal * g = (Goal *) (yyvsp[-1].otype);
                                TimeInterval * ti = (TimeInterval *) (yyvsp[-2].otype);
                                g->setTime(ti);
                                    if(!parser_api->domain->errdurative && !parser_api->domain->hasRequirement(":durative-actions"))
                                    {
                                        parser_api->domain->errdurative = true;
                                        yyerror("Using a clause that requires `:durative-actions' and is not declared in requirements clause");
                                    }
                                    if(!isDurative) {
                                        yyerror("Using a durative goal inside a non durative action.");
                                    }
                                (yyval.otype) = g;
                                }
#line 4502 "generated/parser.cpp"
    break;

  case 196: /* order: %empty  */
#line 2002 "yacc/parser.yy"
                                {
                                (yyval.type_int) = DEFAULT_CRITERIA;
                                }
#line 4510 "generated/parser.cpp"
    break;

  case 197: /* order: ASC  */
#line 2006 "yacc/parser.yy"
                                {
                                (yyval.type_int) = SASC;
                                }
#line 4518 "generated/parser.cpp"
    break;

  case 198: /* order: DESC  */
#line 2010 "yacc/parser.yy"
                                {
                                (yyval.type_int) = SDESC;
                                }
#line 4526 "generated/parser.cpp"
    break;

  case 201: /* v_crit: variable order  */
#line 2020 "yacc/parser.yy"
                                {
                                pkey ret = *(yyvsp[-1].termtype);
                                SortGoal * sg = (SortGoal *) container;
                                sg->addCriteria((SortType)(yyvsp[0].type_int));
                                sg->addParameter(ret);
                                }
#line 4537 "generated/parser.cpp"
    break;

  case 203: /* goal_def_list: goal_def_list goal_def  */
#line 2029 "yacc/parser.yy"
                                {
                                if((yyvsp[0].otype)){
                                ContainerGoal * lc = (ContainerGoal *) gcontainer.back();
                                lc->addGoalByRef((Goal *) (yyvsp[0].otype));

                                }
                                }
#line 4549 "generated/parser.cpp"
    break;

  case 204: /* atomic_formula_term_effect: literal_effect  */
#line 2039 "yacc/parser.yy"
                                { (yyval.otype) = (LiteralEffect *) (yyvsp[0].otype);}
#line 4555 "generated/parser.cpp"
    break;

  case 205: /* atomic_formula_term_effect: LEFTPAR MAINTAIN literal_effect RIGHTPAR  */
#line 2041 "yacc/parser.yy"
                                { LiteralEffect * lit = (LiteralEffect *) (yyvsp[-1].otype);
                                lit->setMaintain(true);
                                (yyval.otype) = lit;
                                }
#line 4564 "generated/parser.cpp"
    break;

  case 206: /* $@29: %empty  */
#line 2050 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                LiteralEffect * lit=0;
                                Meta * mt=0;
                                // buscamos si el literal ya est� definido en el diccionario de
                                // nombres de literales (deber�a estarlo)
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                lit = new LiteralEffect(posit->second,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new LiteralEffect(idCounter++,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador = 0;
                                }
#line 4592 "generated/parser.cpp"
    break;

  case 207: /* literal_effect: LEFTPAR term_name $@29 term_list RIGHTPAR  */
#line 2074 "yacc/parser.yy"
                                {
                                LiteralEffect * lit= (LiteralEffect *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     Unifier u;
                                     if(unify3(lit->getParameters(),(*i).second->getParameters(),&u)){
                                        u.applyTypeSubstitutions(0);
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                        snprintf(parerr,256,"(2) No matching predicate for `%s'.",lit->toString());
                                        yyerror(parerr);
                                        if(candidates.size() > 0) {
                                        *errflow << "Possible candidates:" << endl;
                                          for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                             *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                        (*j)->printL(errflow,1);
                                        *errflow << endl;
                                          }
                                        }
                                }
                                (yyval.otype) = lit;
                                }
#line 4633 "generated/parser.cpp"
    break;

  case 208: /* $@30: %empty  */
#line 2113 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                LiteralGoal * lit=0;
                                Meta * mt = 0;
                                // buscamos si el literal ya est� definido en el diccionario de
                                // nombres de literales (deber�a estarlo)
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                lit = new LiteralGoal(posit->second,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new LiteralGoal(idCounter++,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador = 0;
                                }
#line 4661 "generated/parser.cpp"
    break;

  case 209: /* atomic_formula_term_goal: LEFTPAR term_name $@30 term_list RIGHTPAR  */
#line 2137 "yacc/parser.yy"
                                {
                                LiteralGoal * lit= (LiteralGoal *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     Unifier u;
                                     if(unify3(lit->getParameters(),(*i).second->getParameters(),&u)){
                                        u.applyTypeSubstitutions(0);
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                        snprintf(parerr,256,"(3) No matching predicate for `%s'.",lit->toString());
                                        yyerror(parerr);
                                        if(candidates.size() > 0) {
                                        *errflow << "Possible candidates:" << endl;
                                          for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                             *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                        (*j)->printL(errflow,1);
                                        *errflow << endl;
                                          }
                                        }
                                }
                                (yyval.otype) = lit;
                                }
#line 4702 "generated/parser.cpp"
    break;

  case 212: /* term: term_name  */
#line 2181 "yacc/parser.yy"
                                {
                                string * c = (string *) (yyvsp[0].otype);
                                if(!container)
                                *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                if(container){
                                // la constante deber�a haberse definido con anterioridad, en otro caso
                                // se trata de un error
                                ldictionaryit posit = (parser_api->domain->cdictionary).find(c->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                        // devolver el pkey de la constante
                                        container->addParameter(make_pair((*posit).second, 0));
                                        contador = container->getModificableParameters()->size()+1;
                                }
                                else {
                                     snprintf(parerr,256,"Undefined constant `%s'.",c->c_str());
                                     yyerror(parerr);
                                     ConstantSymbol * n = new ConstantSymbol(c->c_str(),-1);
                                     n->setLineNumber(lexer->getLineNumber());
                                     n->setFileId(parser_api->fileid);
                                     container->addParameter(parser_api->termtable->addConstant(n));
                                     contador = container->getModificableParameters()->size()+1;
                                }
                                }
                                delete c;
                                }
#line 4732 "generated/parser.cpp"
    break;

  case 213: /* term: variable  */
#line 2207 "yacc/parser.yy"
                                {
                                if(!container)
                                *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                if(container){
                                container->addParameter(*(yyvsp[0].termtype));
                                if(container->getModificableParameters()->empty())
                                        contador = 0;
                                }
                                }
#line 4746 "generated/parser.cpp"
    break;

  case 214: /* term: variable PDDL_HYPHEN type  */
#line 2217 "yacc/parser.yy"
                                {
                                if(!container)
                                *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                if(container && (yyvsp[0].otype)){
                                // recorremos hacia atr�s todas las variables insertadas anteriormente,
                                // hasta encontrar la primera que no tiene tipo asignado.
                                // A partir de este asignamos type
                                if(container->getModificableParameters()->empty())
                                        contador = 0;
                                container->addParameter(*(yyvsp[-2].termtype));
                                vector<Type *> * vt = (vector<Type *> *)(yyvsp[0].otype);
                                if(!vt->empty()) {
                                TestTypeTree()(vt);
                                KeyList * kl = container->getModificableParameters();
                                KeyList::iterator i,e;
                                e = kl->end();
                                for(i=kl->begin() + contador;i!=e;i++)
                                {
                                        if(parser_api->termtable->isVariable(*i)){
                                        if(!parser_api->termtable->getVariable(*i)->specializeTypes(vt)){
                                                snprintf(parerr,256,"Unable to specialize the type(s) for variable `%s'.",parser_api->termtable->getVariable(*i)->getName());
                                                yyerror(parerr);
                                        }
                                        }
                                }
                                }
                                delete vt;
                                contador = container->getModificableParameters()->size();
                                }
                                else if(!(yyvsp[0].otype)) {
                                        snprintf(parerr,256,"Type expected after `-'.");
                                        yywarning(parerr);
                                }
                                }
#line 4785 "generated/parser.cpp"
    break;

  case 215: /* term: number  */
#line 2252 "yacc/parser.yy"
                                {
                                if(!container)
                                *errflow << "(mensaje recordatorio) (-- Aqui deber�a haber un container --)" << endl;
                                if(container){
                                container->addParameter(make_pair(-1,(yyvsp[0].type_number)));
                                contador = container->getModificableParameters()->size() +1;
                                }
                                }
#line 4798 "generated/parser.cpp"
    break;

  case 216: /* number: PDDL_NUMBER  */
#line 2263 "yacc/parser.yy"
                                {(yyval.type_number)=(yyvsp[0].type_number);}
#line 4804 "generated/parser.cpp"
    break;

  case 217: /* number: PDDL_DNUMBER  */
#line 2265 "yacc/parser.yy"
                                {(yyval.type_number)=(yyvsp[0].type_number);}
#line 4810 "generated/parser.cpp"
    break;

  case 218: /* var: PDDL_VAR  */
#line 2268 "yacc/parser.yy"
                                {
                                (yyval.type_string) = (yyvsp[0].type_string);
                                }
#line 4818 "generated/parser.cpp"
    break;

  case 219: /* var: PDDL_DURATIONVAR  */
#line 2272 "yacc/parser.yy"
                                {
                                (yyval.type_string) =(yyvsp[0].type_string);
                                }
#line 4826 "generated/parser.cpp"
    break;

  case 220: /* var: STARTVAR  */
#line 2276 "yacc/parser.yy"
                                {
                                (yyval.type_string) = (yyvsp[0].type_string);
                                }
#line 4834 "generated/parser.cpp"
    break;

  case 221: /* var: ENDVAR  */
#line 2280 "yacc/parser.yy"
                                {
                                (yyval.type_string) = (yyvsp[0].type_string);
                                }
#line 4842 "generated/parser.cpp"
    break;

  case 222: /* variable: var  */
#line 2286 "yacc/parser.yy"
                                {
                                  // miramos si la variable se define en un contexto en concreto
                                  // para dar el mismo identificador, por ejemplo en el literal
                                  // (l ?x ?y ?x) en el contexto del literal las dos variables ?x
                                  // que aparecen tienen el mismo identificador. Esto sirve para
                                  // que cuando cambie el valor de una de las ?x se cambien todas.
                                  static pkey id;
                                  id.first=-1;
                                  id.second=0;

                                  if(context){
                                      ldictionaryit posit = context->find((yyvsp[0].type_string));

                                      if(posit==context->end()){
                                          // no se encontr� ninguna variable igual en el contexto
                                          // se crea una nueva
                                          VariableSymbol * v = new VariableSymbol(-1,parser_api->domain->metainfo.size());
                                          Meta * mt = new Meta((yyvsp[0].type_string),lexer->getLineNumber(),parser_api->fileid);
                                          id = parser_api->termtable->addVariable(v);
                                          parser_api->domain->metainfo.push_back(mt);
                                          context->insert(make_pair(parser_api->termtable->getVariable(id)->getName(),id.first));
                                      }
                                      else {
                                          id.first=(*posit).second;
                                      }
                                  }
                                  else {
                                       VariableSymbol * v = new VariableSymbol(-1,parser_api->domain->metainfo.size());
                                       Meta * mt = new Meta((yyvsp[0].type_string),lexer->getLineNumber(),parser_api->fileid);
                                       id = parser_api->termtable->addVariable(v);
                                       parser_api->domain->metainfo.push_back(mt);
                                  }
                                  // devolvemos la variable
                                  (yyval.termtype) = &id;
                                }
#line 4882 "generated/parser.cpp"
    break;

  case 223: /* f_comp: LEFTPAR binary_comp fluent_exp fluent_exp RIGHTPAR  */
#line 2324 "yacc/parser.yy"
                                {
                                ComparationGoal * cg = (ComparationGoal *) (yyvsp[-3].otype);
                                Evaluable * first, * second;
                                first = (Evaluable *) (yyvsp[-2].otype);
                                second = (Evaluable *) (yyvsp[-1].otype);
                                cg->setFirst(first);
                                cg->setSecond(second);
                                (yyval.otype) = cg;
                                }
#line 4896 "generated/parser.cpp"
    break;

  case 224: /* binary_comp: GREATHER  */
#line 2336 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CGREATHER);
                                (yyval.otype) = cg;
                                }
#line 4906 "generated/parser.cpp"
    break;

  case 225: /* binary_comp: LESS  */
#line 2342 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CLESS);
                                (yyval.otype) = cg;
                                }
#line 4916 "generated/parser.cpp"
    break;

  case 226: /* binary_comp: EQUAL  */
#line 2348 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CEQUAL);
                                (yyval.otype) = cg;
                                }
#line 4926 "generated/parser.cpp"
    break;

  case 227: /* binary_comp: GREATHER_EQUAL  */
#line 2354 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CGREATHER_EQUAL);
                                (yyval.otype) = cg;
                                }
#line 4936 "generated/parser.cpp"
    break;

  case 228: /* binary_comp: LESS_EQUAL  */
#line 2360 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CLESS_EQUAL);
                                (yyval.otype) = cg;
                                }
#line 4946 "generated/parser.cpp"
    break;

  case 229: /* binary_comp: DISTINCT  */
#line 2366 "yacc/parser.yy"
                                {
                                ComparationGoal * cg =  new ComparationGoal();
                                cg->setComparator(CDISTINCT);
                                (yyval.otype) = cg;
                                }
#line 4956 "generated/parser.cpp"
    break;

  case 230: /* fluent_exp: number  */
#line 2374 "yacc/parser.yy"
                                {
                                FluentNumber * f = new FluentNumber((yyvsp[0].type_number));
                                isNumber = true;
                                (yyval.otype) = f;
                                }
#line 4966 "generated/parser.cpp"
    break;

  case 231: /* fluent_exp: LEFTPAR binary_op fluent_exp fluent_exp RIGHTPAR  */
#line 2380 "yacc/parser.yy"
                                { FluentOperator * fo = (FluentOperator *) (yyvsp[-3].otype);
                                Evaluable * first, * second;
                                first = (Evaluable *) (yyvsp[-2].otype);
                                second = (Evaluable *) (yyvsp[-1].otype);
                                const Type * number = parser_api->domain->getType("number");
                                if(!first->isType(number)) {
                                snprintf(parerr,256,"Operand `%s' is not of number type.",first->toStringEvaluable());
                                yyerror(parerr);
                                }
                                if(!second->isType(number)) {
                                snprintf(parerr,256,"Operand `%s' is not of number type.",second->toStringEvaluable());
                                yyerror(parerr);
                                }
                                fo->setFirst(first);
                                fo->setSecond(second);
                                (yyval.otype) = fo;
                                }
#line 4988 "generated/parser.cpp"
    break;

  case 232: /* fluent_exp: LEFTPAR unary_op fluent_exp silly_exp RIGHTPAR  */
#line 2398 "yacc/parser.yy"
                                {
                                FluentOperator * fo = new FluentOperator((Operation)(yyvsp[-3].type_int));
                                Evaluable * first, * second;
                                first = (Evaluable *) (yyvsp[-2].otype);
                                second = (Evaluable *) (yyvsp[-1].otype);
                                const Type * number = parser_api->domain->getType("number");
                                if(!first->isType(number)) {
                                        snprintf(parerr,256,"Operand `%s' is not of number type.",first->toStringEvaluable());
                                        yyerror(parerr);
                                }
                                if(second)
                                        if(!second->isType(number)) {
                                        snprintf(parerr,256,"Operand `%s' is not of number type.",second->toStringEvaluable());
                                        yyerror(parerr);
                                        }
                                fo->setFirst(first);
                                if(second)
                                        fo->setSecond(second);
                                if(second && (yyvsp[-3].type_int) != OSUBSTRACT) {
                                        snprintf(parerr,256,"Using two arguments in a operator that only needs one: %s.",fo->toStringEvaluable());
                                        yyerror(parerr);
                                }
                                (yyval.otype) = fo;
                                }
#line 5017 "generated/parser.cpp"
    break;

  case 233: /* fluent_exp: f_head_ref  */
#line 2423 "yacc/parser.yy"
                                {
                                (yyval.otype) = (FluentLiteral *) (yyvsp[0].otype);
                                }
#line 5025 "generated/parser.cpp"
    break;

  case 234: /* fluent_exp: variable  */
#line 2427 "yacc/parser.yy"
                                {
                                FluentVar * v = new FluentVar((yyvsp[0].termtype));
                                // comprobar que la variable sea de tipo number
                                if(!v->isType(parser_api->domain->getType("number"))){
                                        // Dar warning si es objeto.
                                        if(v->isObjectType()) {
                                        parser_api->termtable->getVariable(v->getId())->specializeTypes(parser_api->domain->getModificableType("number"));
                                        snprintf(parerr,256,"Seting type of `%s' to number.",parser_api->termtable->getVariable(v->getId())->getName());
                                        yywarning(parerr);
                                        }
                                        else
                                        parser_api->termtable->getVariable(v->getId())->specializeTypes(parser_api->domain->getModificableType("number"));
                                }
                                (yyval.otype) = v;
                                }
#line 5045 "generated/parser.cpp"
    break;

  case 235: /* fluent_exp: term_name  */
#line 2443 "yacc/parser.yy"
                                {
                                string * c = (string *) (yyvsp[0].otype);
                                FluentConstant * f;
                                ldictionaryit posit = (parser_api->domain->cdictionary).find(c->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                        // devolver el pkey de la constante
                                        f = new FluentConstant(make_pair((*posit).second, 0));
                                }
                                else {
                                    snprintf(parerr,256,"Undefined constant `%s'.",c->c_str());
                                    yyerror(parerr);
                                    ConstantSymbol * n = new ConstantSymbol(c->c_str(),-1);
                                    n->setLineNumber(lexer->getLineNumber());
                                    n->setFileId(parser_api->fileid);
                                    f = new FluentConstant(parser_api->termtable->addConstant(n));
                                }
                                delete c;
                                (yyval.otype) = f;
                                }
#line 5069 "generated/parser.cpp"
    break;

  case 236: /* silly_exp: %empty  */
#line 2465 "yacc/parser.yy"
                                {(yyval.otype)=0;}
#line 5075 "generated/parser.cpp"
    break;

  case 237: /* silly_exp: fluent_exp  */
#line 2467 "yacc/parser.yy"
                                {(yyval.otype)=(yyvsp[0].otype);}
#line 5081 "generated/parser.cpp"
    break;

  case 238: /* unary_op: PDDL_HYPHEN  */
#line 2471 "yacc/parser.yy"
                                {(yyval.type_int)=(int)OSUBSTRACT;}
#line 5087 "generated/parser.cpp"
    break;

  case 239: /* unary_op: ABS  */
#line 2473 "yacc/parser.yy"
                                {(yyval.type_int)=(int)UABS;}
#line 5093 "generated/parser.cpp"
    break;

  case 240: /* unary_op: SQRT  */
#line 2475 "yacc/parser.yy"
                                {(yyval.type_int)=(int)USQRT;}
#line 5099 "generated/parser.cpp"
    break;

  case 241: /* binary_op: PLUS  */
#line 2479 "yacc/parser.yy"
                                {
                                FluentOperator * fo = new FluentOperator(OADD);
                                (yyval.otype) = fo;
                                }
#line 5108 "generated/parser.cpp"
    break;

  case 242: /* binary_op: MULTIPLY  */
#line 2484 "yacc/parser.yy"
                                {
                                FluentOperator * fo = new FluentOperator(OTIMES);
                                (yyval.otype) = fo;
                                }
#line 5117 "generated/parser.cpp"
    break;

  case 243: /* binary_op: DIVIDE  */
#line 2489 "yacc/parser.yy"
                                {
                                FluentOperator * fo = new FluentOperator(ODIVIDE);
                                (yyval.otype) = fo;
                                }
#line 5126 "generated/parser.cpp"
    break;

  case 244: /* binary_op: POW  */
#line 2494 "yacc/parser.yy"
                                {
                                FluentOperator * fo = new FluentOperator(OPOW);
                                (yyval.otype) = fo;
                                }
#line 5135 "generated/parser.cpp"
    break;

  case 245: /* $@31: %empty  */
#line 2564 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                Function * lit=0;
                                Meta * mt = 0;
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),(const char *) nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                        lit = new Function(posit->second,parser_api->domain->metainfo.size(),false,0);
                                        mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new Function(idCounter++,parser_api->domain->metainfo.size(),false,0);
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador=0;
                                }
#line 5161 "generated/parser.cpp"
    break;

  case 246: /* f_head: LEFTPAR term_name $@31 term_list RIGHTPAR  */
#line 2586 "yacc/parser.yy"
                                {
                                Function * lit= (Function *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     Unifier u;
                                     if(unify3(lit->getParameters(),(*i).second->getParameters(),&u)){
                                        u.applyTypeSubstitutions(0);
                                        //if(((Function *)(*i).second)->isPython()){
                                        //    lit->setPython();
                                        //    lit->setCode(((Function *)(*i).second)->getCode());
                                        //}
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                        snprintf(parerr,256,"(5) No matching predicate for `%s'.",lit->toString());
                                        yyerror(parerr);
                                        if(candidates.size() > 0) {
                                        *errflow << "Possible candidates:" << endl;
                                          for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                             *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                        (*j)->printL(errflow,1);
                                        *errflow << endl;
                                          }
                                        }
                                }
                                (yyval.otype) = lit;
                                }
#line 5206 "generated/parser.cpp"
    break;

  case 247: /* $@32: %empty  */
#line 2682 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                FluentLiteral * lit=0;
                                Meta * mt = 0;
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),(const char *) nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                        lit = new FluentLiteral(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new FluentLiteral(idCounter++,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador = 0;
                                }
#line 5232 "generated/parser.cpp"
    break;

  case 248: /* f_head_ref: LEFTPAR term_name $@32 term_list RIGHTPAR  */
#line 2704 "yacc/parser.yy"
                                {
                                FluentLiteral * lit= (FluentLiteral *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                // y el n�mero de argumentos adecuado
                                // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     Unifier u;
                                     if(unify3(lit->getParameters(),(*i).second->getParameters(),&u)){
                                        u.applyTypeSubstitutions(0);
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                        snprintf(parerr,256,"(7) No matching predicate for `%s'.",lit->toString());
                                        yyerror(parerr);
                                        if(candidates.size() > 0) {
                                        *errflow << "Possible candidates:" << endl;
                                          for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                             *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                        (*j)->printL(errflow,1);
                                        *errflow << endl;
                                          }
                                        }
                                }
                                (yyval.otype) = lit;
                                }
#line 5273 "generated/parser.cpp"
    break;

  case 249: /* effect_def: %empty  */
#line 2744 "yacc/parser.yy"
                                {(yyval.otype) = 0;}
#line 5279 "generated/parser.cpp"
    break;

  case 250: /* effect_def: PDDL_EFFECT effect  */
#line 2746 "yacc/parser.yy"
                                {(yyval.otype) =(yyvsp[0].otype);}
#line 5285 "generated/parser.cpp"
    break;

  case 251: /* effect: LEFTPAR RIGHTPAR  */
#line 2750 "yacc/parser.yy"
                                {(yyval.otype)=0;}
#line 5291 "generated/parser.cpp"
    break;

  case 252: /* $@33: %empty  */
#line 2752 "yacc/parser.yy"
                                {
                                AndEffect * ae = new AndEffect();
                                econtainer.push_back(ae);
                                }
#line 5300 "generated/parser.cpp"
    break;

  case 253: /* effect: LEFTPAR PDDL_AND $@33 c_effect_list RIGHTPAR  */
#line 2757 "yacc/parser.yy"
                                {
                                AndEffect * ae = (AndEffect *) econtainer.back();
                                econtainer.pop_back();
                                (yyval.otype) = ae;
                                }
#line 5310 "generated/parser.cpp"
    break;

  case 254: /* effect: c_effect  */
#line 2763 "yacc/parser.yy"
                                { (yyval.otype)= (yyvsp[0].otype);}
#line 5316 "generated/parser.cpp"
    break;

  case 255: /* timed_effect: LEFTPAR time_point p_effect RIGHTPAR  */
#line 2767 "yacc/parser.yy"
                                {
                                Effect * e = (Effect *) (yyvsp[-1].otype);
                                Evaluable * ti = (Evaluable *) (yyvsp[-2].otype);
                                if(e->isLiteralEffect()){
                                        LiteralEffect * le = ((LiteralEffect *)e);
                                        le->setTime(ti);
                                }
                                else{
                                        ((FluentEffect *)e)->setTime(ti);
                                }
                                    if(!parser_api->domain->errdurative && !parser_api->domain->hasRequirement(":durative-actions"))
                                    {
                                        parser_api->domain->errdurative = true;
                                        yyerror("Using a clause that requires `:durative-actions' and is not declared in requirements clause");
                                    }
                                    if(!isDurative)
                                    {
                                        yyerror("Using a durative effect inside a non durative action.");
                                    }
                                (yyval.otype) = e;
                                }
#line 5342 "generated/parser.cpp"
    break;

  case 256: /* @34: %empty  */
#line 2792 "yacc/parser.yy"
                                {
                                // creamos el forall, y lo ponemos como
                                // el elemento que va a contener a las variables
                                ForallEffect * fae = new ForallEffect();
                                container = fae;
                                (yyval.otype) = fae;
                                }
#line 5354 "generated/parser.cpp"
    break;

  case 257: /* $@35: %empty  */
#line 2800 "yacc/parser.yy"
                                {
                                container = 0;
                                }
#line 5362 "generated/parser.cpp"
    break;

  case 258: /* c_effect: LEFTPAR PDDL_FORALL @34 LEFTPAR variable_typed_list RIGHTPAR $@35 effect RIGHTPAR  */
#line 2805 "yacc/parser.yy"
                                {
                                ForallEffect * fae = (ForallEffect *) (yyvsp[-6].otype);
                                Effect * e = (Effect *) (yyvsp[-1].otype);
                                fae->setEffect(e);
                                    if(!parser_api->domain->errconditionals && !parser_api->domain->hasRequirement(":conditional-effects"))
                                    {
                                        parser_api->domain->errconditionals = true;
                                        yyerror("Using a clause that requires `:conditional-effects' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = fae;
                                }
#line 5378 "generated/parser.cpp"
    break;

  case 259: /* c_effect: LEFTPAR PDDL_WHEN goal_def cond_effect RIGHTPAR  */
#line 2817 "yacc/parser.yy"
                                {
                                WhenEffect * we = new WhenEffect((Goal *)(yyvsp[-2].otype),(Effect *)(yyvsp[-1].otype));
                                    if(!parser_api->domain->errconditionals && !parser_api->domain->hasRequirement(":conditional-effects"))
                                    {
                                        parser_api->domain->errconditionals = true;
                                        yyerror("Using a clause that requires `:conditional-effects' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = we;
                                }
#line 5392 "generated/parser.cpp"
    break;

  case 260: /* c_effect: p_effect  */
#line 2827 "yacc/parser.yy"
                                {(yyval.otype) = (yyvsp[0].otype);}
#line 5398 "generated/parser.cpp"
    break;

  case 261: /* c_effect: timed_effect  */
#line 2829 "yacc/parser.yy"
                                { (yyval.otype)= (yyvsp[0].otype);}
#line 5404 "generated/parser.cpp"
    break;

  case 263: /* c_effect_list: c_effect_list c_effect  */
#line 2834 "yacc/parser.yy"
                                {
                                if((yyvsp[0].otype)){
                                ContainerEffect * lc = (ContainerEffect *) econtainer.back();
                                lc->addEffectByRef((Effect *) (yyvsp[0].otype));
                                }
                                }
#line 5415 "generated/parser.cpp"
    break;

  case 264: /* p_effect: LEFTPAR assign_op f_head_ref fluent_exp RIGHTPAR  */
#line 2843 "yacc/parser.yy"
                                {
                                FluentEffect * fe = new FluentEffect((FOperation)(yyvsp[-3].type_int),(FluentLiteral *)(yyvsp[-2].otype),(Evaluable *)(yyvsp[-1].otype));
                                    if(!parser_api->domain->errfluents && !parser_api->domain->hasRequirement(":fluents"))
                                    {
                                        parser_api->domain->errfluents = true;
                                        yyerror("Using a clause that requires `:fluents' and is not declared in requirements clause");
                                    }
                                (yyval.otype) = fe;
                                }
#line 5429 "generated/parser.cpp"
    break;

  case 265: /* p_effect: LEFTPAR PDDL_NOT atomic_formula_term_effect RIGHTPAR  */
#line 2853 "yacc/parser.yy"
                                {
                                LiteralEffect * le = (LiteralEffect *) (yyvsp[-1].otype);
                                if(le->getPolarity())
                                        le->setPolarity(false);
                                (yyval.otype)=le;
                                }
#line 5440 "generated/parser.cpp"
    break;

  case 266: /* p_effect: atomic_formula_term_effect  */
#line 2860 "yacc/parser.yy"
                                {(yyval.otype)=(yyvsp[0].otype);}
#line 5446 "generated/parser.cpp"
    break;

  case 268: /* p_effect_list: p_effect_list p_effect  */
#line 2865 "yacc/parser.yy"
                                {
                                if((yyvsp[0].otype)){
                                ContainerEffect * lc = (ContainerEffect *) econtainer.back();
                                lc->addEffectByRef((Effect *) (yyvsp[0].otype));
                                }
                                }
#line 5457 "generated/parser.cpp"
    break;

  case 269: /* $@36: %empty  */
#line 2874 "yacc/parser.yy"
                                {
                                AndEffect * ae = new AndEffect();
                                econtainer.push_back(ae);
                                }
#line 5466 "generated/parser.cpp"
    break;

  case 270: /* cond_effect: LEFTPAR PDDL_AND $@36 p_effect_list RIGHTPAR  */
#line 2879 "yacc/parser.yy"
                                {
                                AndEffect * ae = (AndEffect *) econtainer.back();
                                econtainer.pop_back();
                                (yyval.otype) = ae;
                                }
#line 5476 "generated/parser.cpp"
    break;

  case 271: /* cond_effect: p_effect  */
#line 2885 "yacc/parser.yy"
                                {(yyval.otype) = (yyvsp[0].otype);}
#line 5482 "generated/parser.cpp"
    break;

  case 272: /* assign_op: PDDL_ASSIGN  */
#line 2889 "yacc/parser.yy"
                                {
                                (yyval.type_int) = (int) FASSIGN;
                                }
#line 5490 "generated/parser.cpp"
    break;

  case 273: /* assign_op: PDDL_SCALE_UP  */
#line 2893 "yacc/parser.yy"
                                {
                                (yyval.type_int) = (int) FSCALEUP;
                                }
#line 5498 "generated/parser.cpp"
    break;

  case 274: /* assign_op: PDDL_SCALE_DOWN  */
#line 2897 "yacc/parser.yy"
                                {
                                (yyval.type_int) = (int) FSCALEDOWN;
                                }
#line 5506 "generated/parser.cpp"
    break;

  case 275: /* assign_op: PDDL_INCREASE  */
#line 2901 "yacc/parser.yy"
                                {
                                (yyval.type_int) = (int) FINCREASE;
                                }
#line 5514 "generated/parser.cpp"
    break;

  case 276: /* assign_op: PDDL_DECREASE  */
#line 2905 "yacc/parser.yy"
                                {
                                (yyval.type_int) = (int) FDECREASE;
                                }
#line 5522 "generated/parser.cpp"
    break;

  case 285: /* $@37: %empty  */
#line 2926 "yacc/parser.yy"
                                     {context = new LDictionary;}
#line 5528 "generated/parser.cpp"
    break;

  case 286: /* problemBody3: init $@37 goal  */
#line 2926 "yacc/parser.yy"
                                                                       {delete context; context=0;}
#line 5534 "generated/parser.cpp"
    break;

  case 289: /* init_el: literal_name  */
#line 2948 "yacc/parser.yy"
                                {
                                parser_api->problem->addToInitialState((LiteralEffect *)(yyvsp[0].otype));
                                //parser_api->problem->getInitialContext()->stateChanges.push_back(new UndoARLiteralState((Literal *)$1,true));
                                }
#line 5543 "generated/parser.cpp"
    break;

  case 290: /* init_el: LEFTPAR EQUAL f_head number RIGHTPAR  */
#line 2953 "yacc/parser.yy"
                                {
                                Function * f = (Function *) (yyvsp[-2].otype);
                                f->setValue((yyvsp[-1].type_number));
                                parser_api->problem->addToInitialState(f);
                                //parser_api->problem->getInitialContext()->stateChanges.push_back(new UndoARLiteralState(f,true));
                                if(!parser_api->domain->errfluents && !parser_api->domain->hasRequirement(":fluents"))
                                    {
                                        parser_api->domain->errfluents = true;
                                        yyerror("Using a clause that requires `:fluents' and is not declared in requirements clause");
                                    }
                                }
#line 5559 "generated/parser.cpp"
    break;

  case 291: /* $@38: %empty  */
#line 2964 "yacc/parser.yy"
                                          {isNumber = false;}
#line 5565 "generated/parser.cpp"
    break;

  case 292: /* init_el: LEFTPAR $@38 number_time_point literal_name RIGHTPAR  */
#line 2965 "yacc/parser.yy"
                                {
                                /* Comprobar que la expresi�n dada por el time specifier
                                * es un n�mero */
                                Evaluable * n = (Evaluable *) (yyvsp[-2].otype);
                                LiteralEffect * l = (LiteralEffect *) (yyvsp[-1].otype);
                                if(!isNumber){
                                        snprintf(parerr,256,"Expecting a number in time initialization: `%s'",l->getName());
                                        yyerror(parerr);
                                }
                                else {
                                        l->setTime(n);
                                }
                                    /*requires timed-initial-literals */
                                if(!parser_api->domain->errdurative && !parser_api->domain->hasRequirement(":durative-actions"))
                                {
                                        parser_api->domain->errdurative = true;
                                        yyerror("Using a clause that requires `:timed-initial-literals' and is not declared in requirements clause");
                                }
                                parser_api->problem->addToInitialState(l);
                                //parser_api->problem->getInitialContext()->stateChanges.push_back(new UndoARLiteralState(l,true));
                                }
#line 5591 "generated/parser.cpp"
    break;

  case 293: /* init_el: LEFTPAR PDDL_BETWEEN number PDDL_AND number optional_repetition literal_name RIGHTPAR  */
#line 2991 "yacc/parser.yy"
                                {
                                LiteralEffect * l = (LiteralEffect *) (yyvsp[-1].otype);
                                TimeLineLiteralEffect * tl = new TimeLineLiteralEffect(l->getId(),l->getMetaId(),l->getParameters(),l->getPolarity());
                                delete l;
                                if(!parser_api->domain->errdurative && !parser_api->domain->hasRequirement(":durative-actions"))
                                {
                                        parser_api->domain->errdurative = true;
                                        yyerror("Using a clause that requires `:timed-initial-literals' and is not declared in requirements clause");
                                }
                                tl->setInterval((int)(yyvsp[-5].type_number),(int)(yyvsp[-3].type_number));
                                tl->setGap((int)(yyvsp[-2].type_number));
                                parser_api->problem->addToInitialState(tl);
                                //parser_api->problem->getInitialContext()->stateChanges.push_back(new UndoARLiteralState(tl,true));
                                (yyval.otype) = 0;
                                }
#line 5611 "generated/parser.cpp"
    break;

  case 294: /* optional_repetition: PDDL_AND_EVERY number  */
#line 3009 "yacc/parser.yy"
                                {
                                if((yyvsp[0].type_number) < 0){
                                        yyerror("Expecting a positive number.");
                                        (yyval.type_number) = 0;
                                }
                                else
                                        (yyval.type_number) = (yyvsp[0].type_number);
                                }
#line 5624 "generated/parser.cpp"
    break;

  case 295: /* optional_repetition: %empty  */
#line 3018 "yacc/parser.yy"
                                {
                                (yyval.type_number) = 0;
                                }
#line 5632 "generated/parser.cpp"
    break;

  case 298: /* goal: LEFTPAR PDDL_GOAL goal_def RIGHTPAR  */
#line 3028 "yacc/parser.yy"
                                { *errflow << "Los goal 'planos' de pddl no est�n soportados." << endl;}
#line 5638 "generated/parser.cpp"
    break;

  case 299: /* goal: LEFTPAR HTN_TASKSGOAL meta_list HTN_TASKS task_network RIGHTPAR  */
#line 3034 "yacc/parser.yy"
                                {
                                parser_api->problem->setInitialGoal((TaskNetwork *)(yyvsp[-1].otype));
                                   if(!parser_api->domain->errhtn && !parser_api->domain->hasRequirement(":htn-expansion"))
                                   {
                                        parser_api->domain->errhtn = true;
                                        yyerror("Using a clause that requires `:htn-expansion' that is not declared in requirements clause");
                                   }
                                if((yyvsp[-3].otype)){
                                TagVector * tv = (TagVector *) (yyvsp[-3].otype);
                                tagv_ite tb, te = tv->end();
                                for(tb = tv->begin();tb!=te;tb++)
                                        parser_api->problem->meta.addTag((*tb));
                                tv->clear();
                                delete tv;
                                }

                                // verificar que todos los objetivos expuestos en
                                // la red de tareas son alcanzables.
                                bool changes=true;
                                while(changes){
                                changes = false;
                                if(!((TaskNetwork *) (yyvsp[-1].otype))->isWellDefined(errflow,&changes))
                                {
                                        snprintf(parerr,256,"In the task network of goal specification.");
                                        yyerror(parerr);
                                }
                                }

                                }
#line 5672 "generated/parser.cpp"
    break;

  case 300: /* literal_name: atomic_formula_name  */
#line 3066 "yacc/parser.yy"
                                {(yyval.otype) = (LiteralEffect *) (yyvsp[0].otype);}
#line 5678 "generated/parser.cpp"
    break;

  case 301: /* literal_name: LEFTPAR PDDL_NOT atomic_formula_name RIGHTPAR  */
#line 3068 "yacc/parser.yy"
                                {
                                LiteralEffect * lit = (LiteralEffect *) (yyvsp[-1].otype);
                                lit->setPolarity(false);
                                (yyval.otype) = lit;
                                }
#line 5688 "generated/parser.cpp"
    break;

  case 302: /* $@39: %empty  */
#line 3076 "yacc/parser.yy"
                                {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                LiteralEffect * lit=0;
                                Meta * mt = 0;
                                // buscamos si el literal ya est� definido en el diccionario de
                                // nombres de literales (deber�a estarlo)
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                lit = new LiteralEffect(posit->second,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                lit = new LiteralEffect(idCounter++,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador = 0;
                                }
#line 5716 "generated/parser.cpp"
    break;

  case 303: /* atomic_formula_name: LEFTPAR term_name $@39 term_list RIGHTPAR  */
#line 3100 "yacc/parser.yy"
                                {
                                LiteralEffect * lit= (LiteralEffect *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                vector<Literal *>::const_iterator j;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     if(unify(lit->getParameters(),(*i).second->getParameters())){
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                        snprintf(parerr,256,"(8) No matching predicate for `%s'.",lit->toString());
                                        yyerror(parerr);
                                        if(candidates.size() > 0) {
                                        *errflow << "Possible candidates:" << endl;
                                          for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                             *errflow << "\t[" << sli.fileName << "]:" << sli.lineNumber;
                                        (*j)->printL(errflow,1);
                                        *errflow << endl;
                                          }
                                        }
                                }
                                (yyval.otype) = lit;
                                }
#line 5755 "generated/parser.cpp"
    break;

  case 304: /* @40: %empty  */
#line 3138 "yacc/parser.yy"
                                {
                                context = new LDictionary;
                                string * name = (string *) (yyvsp[0].otype);
                                PrimitiveTask * priTask=0;
                                Meta * mt = 0;
                                isDurative = true;
                                // buscamos en el diccionario si la acci�n ya tiene un identificador
                                // asociado, en cuyo caso lo reutilizamos
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),name->c_str());
                                      if(posit != (parser_api->domain->ldictionary).end()) {
                                        priTask = new PrimitiveTask(posit->second,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                }
                                      else
                                      {
                                        priTask = new PrimitiveTask(idCounter++,parser_api->domain->metainfo.size());
                                        mt = new Meta(name->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                        parser_api->domain->metainfo.push_back(mt);
                                          (parser_api->domain->ldictionary).insert(make_pair(priTask->getName(),priTask->getId()));
                                      }
                                container = priTask;
                                delete name;
                                (yyval.otype) = priTask;
                                }
#line 5785 "generated/parser.cpp"
    break;

  case 305: /* $@41: %empty  */
#line 3165 "yacc/parser.yy"
                                {
                                    container = 0;
                                    // si hay alg�n tag
                                    if((yyvsp[0].otype)){
                                        TagVector * tv = (TagVector *) (yyvsp[0].otype);
                                        tagv_ite tb, te = tv->end();
                                        int mid = ((PrimitiveTask *) (yyvsp[-5].otype))->getMetaId();
                                        for(tb = tv->begin();tb!=te;tb++){
                                                parser_api->domain->metainfo[mid]->addTag(*tb);
                                        }
                                        tv->clear();
                                        delete tv;
                                    }
                                }
#line 5804 "generated/parser.cpp"
    break;

  case 306: /* $@42: %empty  */
#line 3180 "yacc/parser.yy"
                                {
                                 if((yyvsp[0].otype)){
                                     ((PrimitiveTask *) (yyvsp[-8].otype))->setTConstraints((vector<TCTR> *) (yyvsp[0].otype));
                                 }
                                }
#line 5814 "generated/parser.cpp"
    break;

  case 307: /* durative_action_def: LEFTPAR PDDL_DURATIVE_ACTION term_name @40 PDDL_PARAMETERS LEFTPAR variable_typed_list RIGHTPAR meta_list $@41 PDDL_DURATION pduration_constraints $@42 PDDL_CONDITION goal_def PDDL_EFFECT effect RIGHTPAR  */
#line 3188 "yacc/parser.yy"
                                {
                                 isDurative = false;
                                 PrimitiveTask * priTask= (PrimitiveTask *) (yyvsp[-14].otype);
                                 priTask->setPrecondition((Goal *) (yyvsp[-3].otype));
                                 priTask->setEffect((Effect *) (yyvsp[-1].otype));
                                 parser_api->domain->addTask(priTask);
                                 delete context;
                                 context = 0;
                                 if(!parser_api->domain->errdurative && !parser_api->domain->hasRequirement(":durative-actions")){
                                     parser_api->domain->errdurative = true;
                                     yyerror("Using a clause that requires `:durative-actions' and is not declared in requirements clause");
                                 }
                                }
#line 5832 "generated/parser.cpp"
    break;

  case 308: /* sdur_constraint_list: sdur_constraint  */
#line 3202 "yacc/parser.yy"
                                {
                                vector<pair<int,Evaluable *> > * v = new vector<pair<int,Evaluable *> >;
                                v->push_back(*((pair<int,Evaluable *> *) (yyvsp[0].otype)));
                                (yyval.otype)= v;
                                }
#line 5842 "generated/parser.cpp"
    break;

  case 309: /* sdur_constraint_list: sdur_constraint_list sdur_constraint  */
#line 3208 "yacc/parser.yy"
                                {
                                vector<pair<int,Evaluable *> > * v = (vector<pair<int,Evaluable *> > *) (yyvsp[-1].otype);
                                v->push_back(*((pair<int,Evaluable *> *) (yyvsp[0].otype)));
                                (yyval.otype)= v;
                                }
#line 5852 "generated/parser.cpp"
    break;

  case 310: /* pduration_constraints: sdur_constraint  */
#line 3216 "yacc/parser.yy"
                                {
                                 vector<TCTR> * v = new vector<TCTR>;
                                 TCTR * ele = (TCTR *) (yyvsp[0].otype);
                                 v->push_back(*ele);
                                 (yyval.otype)= v;
                                }
#line 5863 "generated/parser.cpp"
    break;

  case 311: /* pduration_constraints: LEFTPAR PDDL_AND sdur_constraint_list RIGHTPAR  */
#line 3223 "yacc/parser.yy"
                                {
                                 vector<TCTR> * v = (vector<TCTR> *) (yyvsp[-1].otype);
                                 (yyval.otype)= v;
                                }
#line 5872 "generated/parser.cpp"
    break;

  case 312: /* pduration_constraints: LEFTPAR RIGHTPAR  */
#line 3228 "yacc/parser.yy"
                                {
                                 vector<TCTR> * v = new vector<TCTR>;
                                 (yyval.otype)= v;
                                }
#line 5881 "generated/parser.cpp"
    break;

  case 313: /* time_specifier: time_point  */
#line 3234 "yacc/parser.yy"
                                {
                                TimeInterval * ti = new TimeInterval();
                                ti->setStart((Evaluable *)(yyvsp[0].otype));
                                (yyval.otype) = ti;
                                }
#line 5891 "generated/parser.cpp"
    break;

  case 314: /* time_specifier: PDDL_OVERALL  */
#line 3240 "yacc/parser.yy"
                                {
                                TimeInterval * ti = new TimeInterval();
                                ti->setStart((double)ATSTART);
                                ti->setEnd((double)ATEND);
                                (yyval.otype) = ti;
                                }
#line 5902 "generated/parser.cpp"
    break;

  case 315: /* time_specifier: PDDL_BETWEEN time_point PDDL_AND time_point  */
#line 3247 "yacc/parser.yy"
                                {
                                TimeInterval * ti = new TimeInterval();
                                ti->setStart((Evaluable *)(yyvsp[-2].otype));
                                ti->setEnd((Evaluable *)(yyvsp[0].otype));
                                (yyval.otype) = ti;
                                isNumber = false;
                                }
#line 5914 "generated/parser.cpp"
    break;

  case 316: /* time_point: PDDL_ATSTART  */
#line 3257 "yacc/parser.yy"
                                {
                                (yyval.otype) = new FluentNumber((double)ATSTART);
                                }
#line 5922 "generated/parser.cpp"
    break;

  case 317: /* time_point: PDDL_ATEND  */
#line 3261 "yacc/parser.yy"
                                {
                                (yyval.otype) = new FluentNumber((double)ATEND);
                                }
#line 5930 "generated/parser.cpp"
    break;

  case 318: /* time_point: number_time_point  */
#line 3265 "yacc/parser.yy"
                                { (yyval.otype) = (yyvsp[0].otype);}
#line 5936 "generated/parser.cpp"
    break;

  case 319: /* $@43: %empty  */
#line 3268 "yacc/parser.yy"
                                  {AtExpected = true;}
#line 5942 "generated/parser.cpp"
    break;

  case 320: /* $@44: %empty  */
#line 3268 "yacc/parser.yy"
                                                               {AtExpected = false;}
#line 5948 "generated/parser.cpp"
    break;

  case 321: /* number_time_point: $@43 PDDL_AT $@44 fluent_exp  */
#line 3269 "yacc/parser.yy"
                                {
                                Evaluable * c = (Evaluable *) (yyvsp[0].otype);
                                const Type * number = parser_api->domain->getType("number");
                                if(!c->isType(number)) {
                                snprintf(parerr,256,"Expression `%s' is not numeric.",c->toStringEvaluable());
                                yyerror(parerr);
                                }
                                (yyval.otype) = c;
                                }
#line 5962 "generated/parser.cpp"
    break;

  case 322: /* $@45: %empty  */
#line 3281 "yacc/parser.yy"
                                {
                                context = new LDictionary;
                                }
#line 5970 "generated/parser.cpp"
    break;

  case 323: /* derived_def: LEFTPAR PDDL_DERIVED $@45 derived_body RIGHTPAR  */
#line 3285 "yacc/parser.yy"
                                {

                                delete context;
                                context = 0;
                                }
#line 5980 "generated/parser.cpp"
    break;

  case 324: /* derived_body: derived_formula_skeleton goal_def  */
#line 3293 "yacc/parser.yy"
                                {

                                if((yyvsp[-1].otype))
                                {
                                        Axiom * a = (Axiom *) (yyvsp[-1].otype);
                                        if((yyvsp[0].otype))
                                        a->setGoal((Goal *)(yyvsp[0].otype));
                                }
                                else
                                {
                                        if((yyvsp[0].otype))
                                        delete (Goal *) (yyvsp[0].otype);
                                }
                                }
#line 5999 "generated/parser.cpp"
    break;

  case 325: /* derived_body: derived_formula_skeleton code  */
#line 3308 "yacc/parser.yy"
                                {

                                if((yyvsp[-1].otype))
                                {
                                        Axiom * a = (Axiom *) (yyvsp[-1].otype);
                                        if((yyvsp[0].type_string)){
                                        if(!a->setCode((yyvsp[0].type_string))){
                                                snprintf(parerr,256,"Error in Python script code. Axiom: %s.",a->getName());
                                                yyerror(parerr);
                                        }
                                        }
                                }
                                }
#line 6017 "generated/parser.cpp"
    break;

  case 326: /* $@46: %empty  */
#line 3325 "yacc/parser.yy"
                                   {inDebugContext=true;}
#line 6023 "generated/parser.cpp"
    break;

  case 327: /* $@47: %empty  */
#line 3325 "yacc/parser.yy"
                                                                            {inDebugContext=false;}
#line 6029 "generated/parser.cpp"
    break;

  case 328: /* debug_sentence: $@46 DBG_DEBUG command $@47  */
#line 3326 "yacc/parser.yy"
                        {
                                YYACCEPT;
                        }
#line 6037 "generated/parser.cpp"
    break;

  case 329: /* debug_sentence: error  */
#line 3330 "yacc/parser.yy"
                        {
                                YYABORT;
                        }
#line 6045 "generated/parser.cpp"
    break;

  case 330: /* command: DBG_QUIT  */
#line 3336 "yacc/parser.yy"
                            {
                                exit(EXIT_SUCCESS);
                            }
#line 6053 "generated/parser.cpp"
    break;

  case 332: /* command: DBG_CONTINUE  */
#line 3341 "yacc/parser.yy"
                            {
                                debugger->cont = true;
                            }
#line 6061 "generated/parser.cpp"
    break;

  case 342: /* command: DBG_NEXT  */
#line 3354 "yacc/parser.yy"
                            {
                                debugger->next = true;
                            }
#line 6069 "generated/parser.cpp"
    break;

  case 343: /* command: DBG_NEXP  */
#line 3358 "yacc/parser.yy"
                            {
                                debugger->nexp = true;
                            }
#line 6077 "generated/parser.cpp"
    break;

  case 344: /* command: DBG_MEM  */
#line 3362 "yacc/parser.yy"
                            {
                                struct mallinfo myinfo=mallinfo();
                                cerr << "Memory allocated (bytes): " << myinfo.hblkhd << " Memory chunks occupied: " << myinfo.uordblks << endl;
                            }
#line 6086 "generated/parser.cpp"
    break;

  case 345: /* command: DBG_SELECT PDDL_DNUMBER  */
#line 3367 "yacc/parser.yy"
                            {
                                debugger->select((int)(yyvsp[0].type_number));
                            }
#line 6094 "generated/parser.cpp"
    break;

  case 346: /* command: DBG_VERBOSE DBG_ON  */
#line 3371 "yacc/parser.yy"
                            {
                                current_plan->FLAG_VERBOSE = 1;
                            }
#line 6102 "generated/parser.cpp"
    break;

  case 347: /* command: DBG_VERBOSE DBG_OFF  */
#line 3375 "yacc/parser.yy"
                            {
                                current_plan->FLAG_VERBOSE = 0;
                            }
#line 6110 "generated/parser.cpp"
    break;

  case 348: /* help: DBG_HELP  */
#line 3381 "yacc/parser.yy"
                            {
                                cerr << "Type `help <command>' to obtain detailed information about a command." << endl;
                                cerr << "Avaliable commands:" <<endl;
                                cerr << "print          display        quit           plot"<<endl;
                                cerr << "continue       undisplay      next           set" <<endl;
                                cerr << "describe       break          disable        enable"<<endl;
                                cerr << "nexp           eval           watch          apply"<<endl;
                                cerr << "<enter> executes the last command." << endl;
                            }
#line 6124 "generated/parser.cpp"
    break;

  case 349: /* help: DBG_HELP DBG_CONTINUE  */
#line 3391 "yacc/parser.yy"
                            {
                                cerr << "Command: `continue'. Shortcut: `c'" << endl << endl;
                                cerr << "Description: Continues the execution until a breakpoint or the end of the program is reached." << endl;
                                cerr << "See also: `next'" << endl;
                            }
#line 6134 "generated/parser.cpp"
    break;

  case 350: /* help: DBG_HELP DBG_QUIT  */
#line 3397 "yacc/parser.yy"
                            {
                                cerr << "Command: `quit' or `exit'" << endl << endl;
                                cerr << "Description: Terminates the program execution." << endl;
                            }
#line 6143 "generated/parser.cpp"
    break;

  case 351: /* help: DBG_HELP DBG_PRINT  */
#line 3402 "yacc/parser.yy"
                            {
                                cerr << "Command: `print'. Shortcut: `p'" << endl << endl;
                                cerr << "Description: Prints information about the planning context." << endl;
                                cerr << "\t`print state':\tPrints the current state." << endl;
                                cerr << "\t`print agenda':\tPrints the current agenda." << endl;
                                cerr << "\t`print plan':\tPrints the ongoing plan." << endl;
                                cerr << "\t`print options':\tPrints the options you can peform on next step." << endl;
                                cerr << "\t`print termtable':\tPrints the internal term table." << endl;
                                cerr << "\t`print tasks':\tPrints all the tasks defined in the domain." << endl;
                                cerr << "\t`print predicates':\tPrints all the avaliable predicates defined in the domain." << endl;
                                cerr << "\t`print <predicate-expression>':\tPrints all the predicates in the current state, or the tasks in current plan, that match the given expression." << endl;
                            }
#line 6160 "generated/parser.cpp"
    break;

  case 352: /* help: DBG_HELP DBG_DISPLAY  */
#line 3415 "yacc/parser.yy"
                            {
                                cerr << "Command: `display'. Shortcut `d'." << endl << endl;
                                cerr << "Description: Display information about the current planning context every step until is undisplayed." << endl;
                                cerr << "\t`display':\tShows information about the current displays." << endl;
                                cerr << "\t`display <number>':\tActivates the display of given number." << endl;
                                cerr << "\t`display state':\tDisplays the current state." << endl;
                                cerr << "\t`display agenda':\tDisplays the current agenda." << endl;
                                cerr << "\t`display plan':\tDisplays the ongoing plan." << endl;
                                cerr << "\t`display termtable':\tDisplays the internal term table." << endl;
                                cerr << "\t`display <predicate-expression>':\tDisplays all the predicates in the current state, or the tasks in current plan, that match the given expression." << endl;
                                cerr << "See also: `print', `undisplay'" << endl;
                            }
#line 6177 "generated/parser.cpp"
    break;

  case 353: /* help: DBG_HELP DBG_UNDISPLAY  */
#line 3428 "yacc/parser.yy"
                            {
                                cerr << "Command: `undisplay <number>'." << endl << endl;
                                cerr << "Description: Deactivates the display of given number." << endl;
                        }
#line 6186 "generated/parser.cpp"
    break;

  case 354: /* help: DBG_HELP DBG_NEXT  */
#line 3433 "yacc/parser.yy"
                            {
                                cerr << "Command: `next'. ShortCut: `n'" << endl << endl;
                                cerr << "Description: Advance one more step." << endl;
                                cerr << "See also: `continue'" << endl;
                        }
#line 6196 "generated/parser.cpp"
    break;

  case 355: /* help: DBG_HELP DBG_NEXP  */
#line 3439 "yacc/parser.yy"
                            {
                                cerr << "Command: `nexp' (next expansion). ShortCut: `ne'" << endl << endl;
                                cerr << "Description: Advance until a new task is chosen." << endl;
                                cerr << "See also: `continue', `next'" << endl;
                        }
#line 6206 "generated/parser.cpp"
    break;

  case 356: /* help: DBG_HELP DBG_PLOT  */
#line 3445 "yacc/parser.yy"
                            {
                                cerr << "Command: `plot'." << endl << endl;
                                cerr << "Description: Graphically shows information about the current plan." << endl;
                                cerr << "You need to have installed the 'dot' program avaliable at http://www.graphviz.org." << endl;
                                cerr << "You also need to correct set up some environment variables." << endl;
                                cerr << "\t`plot plan':\tShows the current plan graph." << endl;
                                cerr << "\t`plot causal':\tShows the graph of the causal link structure in the plan." << endl;
                                cerr << "See also: `set'" << endl;
                        }
#line 6220 "generated/parser.cpp"
    break;

  case 357: /* help: DBG_HELP DBG_SET  */
#line 3455 "yacc/parser.yy"
                            {
                                cerr << "Command: `set'." << endl << endl;
                                cerr << "Description: Sets some environment variables." << endl;
                                cerr << "\t`set <variable>':\tShows the current value of the given variable." << endl;
                                cerr << "\t`set <variable> = <value>':\tSets a new value for the given variable." << endl;
                                cerr << "\tAvaliable variables:" << endl;
                                cerr << "\t\t`verbosity: Level of verbosity (0=nothing,1=shy,2=normal(default),3=promiscuous)." << endl;
                                cerr << "\t\t`viewer: Path to a program able to display png format images." << endl;
                                cerr << "\t\t`tmpdir: Directory to store temporary information." << endl;
                                cerr << "\t\t`dotpath: Path to the dot program." << endl;
                                cerr << "See also: `plot'" << endl;
                        }
#line 6237 "generated/parser.cpp"
    break;

  case 358: /* help: DBG_HELP DBG_DESCRIBE  */
#line 3468 "yacc/parser.yy"
                            {
                                cerr << "Command: `describe'." << endl << endl;
                                cerr << "Description: Shows detailed information about a structure defined in the domain." << endl;
                                cerr << "\t`describe <predicate-expression>':\tPrint the description in the domain relative to the predicate expression. It can be a predicate or a task." << endl;
                                cerr << "See also: `print', `display'" << endl;
                            }
#line 6248 "generated/parser.cpp"
    break;

  case 359: /* help: DBG_HELP DBG_ENABLE  */
#line 3475 "yacc/parser.yy"
                            {
                                cerr << "Command: `enable <number>'." << endl << endl;
                                cerr << "Description: Reactivates a previously disabled breakpoint or watch." << endl;
                                cerr << "<number> is de id of the breakpoint or watch to enable." << endl;
                                cerr << "See also: `break', `watch', `disable'." << endl;
                            }
#line 6259 "generated/parser.cpp"
    break;

  case 360: /* help: DBG_HELP DBG_DISABLE  */
#line 3482 "yacc/parser.yy"
                            {
                                cerr << "Command: `disable <number>'." << endl << endl;
                                cerr << "Description: Deactivates a breakpoint or watch." << endl;
                                cerr << "<number> is de id of the breakpoint or watch to disable." << endl;
                                cerr << "See also: `break', `watch', `enable'." << endl;
                            }
#line 6270 "generated/parser.cpp"
    break;

  case 361: /* help: DBG_HELP DBG_WATCH  */
#line 3489 "yacc/parser.yy"
                            {
                                cerr << "Command: `watch <precondition>'. Shortcut `s'" << endl << endl;
                                cerr << "Description: Defines a condition where the debugger will stop." << endl;
                                cerr << "If ithe watch is enabled, the debugger will stop every time the condition produce one or more valid unifications." << endl;
                                cerr << "See also: `break', `disable', `enable'." << endl;
                            }
#line 6281 "generated/parser.cpp"
    break;

  case 362: /* help: DBG_HELP DBG_BREAKPOINT  */
#line 3496 "yacc/parser.yy"
                            {
                                cerr << "Command: `break'. Shortcut `b'" << endl << endl;
                                cerr << "Description: Manages the stablished breakpoints." << endl;
                                cerr << "\t`break':\tLists all defined breakpoints." << endl;
                                cerr << "\t`break <number>':\tPrints breakpoint whith given id." << endl;
                                cerr << "\t`break <predicate>':\tDefines a new breakpoint. <predcate> can be a task definition or a simple predicate." << endl;
                                cerr << "See also: `watch', `disable', `enable'." << endl;
                            }
#line 6294 "generated/parser.cpp"
    break;

  case 363: /* help: DBG_HELP DBG_EVAL  */
#line 3505 "yacc/parser.yy"
                            {
                                cerr << "Command: `eval <precondition>'." << endl << endl;
                                cerr << "Description: Evaluates the given expression and prints the produced unifications." << endl;
                            }
#line 6303 "generated/parser.cpp"
    break;

  case 364: /* help: DBG_HELP DBG_APPLY  */
#line 3510 "yacc/parser.yy"
                            {
                                cerr << "Command: `apply <effect>'." << endl << endl;
                                cerr << "Description: Applies the given effect." << endl;
                                cerr << "Be cautious with this command is dangerous." << endl;
                                cerr << "See also: `eval'." << endl;
                            }
#line 6314 "generated/parser.cpp"
    break;

  case 365: /* print: DBG_PRINT DBG_STATE  */
#line 3519 "yacc/parser.yy"
                            {
                                debugger->printState();
                            }
#line 6322 "generated/parser.cpp"
    break;

  case 366: /* $@48: %empty  */
#line 3522 "yacc/parser.yy"
                                        {inDebugContext=false;context=new LDictionary();}
#line 6328 "generated/parser.cpp"
    break;

  case 367: /* $@49: %empty  */
#line 3522 "yacc/parser.yy"
                                                                                                                   {inDebugContext=true; delete context; context=0;}
#line 6334 "generated/parser.cpp"
    break;

  case 368: /* print: DBG_PRINT $@48 simple_formula_term_goal $@49  */
#line 3523 "yacc/parser.yy"
                            {
                                LiteralGoal * lg = (LiteralGoal *) (yyvsp[-1].otype);
                                if((yyvsp[-1].otype)){
                                debugger->printLiteral(lg);
                                delete lg;
                                }
                            }
#line 6346 "generated/parser.cpp"
    break;

  case 369: /* print: DBG_PRINT DBG_AGENDA  */
#line 3531 "yacc/parser.yy"
                            {
                                debugger->printAgenda();
                            }
#line 6354 "generated/parser.cpp"
    break;

  case 370: /* print: DBG_PRINT DBG_PLAN  */
#line 3535 "yacc/parser.yy"
                            {
                                debugger->printPlan();
                            }
#line 6362 "generated/parser.cpp"
    break;

  case 371: /* print: DBG_PRINT DBG_OPTIONS  */
#line 3539 "yacc/parser.yy"
                            {
                                debugger->printOptions();
                            }
#line 6370 "generated/parser.cpp"
    break;

  case 372: /* print: DBG_PRINT DBG_TERMTABLE  */
#line 3543 "yacc/parser.yy"
                            {
                                debugger->printTermtable();
                            }
#line 6378 "generated/parser.cpp"
    break;

  case 373: /* print: DBG_PRINT DBG_TASKS  */
#line 3547 "yacc/parser.yy"
                        {
                                debugger->printTasks();
                        }
#line 6386 "generated/parser.cpp"
    break;

  case 374: /* print: DBG_PRINT DBG_PREDICATES  */
#line 3551 "yacc/parser.yy"
                        {
                                debugger->printPredicates();
                        }
#line 6394 "generated/parser.cpp"
    break;

  case 375: /* display: DBG_DISPLAY DBG_STATE  */
#line 3557 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                de->name = "state";
                                debugger->displaySymbol(de);
                            }
#line 6404 "generated/parser.cpp"
    break;

  case 376: /* $@50: %empty  */
#line 3562 "yacc/parser.yy"
                                          {inDebugContext=false;context= new LDictionary();}
#line 6410 "generated/parser.cpp"
    break;

  case 377: /* $@51: %empty  */
#line 3562 "yacc/parser.yy"
                                                                                                                      {inDebugContext=true; delete context; context=0;}
#line 6416 "generated/parser.cpp"
    break;

  case 378: /* display: DBG_DISPLAY $@50 simple_formula_term_goal $@51  */
#line 3563 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                if((yyvsp[-1].otype)){
                                de->goal = (LiteralGoal *) (yyvsp[-1].otype);
                                debugger->displaySymbol(de);
                                }
                                else
                                delete de;
                            }
#line 6430 "generated/parser.cpp"
    break;

  case 379: /* display: DBG_DISPLAY DBG_AGENDA  */
#line 3573 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                de->name = "agenda";
                                debugger->displaySymbol(de);
                            }
#line 6440 "generated/parser.cpp"
    break;

  case 380: /* display: DBG_DISPLAY DBG_PLAN  */
#line 3579 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                de->name = "plan";
                                debugger->displaySymbol(de);
                            }
#line 6450 "generated/parser.cpp"
    break;

  case 381: /* display: DBG_DISPLAY  */
#line 3585 "yacc/parser.yy"
                            {
                                debugger->printDisplays();
                            }
#line 6458 "generated/parser.cpp"
    break;

  case 382: /* display: DBG_DISPLAY PDDL_DNUMBER  */
#line 3589 "yacc/parser.yy"
                            {
                                debugger->display((int)(yyvsp[0].type_number));
                            }
#line 6466 "generated/parser.cpp"
    break;

  case 383: /* display: DBG_DISPLAY DBG_TERMTABLE  */
#line 3593 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                de->name = "termtable";
                                debugger->displaySymbol(de);
                            }
#line 6476 "generated/parser.cpp"
    break;

  case 384: /* plot: DBG_PLOT DBG_PLAN  */
#line 3601 "yacc/parser.yy"
                            {
                                debugger->plotPlan();
                            }
#line 6484 "generated/parser.cpp"
    break;

  case 385: /* plot: DBG_PLOT DBG_CAUSAL  */
#line 3605 "yacc/parser.yy"
                            {
                                debugger->plotCausal();
                            }
#line 6492 "generated/parser.cpp"
    break;

  case 386: /* undisplay: DBG_UNDISPLAY PDDL_DNUMBER  */
#line 3610 "yacc/parser.yy"
                            {
                                debugger->undisplay((int)(yyvsp[0].type_number));
                            }
#line 6500 "generated/parser.cpp"
    break;

  case 387: /* set: DBG_SET DBG_VIEWER  */
#line 3617 "yacc/parser.yy"
                            {
                                cerr << debugger->viewerCommand << endl;
                            }
#line 6508 "generated/parser.cpp"
    break;

  case 388: /* set: DBG_SET DBG_VIEWER EQUAL DBG_PATH  */
#line 3621 "yacc/parser.yy"
                            {
                                debugger->viewerCommand = (yyvsp[0].type_string);
                            }
#line 6516 "generated/parser.cpp"
    break;

  case 389: /* set: DBG_SET DBG_TMPDIR  */
#line 3625 "yacc/parser.yy"
                            {
                                cerr << debugger->tmpdir << endl;
                            }
#line 6524 "generated/parser.cpp"
    break;

  case 390: /* set: DBG_SET DBG_TMPDIR EQUAL DBG_PATH  */
#line 3629 "yacc/parser.yy"
                            {
                                debugger->tmpdir = (yyvsp[0].type_string);
                            }
#line 6532 "generated/parser.cpp"
    break;

  case 391: /* set: DBG_SET DBG_DOTPATH  */
#line 3633 "yacc/parser.yy"
                            {
                                cerr << debugger->dotPath << endl;
                            }
#line 6540 "generated/parser.cpp"
    break;

  case 392: /* set: DBG_SET DBG_DOTPATH EQUAL DBG_PATH  */
#line 3637 "yacc/parser.yy"
                            {
                                debugger->dotPath = (yyvsp[0].type_string);
                            }
#line 6548 "generated/parser.cpp"
    break;

  case 393: /* set: DBG_SET DBG_VERBOSITY  */
#line 3641 "yacc/parser.yy"
                        {
                                cerr << current_plan->FLAG_VERBOSE << endl;
                        }
#line 6556 "generated/parser.cpp"
    break;

  case 394: /* set: DBG_SET DBG_VERBOSITY EQUAL PDDL_DNUMBER  */
#line 3645 "yacc/parser.yy"
                        {
                                if((yyvsp[0].type_number) >= 0 && (yyvsp[0].type_number) <= 3)
                                current_plan->FLAG_VERBOSE = (int) (yyvsp[0].type_number);
                        }
#line 6565 "generated/parser.cpp"
    break;

  case 395: /* breakpoint: DBG_BREAKPOINT  */
#line 3652 "yacc/parser.yy"
                            {
                                debugger->printBreakpoints();
                            }
#line 6573 "generated/parser.cpp"
    break;

  case 396: /* $@52: %empty  */
#line 3655 "yacc/parser.yy"
                                        {inDebugContext=false;context= new LDictionary();}
#line 6579 "generated/parser.cpp"
    break;

  case 397: /* $@53: %empty  */
#line 3655 "yacc/parser.yy"
                                                                                                    {inDebugContext=true;delete context; context=0;}
#line 6585 "generated/parser.cpp"
    break;

  case 398: /* breakpoint: DBG_WATCH $@52 goal_def $@53  */
#line 3656 "yacc/parser.yy"
                            {
                                DisplayElement * de = new DisplayElement();
                                de->goal = (Goal *) (yyvsp[-1].otype);
                                debugger->setBreakpoint(de);
                            }
#line 6595 "generated/parser.cpp"
    break;

  case 399: /* breakpoint: DBG_BREAKPOINT PDDL_DNUMBER  */
#line 3662 "yacc/parser.yy"
                            {
                                debugger->printBreakpoint((int)(yyvsp[0].type_number));
                            }
#line 6603 "generated/parser.cpp"
    break;

  case 400: /* breakpoint: DBG_ENABLE PDDL_DNUMBER  */
#line 3666 "yacc/parser.yy"
                        {
                                debugger->enableBreakpoint((int) (yyvsp[0].type_number));
                        }
#line 6611 "generated/parser.cpp"
    break;

  case 401: /* breakpoint: DBG_DISABLE PDDL_DNUMBER  */
#line 3670 "yacc/parser.yy"
                        {
                                debugger->disableBreakpoint((int) (yyvsp[0].type_number));
                        }
#line 6619 "generated/parser.cpp"
    break;

  case 402: /* $@54: %empty  */
#line 3673 "yacc/parser.yy"
                                             {inDebugContext=false;context= new LDictionary();}
#line 6625 "generated/parser.cpp"
    break;

  case 403: /* $@55: %empty  */
#line 3673 "yacc/parser.yy"
                                                                                                                                   {inDebugContext=true; delete context; context=0;}
#line 6631 "generated/parser.cpp"
    break;

  case 404: /* breakpoint: DBG_BREAKPOINT $@54 simple_formula_term_goal met_name $@55  */
#line 3674 "yacc/parser.yy"
                        {
                                DisplayElement * de = new DisplayElement();
                                de->goal = (Goal *) (yyvsp[-2].otype);
                                if((yyvsp[-2].otype)){
                                if((yyvsp[-1].otype)){
                                        de->name = *((string *) (yyvsp[-1].otype));
                                        delete (string *) (yyvsp[-1].otype);
                                }
                                debugger->setBreakpoint(de);
                                }
                                else{
                                delete de;
                                }
                        }
#line 6650 "generated/parser.cpp"
    break;

  case 405: /* met_name: %empty  */
#line 3691 "yacc/parser.yy"
                        {
                                (yyval.otype) = 0;
                        }
#line 6658 "generated/parser.cpp"
    break;

  case 406: /* met_name: PDDL_NAME  */
#line 3695 "yacc/parser.yy"
                        {
                                (yyval.otype) = new string((yyvsp[0].type_string));
                        }
#line 6666 "generated/parser.cpp"
    break;

  case 407: /* $@56: %empty  */
#line 3699 "yacc/parser.yy"
                                          {inDebugContext=false;context= new LDictionary();}
#line 6672 "generated/parser.cpp"
    break;

  case 408: /* $@57: %empty  */
#line 3699 "yacc/parser.yy"
                                                                                                      {inDebugContext=true;delete context; context=0;}
#line 6678 "generated/parser.cpp"
    break;

  case 409: /* eval: DBG_EVAL $@56 goal_def $@57  */
#line 3700 "yacc/parser.yy"
                            {
                                debugger->eval((Goal *) (yyvsp[-1].otype));
                                if((yyvsp[-1].otype))
                                delete (Goal *) (yyvsp[-1].otype);
                            }
#line 6688 "generated/parser.cpp"
    break;

  case 410: /* $@58: %empty  */
#line 3707 "yacc/parser.yy"
                                            {inDebugContext=false;context= new LDictionary();}
#line 6694 "generated/parser.cpp"
    break;

  case 411: /* $@59: %empty  */
#line 3707 "yacc/parser.yy"
                                                                                                      {inDebugContext=true;delete context; context=0;}
#line 6700 "generated/parser.cpp"
    break;

  case 412: /* apply: DBG_APPLY $@58 effect $@59  */
#line 3708 "yacc/parser.yy"
                            {
                                debugger->apply((Effect *) (yyvsp[-1].otype));
                                if((yyvsp[-1].otype))
                                delete (Effect *) (yyvsp[-1].otype);
                            }
#line 6710 "generated/parser.cpp"
    break;

  case 413: /* $@60: %empty  */
#line 3716 "yacc/parser.yy"
                                         {inDebugContext=false;context = new LDictionary();}
#line 6716 "generated/parser.cpp"
    break;

  case 414: /* $@61: %empty  */
#line 3716 "yacc/parser.yy"
                                                                                                                      {inDebugContext=true; delete context; context=0;}
#line 6722 "generated/parser.cpp"
    break;

  case 415: /* describe: DBG_DESCRIBE $@60 simple_formula_term_goal $@61  */
#line 3717 "yacc/parser.yy"
                            {

                                DisplayElement * de = new DisplayElement();
                                de->goal = (LiteralGoal *) (yyvsp[-1].otype);
                                if((yyvsp[-1].otype)){
                                debugger->describeSymbol(de);
                                }
                                delete de;
                            }
#line 6736 "generated/parser.cpp"
    break;

  case 416: /* $@62: %empty  */
#line 3729 "yacc/parser.yy"
                        {
                                string * nameLit = (string *) (yyvsp[0].otype);
                                LiteralGoal * lit=0;
                                Meta * mt = 0;
                                // buscamos si el literal ya est� definido en el diccionario de
                                // nombres de literales (deber�a estarlo)
                                ldictionaryit posit = SearchDictionary(&(parser_api->domain->ldictionary),nameLit->c_str());
                                if(posit != (parser_api->domain->ldictionary).end()) {
                                lit = new LiteralGoal(posit->second,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                }
                                else
                                {
                                snprintf(parerr,256,"Undefined name: `%s'.",nameLit->c_str());
                                yyerror(parerr);
                                lit = new LiteralGoal(idCounter,parser_api->domain->metainfo.size());
                                mt = new Meta(nameLit->c_str(),lexer->getLineNumber(),parser_api->fileid);
                                parser_api->domain->metainfo.push_back(mt);
                                (parser_api->domain->ldictionary).insert(make_pair(lit->getName(), lit->getId()));
                                }
                                container = lit;
                                delete nameLit;
                                contador = 0;
                                }
#line 6766 "generated/parser.cpp"
    break;

  case 417: /* simple_formula_term_goal: LEFTPAR term_name $@62 term_list RIGHTPAR  */
#line 3755 "yacc/parser.yy"
                                {
                                LiteralGoal * lit= (LiteralGoal *) container;
                                container = 0;
                                // comprobaciones de correctitud
                                // busco en el dominio los literales con el nombre capturado
                                  // y el n�mero de argumentos adecuado
                                  // Esto sirve para poner los tipos seg�n est�n definidos en la tabla de literales.
                                int id = SearchDictionary(&(parser_api->domain->ldictionary),lit->getName())->second;
                                  LiteralTableRange r = parser_api->domain->getLiteralRange(id);
                                bool unificacion=false;
                                vector<Literal *> candidates;
                                  for(literaltablecit i = r.first; i != r.second && !unificacion; i++)
                                  {
                                candidates.push_back((*i).second);
                                     if(unify((*i).second->getParameters(),lit->getParameters())){
                                        unificacion=true;
                                     }
                                  }
                                  TaskTableRange tr = parser_api->domain->getTaskRange(id);
                                vector<Task *> candidates2;
                                  for(tasktablecit k = tr.first; k != tr.second && !unificacion; k++)
                                  {
                                candidates2.push_back((*k).second);
                                     if(unify((*k).second->getParameters(),lit->getParameters())){
                                        unificacion=true;
                                     }
                                  }
                                if(!unificacion){
                                snprintf(parerr,256,"No matching predicate or action for: `%s'.",lit->toString());
                                yyerror(parerr);
                                if(candidates.size() > 0) {
                                        *errflow << "Possible candidate predicates:" << endl;
                                        vector<Literal *>::const_iterator j;
                                        for(j=candidates.begin();j!=candidates.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                        (*j)->printL(errflow,0);
                                        *errflow << endl;
                                        }
                                }
                                if(candidates2.size() > 0) {
                                        *errflow << "Possible candidate tasks:" << endl;
                                        vector<Task *>::const_iterator j;
                                        for(j=candidates2.begin();j!=candidates2.end();j++) {
                                        SearchLineInfo sli((*j)->getMetaId());
                                        (*j)->printHead(errflow);
                                        *errflow << endl;
                                        }
                                }
                                delete lit;
                                lit = 0;
                                }
                                (yyval.otype) = lit;
                                }
#line 6824 "generated/parser.cpp"
    break;

  case 423: /* customization_element: LEFTPAR EQUAL TIMEUNIT time_unit RIGHTPAR  */
#line 3822 "yacc/parser.yy"
                                {
                                parser_api->setFlagTUnit((TimeUnit) (yyvsp[-1].type_number));
                                }
#line 6832 "generated/parser.cpp"
    break;

  case 424: /* customization_element: LEFTPAR EQUAL TIMEFORMAT HTN_TEXT RIGHTPAR  */
#line 3826 "yacc/parser.yy"
                                {
                                parser_api->setTFormat((yyvsp[-1].type_string));
                                }
#line 6840 "generated/parser.cpp"
    break;

  case 425: /* customization_element: LEFTPAR EQUAL TIMEHORIZON PDDL_DNUMBER RIGHTPAR  */
#line 3830 "yacc/parser.yy"
                                {
                                parser_api->setMTHorizon((int) rint((yyvsp[-1].type_number)));
                                }
#line 6848 "generated/parser.cpp"
    break;

  case 426: /* customization_element: LEFTPAR EQUAL RELTIMEHORIZON PDDL_DNUMBER RIGHTPAR  */
#line 3834 "yacc/parser.yy"
                                {
                                parser_api->setRTHorizon((int) rint((yyvsp[-1].type_number)));
                                }
#line 6856 "generated/parser.cpp"
    break;

  case 427: /* customization_element: LEFTPAR EQUAL TIMESTART PDDL_DNUMBER RIGHTPAR  */
#line 3838 "yacc/parser.yy"
                                {
                                if(parser_api->getTStart() != 0){
                                        snprintf(parerr,256,":time-start redefinition.");
                                        yyerror(parerr);
                                }
                                parser_api->setTStart((time_t) (yyvsp[-1].type_number));
                                }
#line 6868 "generated/parser.cpp"
    break;

  case 428: /* python_init: LEFTPAR PYTHON_INIT code RIGHTPAR  */
#line 3847 "yacc/parser.yy"
                                {
#ifdef PYTHON_FOUND
                                if(parser_api->wpython.loadStr((yyvsp[-1].type_string))){
                                        yyerror("While parsing :pyinit.");
                                }
#else
                                yyerror("Parser compiled without Python support. Install python and recompile.");
#endif
                                }
#line 6882 "generated/parser.cpp"
    break;

  case 429: /* time_unit: THOURS  */
#line 3858 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_HOURS;
                                }
#line 6890 "generated/parser.cpp"
    break;

  case 430: /* time_unit: TMINUTES  */
#line 3862 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_MINUTES;
                                }
#line 6898 "generated/parser.cpp"
    break;

  case 431: /* time_unit: TSECONDS  */
#line 3866 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_SECONDS;
                                }
#line 6906 "generated/parser.cpp"
    break;

  case 432: /* time_unit: TDAYS  */
#line 3870 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_DAYS;
                                }
#line 6914 "generated/parser.cpp"
    break;

  case 433: /* time_unit: TYEARS  */
#line 3874 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_YEARS;
                                }
#line 6922 "generated/parser.cpp"
    break;

  case 434: /* time_unit: TMONTHS  */
#line 3878 "yacc/parser.yy"
                                {
                                (yyval.type_number) = TU_MONTHS;
                                }
#line 6930 "generated/parser.cpp"
    break;


#line 6934 "generated/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 3882 "yacc/parser.yy"

