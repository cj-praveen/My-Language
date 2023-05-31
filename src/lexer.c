#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./lexer.h"
#include "./utils/string_view.h"

const StringView KEYWORDS[] = {
    SV_Fcstr("print"),
    SV_Fcstr("exit"),
};

#define KEYWORDS_LEN sizeof(KEYWORDS) / sizeof(KEYWORDS[0])

void Token_print(Token* self, FILE* stream) {
    switch (self->type) {
        case TT_NEW_LINE:
            fprintf(stream, "NEW_LINE\n");
            return;
        case TT_KEYWORD:
            fprintf(stream, "KEYWORD: "SV_Fmt"\n", SV_Arg(KEYWORDS[self->as.keyword]));
            return;
        case TT_STRING:
            fprintf(stream, "STRING: "SV_Fmt"\n", SV_Arg(self->as.string));
            return;
    }
    assert(0 && "Token_print: Unreachable");
}

TokensList TokensList_alloc() {
    Token* allocation = calloc(TOKENSLIST_INITILCAPACITY, sizeof(Token));
    if (allocation == NULL) {
        fprintf(stderr, "S_ERROR: Buy more RAM, XD\n");
        exit(69);
    }

    return (TokensList) {
        .size = 0,
        .capacity = TOKENSLIST_INITILCAPACITY,
        .as = allocation,
    };
}

void TokensList_append(TokensList* self, Token token){
    if (self->size >= self->capacity) {
        self->capacity *= 2;
        self->as = realloc(self->as, self->capacity);
        if (self->as == NULL) {
            fprintf(stderr, "S_ERROR: Buy more RAM, XD\n");
            exit(69);
        }
    }

    self->as[self->size] = token;
    self->size += 1;
}

void TokensList_free(TokensList* self) {
    free(self->as);
    self->capacity = 0;
    self->size = 0;
}

void TokensList_print(TokensList* self, FILE* stream) {
    fprintf(stream, "Tokens:\n");
    for (size_t i = 0; i < self->size; ++i) {
        fprintf(stream, "    ");
        Token_print(&self->as[i], stream);
    }
}

typedef struct {
    const char* source;
    const int source_len;
    TokensList *tokens;
    int index;
    char curr_char;
} _LexerState;

void _LexS_advance(_LexerState* lexer) {
    lexer->index++;

    if (lexer->index >= lexer->source_len) {
        lexer->curr_char = EOF;
        return;
    }

    lexer->curr_char = lexer->source[lexer->index];
}

void _LexS_make_string(_LexerState* lexer) {
    assert(lexer->curr_char == '"');
    _LexS_advance(lexer);
    StringView string = SV_New(0, lexer->source + lexer->index);

    while (lexer->curr_char != '"') {
        string.size += 1;
        _LexS_advance(lexer);
    }

    _LexS_advance(lexer);
    TokensList_append(lexer->tokens, T_String(string));
}

void _LexS_make_identifier(_LexerState* lexer) {
    assert(isalpha(lexer->curr_char) && "Unreachable");
    StringView identifier = SV_New(0, lexer->source + lexer->index);

    while isalnum(lexer->curr_char) {
        identifier.size += 1;
        _LexS_advance(lexer);
    }

    int keyword_index = SV_in(KEYWORDS, KEYWORDS_LEN, identifier);
    if (keyword_index >= 0) {
        TokensList_append(lexer->tokens, T_Keyword(keyword_index));
        return;
    }

    fprintf(stderr, "InvalidIdentifier: `"SV_Fmt"`\n", SV_Arg(identifier));
    exit(-1);
}

void Lexer_make_tokens(const char* source, TokensList* tokens) {
    _LexerState lexer = (_LexerState) {
        .source = source,
        .source_len = strlen(source),
        .tokens = tokens,
        .index = 0,
        .curr_char = source[0],
    };

    while (lexer.curr_char != EOF) {
        if isspace(lexer.curr_char) {
            _LexS_advance(&lexer);
        }
        else if (lexer.curr_char == ';') {
            TokensList_append(lexer.tokens, T_New_Line);
            _LexS_advance(&lexer);
        }
        else if (lexer.curr_char == '"') {
            _LexS_make_string(&lexer);
        }
        else if isalpha(lexer.curr_char) {
            _LexS_make_identifier(&lexer);
        }
        else {
            fprintf(stderr, "InvalidCharError: `%c`(%d)\n", lexer.curr_char, lexer.curr_char);
            exit(-1);
        }
    }
}
