#ifndef LEXER_H_
#define LEXER_H_

#include <stddef.h>
#include <stdio.h>

#include "utils/string_view.h"

#define TOKENSLIST_INITILCAPACITY 16

typedef enum {
    TT_NEW_LINE,
    TT_KEYWORD,
    TT_STRING,
} TokenType;

typedef enum {
    KW_PRINT,
    KW_EXIT,
} KeywordType;

typedef union {
    KeywordType keyword;
    StringView string;
} TokenData;

typedef struct {
    TokenType type;
    TokenData as;
} Token;

#define T_New_Line    (Token) { .type = TT_NEW_LINE, .as = {0} }
#define T_Keyword(kw) (Token) { .type = TT_KEYWORD, .as.keyword = (kw) }
#define T_String(sv)  (Token) { .type = TT_STRING, .as.string = (sv) }

typedef struct {
    size_t size;
    size_t capacity;
    Token* as;
} TokensList;

void Lexer_make_tokens(const char* code, TokensList* tokens);

void Token_print(Token* self, FILE* stream);

TokensList TokensList_alloc();
void TokensList_free(TokensList* self);
void TokensList_append(TokensList* self, Token token);
void TokensList_print(TokensList* self, FILE* stream);

#endif // LEXER_H_
