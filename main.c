#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
    TT_PRINT,
    TT_EXIT,
    TT_IDENTIFIER,
    TT_EXPR,
    TT_EOL,
    TT_COMMENTS,
    TT_STR
} TokenType;

TokenType *TOKENS;
int tt_size = 0;
char *STRING;

int make_string(char code[], int len, int pos) {
    int i;

    for (i = pos + 1; i < len; i++) {
        char tmp[2] = {code[i], '\0'};

        if (code[i] != '"')
            strcat(STRING, tmp);
        else
            break; 
    }
    
    return i;
}

int handle_comments(char code[], int len, int pos) {
    int i;

    for (i = pos; i < len; i++) {
        if (code[i] == ';')
            break; 
    }
    
    return i - 1;
}

void make_tokens(char code[], int len) {
    char *chunk = malloc(sizeof(char) * 10);

    for (int i = 0; i < len; i++) {
        // printf("%c\n", code[i]);

        char tmp[2] = {code[i], '\0'};
        strcat(chunk, tmp);
        
        if (code[i] == ';') {
            TOKENS[tt_size] = TT_EOL;
            tt_size++;
            chunk[0] = '\0';
        }
        else if (code[i] == '#') {
            TOKENS[tt_size] = TT_COMMENTS;
            tt_size++;
            i = handle_comments(code, len, i);
            chunk[0] = '\0';
        }
        else if (code[i] == '"') {
            TOKENS[tt_size] = TT_STR;
            tt_size++;
            chunk[0] = '\0';
            i = make_string(code, len, i);
            printf("%s\n", STRING);
        }

        if (strcmp(chunk, "print") == 0) {
            TOKENS[tt_size] = TT_PRINT;
            tt_size++;
            chunk[0] = '\0';
        }
        else if (strcmp(chunk, "exit") == 0) {
            TOKENS[tt_size] = TT_EXIT;
            tt_size++;
            chunk[0] = '\0';
        }
    }

    free(chunk);
}

void parse_tokens() {
    for (int i = 0; i < tt_size; i++) {
        TokenType l = TOKENS[i];
        switch(l) {
            case TT_EOL:
            printf("end of line\n");
            break;
            case TT_EXIT:
            printf("exit\n");
            break;
            case TT_PRINT:
            printf("print\n");
            break;
            case TT_EXPR:
            printf("expression\n");
            break;
            case TT_IDENTIFIER:
            printf("identifier\n");
            break;
            case TT_COMMENTS:
            printf("comments\n");
            break;
            case TT_STR:
            printf("string\n");
            break;
        }
    }
}

int main() {
    TOKENS = malloc(sizeof(TokenType) * 10);
    STRING = malloc(sizeof(char) * 10);
    
    char code[] = \
    "print \"Hello, World!\n\";"\
    "# this is a non-executable line;"\
    "exit();";
    
    int sizeof_code = sizeof(code)/sizeof(code[0]);
    
    make_tokens(code, sizeof_code);
    parse_tokens();
}
