#include <stddef.h>
#include<stdio.h>

#include "./lexer.h"

int main() {
    char* code = "print     \"Hello\";exit";

    TokensList tokens_list = TokensList_alloc();
    Lexer_make_tokens(code, &tokens_list);
    TokensList_print(&tokens_list, stdout);
    //parse_tokens(&tokens_list);

    TokensList_free(&tokens_list);

    return 0;
}
