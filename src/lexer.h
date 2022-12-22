#ifndef CODIN_LEXER_H
#define CODIN_LEXER_H
#include "support.h"

typedef struct Lexer Lexer;
typedef struct Token Token;
typedef struct Location Location;
typedef struct Source Source;
typedef struct Input Input;

typedef enum Kind Kind;
typedef enum Literal Literal;
typedef enum Operator Operator;
typedef enum Keyword Keyword;

#define KIND(kind, ...) KIND_ ## kind,
enum Kind {
	#include "lexemes.h"
	KIND_COUNT,
};

String kind_to_string(Kind kind);

#define LITERAL(kind, ...) LITERAL_ ## kind,
enum Literal {
	#include "lexemes.h"
	LITERAL_COUNT,
};

#define OPERATOR(kind, ...) OPERATOR_ ## kind,
enum Operator {
	#include "lexemes.h"
	OPERATOR_COUNT,
};

String operator_to_string(Operator op);

#define KEYWORD(kind, ...) KEYWORD_ ## kind,
enum Keyword {
	#include "lexemes.h"
	KEYWORD_COUNT,
};

String keyword_to_string(Keyword keyword);

struct Source {
	String name;
	String contents;
};

struct Location {
	int column;
	int line;
};

struct Token {
	Kind kind;
	Location location;
	String string; // comment, identifier
	union {
		Literal as_literal;
		Operator as_operator;
		Keyword as_keyword;
	};
};

String token_to_string(Token token);

struct Input {
	const Source *source;
	Uint8 *cur;
	const Uint8 *end;
};

struct Lexer {
	Input input;
	Location location; 
	const Uint8 *here;
	Rune rune;
	Bool asi;
};

Bool lexer_init(Lexer *lexer, const Source *source);
Token lexer_next(Lexer *lexer);

#endif // CODIN_LEXER_H