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
#line 1 "Easylang.y"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "generador.h"

void yyerror(char *mensaje);
int yylex();

#line 81 "Easylang.tab.c"

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

#include "Easylang.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ALLOCATE = 3,                   /* ALLOCATE  */
  YYSYMBOL_BEGIN1 = 4,                     /* BEGIN1  */
  YYSYMBOL_END = 5,                        /* END  */
  YYSYMBOL_MAIN = 6,                       /* MAIN  */
  YYSYMBOL_INPUT = 7,                      /* INPUT  */
  YYSYMBOL_OUTPUT = 8,                     /* OUTPUT  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_TO = 17,                        /* TO  */
  YYSYMBOL_DO_CHIQUITO = 18,               /* DO_CHIQUITO  */
  YYSYMBOL_ASIGNACION = 19,                /* ASIGNACION  */
  YYSYMBOL_SUMA = 20,                      /* SUMA  */
  YYSYMBOL_RESTA = 21,                     /* RESTA  */
  YYSYMBOL_MUL = 22,                       /* MUL  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_POTENCIA = 24,                  /* POTENCIA  */
  YYSYMBOL_PUNTOYCOMA = 25,                /* PUNTOYCOMA  */
  YYSYMBOL_DOSPUNTOS = 26,                 /* DOSPUNTOS  */
  YYSYMBOL_PARENTESIS_IZQ = 27,            /* PARENTESIS_IZQ  */
  YYSYMBOL_PARENTESIS_DER = 28,            /* PARENTESIS_DER  */
  YYSYMBOL_COMENTARIO = 29,                /* COMENTARIO  */
  YYSYMBOL_INVALIDO = 30,                  /* INVALIDO  */
  YYSYMBOL_IDENTIFICADOR = 31,             /* IDENTIFICADOR  */
  YYSYMBOL_VALOR_INT = 32,                 /* VALOR_INT  */
  YYSYMBOL_COMPARADOR = 33,                /* COMPARADOR  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_inicio = 35,                    /* inicio  */
  YYSYMBOL_36_1 = 36,                      /* $@1  */
  YYSYMBOL_37_2 = 37,                      /* $@2  */
  YYSYMBOL_bloque_codigo = 38,             /* bloque_codigo  */
  YYSYMBOL_otro_bloque_codigo = 39,        /* otro_bloque_codigo  */
  YYSYMBOL_identificador = 40,             /* identificador  */
  YYSYMBOL_41_3 = 41,                      /* $@3  */
  YYSYMBOL_otro_identificador = 42,        /* otro_identificador  */
  YYSYMBOL_43_4 = 43,                      /* $@4  */
  YYSYMBOL_input = 44,                     /* input  */
  YYSYMBOL_output = 45,                    /* output  */
  YYSYMBOL_instruccion = 46,               /* instruccion  */
  YYSYMBOL_expresion = 47,                 /* expresion  */
  YYSYMBOL_termino = 48,                   /* termino  */
  YYSYMBOL_factor = 49,                    /* factor  */
  YYSYMBOL_operando = 50,                  /* operando  */
  YYSYMBOL_condiciones = 51,               /* condiciones  */
  YYSYMBOL_condicion = 52,                 /* condicion  */
  YYSYMBOL_bloque_instrucciones = 53,      /* bloque_instrucciones  */
  YYSYMBOL_sentencia_if = 54,              /* sentencia_if  */
  YYSYMBOL_55_5 = 55,                      /* @5  */
  YYSYMBOL_56_6 = 56,                      /* @6  */
  YYSYMBOL_repeticion_do = 57,             /* repeticion_do  */
  YYSYMBOL_58_7 = 58,                      /* @7  */
  YYSYMBOL_ciclo_for = 59,                 /* ciclo_for  */
  YYSYMBOL_60_8 = 60,                      /* @8  */
  YYSYMBOL_61_9 = 61,                      /* @9  */
  YYSYMBOL_vacio = 62                      /* vacio  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    22,    22,    22,    23,    23,    25,    25,    27,    27,
      29,    29,    31,    31,    32,    34,    36,    40,    41,    42,
      43,    44,    45,    46,    48,    49,    50,    52,    53,    54,
      56,    57,    59,    60,    61,    62,    66,    67,    68,    70,
      73,    73,    78,    80,    77,    86,    85,    92,    93,    91,
     100
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ALLOCATE", "BEGIN1",
  "END", "MAIN", "INPUT", "OUTPUT", "IF", "ELSE", "THEN", "AND", "OR",
  "DO", "WHILE", "FOR", "TO", "DO_CHIQUITO", "ASIGNACION", "SUMA", "RESTA",
  "MUL", "DIV", "POTENCIA", "PUNTOYCOMA", "DOSPUNTOS", "PARENTESIS_IZQ",
  "PARENTESIS_DER", "COMENTARIO", "INVALIDO", "IDENTIFICADOR", "VALOR_INT",
  "COMPARADOR", "$accept", "inicio", "$@1", "$@2", "bloque_codigo",
  "otro_bloque_codigo", "identificador", "$@3", "otro_identificador",
  "$@4", "input", "output", "instruccion", "expresion", "termino",
  "factor", "operando", "condiciones", "condicion", "bloque_instrucciones",
  "sentencia_if", "@5", "@6", "repeticion_do", "@7", "ciclo_for", "@8",
  "@9", "vacio", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -3,   -42,    18,    27,    25,   -42,   -42,    -1,    30,     6,
      21,    12,   -42,    35,   -42,    31,    -1,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,    -1,    34,    36,    37,     9,    50,
      14,    44,    -1,    66,   -42,    -1,   -42,   -42,    39,     8,
     -42,    31,     9,    58,    14,    42,    14,   -42,   -42,    28,
     -12,   -42,    52,    46,    76,   -42,   -42,   -42,    75,    14,
      37,    37,    70,   -42,    55,    67,   -42,    23,    14,    14,
     -42,    14,    14,    14,   -42,    60,   -42,   -42,   -42,   -42,
      79,    37,    14,   -42,   -12,   -12,   -42,   -42,   -42,    44,
     -42,   -42,    19,    68,   -42,     9,   -42,    83,    84,   -42,
     -42,   -42,    78,     9,    86,    87,     9,   -42,    88,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     2,     0,     0,     0,     4,     1,     0,     0,     0,
       0,     0,    45,     0,    23,    10,    50,     6,    18,    19,
       7,    20,    21,    22,     0,     0,     0,     0,     0,     0,
       0,    50,    50,     0,     9,    50,    15,    16,     0,     0,
      36,     0,    41,     0,     0,     0,     0,    32,    33,     0,
      26,    29,    31,     0,     0,    14,     8,     3,     0,     0,
       0,     0,     0,    40,     0,     0,    34,     0,     0,     0,
      17,     0,     0,     0,    12,     0,     5,    39,    37,    38,
       0,     0,     0,    35,    24,    25,    27,    28,    30,    50,
      11,    42,     0,     0,    13,     0,    46,     0,     0,    47,
      43,    48,     0,     0,     0,     0,     0,    49,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,    -2,   -23,   -42,   -42,     2,   -42,
     -42,   -42,   -28,    48,   -13,   -14,   -40,    15,     3,   -41,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,    32,    33,    17,    31,    54,    89,
      18,    19,    20,    49,    50,    51,    52,    39,    40,    43,
      21,    95,   102,    22,    28,    23,   101,   103,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,    63,    55,     1,    65,    16,     9,    10,    11,    56,
      71,    72,    58,    12,    42,    13,     9,    10,    11,    77,
      60,    61,    35,    12,     5,    13,     2,     6,    14,     7,
      15,    60,    61,    88,    24,    45,    62,    25,    14,    27,
      41,    46,    93,    68,    69,    47,    48,    96,    68,    69,
      30,    83,    26,    70,    98,    84,    85,    86,    87,    36,
      55,    37,   105,    78,    79,   108,    29,    42,    38,    44,
      53,    57,    59,    64,    66,    42,    73,    74,    42,    75,
      76,    80,    81,    91,    82,    90,    97,    99,   104,   100,
     106,    94,   107,   109,    67,     0,    92
};

static const yytype_int8 yycheck[] =
{
      28,    42,    31,     6,    44,     7,     7,     8,     9,    32,
      22,    23,    35,    14,    42,    16,     7,     8,     9,    59,
      12,    13,    24,    14,     6,    16,    29,     0,    29,     4,
      31,    12,    13,    73,     4,    21,    28,    31,    29,    27,
      31,    27,    82,    20,    21,    31,    32,    28,    20,    21,
      19,    28,    31,    25,    95,    68,    69,    71,    72,    25,
      89,    25,   103,    60,    61,   106,    31,    95,    31,    19,
      26,     5,    33,    15,    32,   103,    24,    31,   106,     3,
       5,    11,    27,     4,    17,    25,    18,     4,    10,     5,
       4,    89,     5,     5,    46,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    29,    35,    36,     6,     0,     4,    37,     7,
       8,     9,    14,    16,    29,    31,    38,    40,    44,    45,
      46,    54,    57,    59,     4,    31,    31,    27,    58,    31,
      19,    41,    38,    39,    62,    38,    25,    25,    31,    51,
      52,    31,    46,    53,    19,    21,    27,    31,    32,    47,
      48,    49,    50,    26,    42,    62,    39,     5,    39,    33,
      12,    13,    28,    53,    15,    50,    32,    47,    20,    21,
      25,    22,    23,    24,    31,     3,     5,    50,    52,    52,
      11,    27,    17,    28,    48,    48,    49,    49,    50,    43,
      25,     4,    51,    50,    42,    55,    28,    18,    53,     4,
       5,    60,    56,    61,    10,    53,     4,     5,    53,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    36,    35,    37,    35,    38,    38,    39,    39,
      41,    40,    43,    42,    42,    44,    45,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    47,    48,    48,    48,
      49,    49,    50,    50,    50,    50,    51,    51,    51,    52,
      53,    53,    55,    56,    54,    58,    57,    60,    61,    59,
      62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     7,     1,     1,     2,     1,
       0,     5,     0,     4,     1,     3,     3,     4,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     1,     2,     3,     1,     3,     3,     3,
       2,     1,     0,     0,    14,     0,     7,     0,     0,    12,
       0
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
  case 2: /* $@1: %empty  */
#line 22 "Easylang.y"
             { printf("main:\n"); }
#line 1195 "Easylang.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 23 "Easylang.y"
                        { printf("main:\n"); }
#line 1201 "Easylang.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 29 "Easylang.y"
                             { registrarVariable((yyvsp[0].cadena)); }
#line 1207 "Easylang.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 31 "Easylang.y"
                                            { registrarVariable((yyvsp[0].cadena)); }
#line 1213 "Easylang.tab.c"
    break;

  case 15: /* input: INPUT IDENTIFICADOR PUNTOYCOMA  */
#line 34 "Easylang.y"
                                        { genInput((yyvsp[-1].cadena)); }
#line 1219 "Easylang.tab.c"
    break;

  case 16: /* output: OUTPUT IDENTIFICADOR PUNTOYCOMA  */
#line 36 "Easylang.y"
                                        { genOutput((yyvsp[-1].cadena)); }
#line 1225 "Easylang.tab.c"
    break;

  case 17: /* instruccion: IDENTIFICADOR ASIGNACION expresion PUNTOYCOMA  */
#line 40 "Easylang.y"
                                                              { genAsignacion((yyvsp[-3].cadena),(yyvsp[-1].cadena)); }
#line 1231 "Easylang.tab.c"
    break;

  case 24: /* expresion: expresion SUMA termino  */
#line 48 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"+",(yyvsp[0].cadena)); }
#line 1237 "Easylang.tab.c"
    break;

  case 25: /* expresion: expresion RESTA termino  */
#line 49 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"-",(yyvsp[0].cadena)); }
#line 1243 "Easylang.tab.c"
    break;

  case 26: /* expresion: termino  */
#line 50 "Easylang.y"
                                    { strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1249 "Easylang.tab.c"
    break;

  case 27: /* termino: termino MUL factor  */
#line 52 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"*",(yyvsp[0].cadena)); }
#line 1255 "Easylang.tab.c"
    break;

  case 28: /* termino: termino DIV factor  */
#line 53 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"/",(yyvsp[0].cadena)); }
#line 1261 "Easylang.tab.c"
    break;

  case 29: /* termino: factor  */
#line 54 "Easylang.y"
                                    { strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1267 "Easylang.tab.c"
    break;

  case 30: /* factor: operando POTENCIA operando  */
#line 56 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"**",(yyvsp[0].cadena)); }
#line 1273 "Easylang.tab.c"
    break;

  case 31: /* factor: operando  */
#line 57 "Easylang.y"
                                    { strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1279 "Easylang.tab.c"
    break;

  case 32: /* operando: IDENTIFICADOR  */
#line 59 "Easylang.y"
                                    { registrarVariable((yyvsp[0].cadena)); strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1285 "Easylang.tab.c"
    break;

  case 33: /* operando: VALOR_INT  */
#line 60 "Easylang.y"
                                    { strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1291 "Easylang.tab.c"
    break;

  case 34: /* operando: RESTA VALOR_INT  */
#line 61 "Easylang.y"
                                    { strcpy((yyval.cadena),"-"); strcat((yyval.cadena),(yyvsp[0].cadena)); }
#line 1297 "Easylang.tab.c"
    break;

  case 35: /* operando: PARENTESIS_IZQ expresion PARENTESIS_DER  */
#line 62 "Easylang.y"
                                                { strcpy((yyval.cadena),(yyvsp[-1].cadena)); }
#line 1303 "Easylang.tab.c"
    break;

  case 36: /* condiciones: condicion  */
#line 66 "Easylang.y"
                                    { strcpy((yyval.cadena),(yyvsp[0].cadena)); }
#line 1309 "Easylang.tab.c"
    break;

  case 37: /* condiciones: condiciones AND condicion  */
#line 67 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"AND",(yyvsp[0].cadena)); }
#line 1315 "Easylang.tab.c"
    break;

  case 38: /* condiciones: condiciones OR condicion  */
#line 68 "Easylang.y"
                                    { nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),"OR",(yyvsp[0].cadena)); }
#line 1321 "Easylang.tab.c"
    break;

  case 39: /* condicion: IDENTIFICADOR COMPARADOR operando  */
#line 70 "Easylang.y"
                                             { registrarVariable((yyvsp[-2].cadena)); nuevaTem((yyval.cadena)); genOperacion((yyval.cadena),(yyvsp[-2].cadena),(yyvsp[-1].cadena),(yyvsp[0].cadena)); }
#line 1327 "Easylang.tab.c"
    break;

  case 42: /* @5: %empty  */
#line 78 "Easylang.y"
        { nuevaEtq((yyval.cadena)); genIfz((yyvsp[-3].cadena),(yyval.cadena)); }
#line 1333 "Easylang.tab.c"
    break;

  case 43: /* @6: %empty  */
#line 80 "Easylang.y"
        { nuevaEtq((yyval.cadena)); genGoto((yyval.cadena)); genEtiqueta((yyvsp[-2].cadena)); }
#line 1339 "Easylang.tab.c"
    break;

  case 44: /* sentencia_if: IF PARENTESIS_IZQ condiciones PARENTESIS_DER THEN BEGIN1 @5 bloque_instrucciones END @6 ELSE BEGIN1 bloque_instrucciones END  */
#line 82 "Easylang.y"
        { genEtiqueta((yyvsp[-4].cadena)); }
#line 1345 "Easylang.tab.c"
    break;

  case 45: /* @7: %empty  */
#line 86 "Easylang.y"
        { nuevaEtq((yyval.cadena)); genEtiqueta((yyval.cadena)); }
#line 1351 "Easylang.tab.c"
    break;

  case 46: /* repeticion_do: DO @7 bloque_instrucciones WHILE PARENTESIS_IZQ condiciones PARENTESIS_DER  */
#line 88 "Easylang.y"
        { genIfnz((yyvsp[-1].cadena),(yyvsp[-5].cadena)); }
#line 1357 "Easylang.tab.c"
    break;

  case 47: /* @8: %empty  */
#line 92 "Easylang.y"
        { genAsignacion((yyvsp[-6].cadena),(yyvsp[-4].cadena)); nuevaEtq((yyval.cadena)); genEtiqueta((yyval.cadena)); }
#line 1363 "Easylang.tab.c"
    break;

  case 48: /* @9: %empty  */
#line 93 "Easylang.y"
        { char t[50]; nuevaTem(t); genOperacion(t,(yyvsp[-7].cadena),"<=",(yyvsp[-3].cadena));
          nuevaEtq((yyval.cadena)); genIfz(t,(yyval.cadena)); }
#line 1370 "Easylang.tab.c"
    break;

  case 49: /* ciclo_for: FOR IDENTIFICADOR ASIGNACION operando TO operando DO_CHIQUITO BEGIN1 @8 @9 bloque_instrucciones END  */
#line 96 "Easylang.y"
        { char t[50]; nuevaTem(t); genOperacion(t,(yyvsp[-10].cadena),"+","1"); genAsignacion((yyvsp[-10].cadena),t);
          genGoto((yyvsp[-3].cadena)); genEtiqueta((yyvsp[-2].cadena)); }
#line 1377 "Easylang.tab.c"
    break;


#line 1381 "Easylang.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 102 "Easylang.y"


void yyerror(char *mensaje){
    extern int yylineno;
    extern char *yytext;
    fprintf(stderr, "Error: %s en la linea %i cerca de %s\n", mensaje, yylineno, yytext);
}

/*escribe salida.asm y salida.tac */
int main(int argc, char **argv){
    extern FILE *yyin;
    const char *nombreSalida = (argc > 2) ? argv[2] : "salida.asm";
    const char *nombreTac = (argc > 3) ? argv[3] : "salida.tac";
    FILE *tac;
    int pantalla, resultado, c;

    if (argc > 1 && !(yyin = fopen(argv[1], "r"))) { perror(argv[1]); return 1; }

    if (iniciarGenerador() != 0) return 1;

    /* Mientras se analiza, los printf del codigo de tres direcciones van al archivo */
    pantalla = dup(STDOUT_FILENO);
    if (!freopen(nombreTac, "w", stdout)) { perror(nombreTac); return 1; }
    resultado = yyparse();
    fflush(stdout);
    dup2(pantalla, STDOUT_FILENO);     

    if (resultado != 0) {              
        remove(nombreTac);
        return 1;
    }

    tac = fopen(nombreTac, "r");
    if (!tac) { perror(nombreTac); return 1; }
    while ((c = fgetc(tac)) != EOF) putchar(c);
    fclose(tac);

    return escribirAsm(nombreSalida);
}
