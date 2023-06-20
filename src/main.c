#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Token {
    char TOKENS[1024][1024];
    int size;
} s;

char STRING[128];

int make_string(char code[], int len, int pos) {
    int i;

    for (i = pos; i < len; i++) {
        char tmp[2] = {code[i], '\0'};

        if (code[i] != '"')
            strcat(STRING, tmp);
        else
            break;
    }
    
    return i;
}

void make_tokens(char code[], int len) {
    s.size = 0;

    char chunk[1024] = "";

    for (int i = 0; i < len; i++) {
        // printf("%c\n", code[i]);

        char tmp[2] = {code[i], '\0'};
        strcat(chunk, tmp);

        if (code[i] == ';') {
            strcpy(s.TOKENS[s.size], "TT_NEWLINE");
            s.size++;
            chunk[0] = '\0';
        }
        else if (code[i] == '"') {
            i = make_string(code, len, i+1);
            strcpy(s.TOKENS[s.size], STRING);
            s.size++;
            chunk[0] = '\0';
            STRING[0] = '\0';
        }

        if (strcmp(chunk, "print") == 0) {
            strcpy(s.TOKENS[s.size], "TT_PRINT");
            s.size++;
            chunk[0] = '\0';
        }
        else if (strcmp(chunk, "exit") == 0) {
            strcpy(s.TOKENS[s.size], "TT_EXIT");
            s.size++;
            chunk[0] = '\0';  
        }
        //else if (strcmp(chunk, "") == 0) {
        //}
    }

}

int main() {
    char code[] = "print \"Hello, World!\";exit;";
    int sizeof_code = sizeof(code)/sizeof(code[0]);
    make_tokens(code, sizeof_code);
    
    for (int i = 0; i < s.size; i++)
        printf("%s\n", s.TOKENS[i]);
}

