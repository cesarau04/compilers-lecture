#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void rmcomments(char* str, size_t linenum);
void checkparentesis(char* str, size_t linenum);
void checkbrackets(char* str, size_t linenum);
void checkbraces(char* str, size_t linenum);

int errfound = 0;

size_t parentesis_in_count = 0;
size_t brackets_in_count = 0;
size_t braces_in_count = 0;

size_t parentesis_out_count = 0;
size_t brackets_out_count = 0;
size_t braces_out_count = 0;

int lastparentesis_in_loc = -1;
int lastbracket_in_loc = -1;
int lastbrace_in_loc = -1;

int lastparentesis_out_loc = -1;
int lastbracket_out_loc = -1;
int lastbrace_out_loc = -1;

int lastparentesis_numline = -1;
int lastbracket_numline = -1;
int lastbrace_numline = -1;

char lastparentesisline[256];
char lastbracketline[256];
char lastbraceline[256];

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Error: invalid argument\n");
        return 1;
    }
    
    char const* const fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    
    if (file == NULL){
        printf("Error: cannot open file\n");
        return 1;
    }

    char line[256];

    size_t linenum = 1;
    while (fgets(line, sizeof(line), file)) {
        rmcomments(line, linenum);
        checkparentesis(line, linenum);
        checkbrackets(line, linenum);
        checkbraces(line, linenum);
        linenum++;
    }

    if (parentesis_in_count != parentesis_out_count){
        printf("Error: no matched parentesis (%d,%d)\n%s\n", lastparentesis_numline, lastparentesis_in_loc,lastparentesisline);
        for (size_t i = 0; i < lastparentesis_in_loc; i++)
        {
            printf(" ");
        }
        printf("^\n");
        errfound = 1;
    }
    if (brackets_in_count != brackets_out_count){
        printf("Error: no matched brackets (%d,%d)\n%s\n", lastbracket_numline, lastbracket_in_loc, lastbracketline);
        for (size_t i = 0; i < lastbracket_in_loc; i++)
        {
            printf(" ");
        }
        printf("^\n");
        errfound = 1;
    }
    if (braces_in_count != braces_out_count){
        printf("Error: no matched braces (%d,%d)\n%s\n", lastbrace_numline, lastbrace_in_loc, lastbraceline);
        for (size_t i = 0; i < lastbrace_in_loc; i++)
        {
            printf(" ");
        }
        printf("^\n");
        errfound = 1;
    }

    if (!errfound){
        printf("No errors found!\n");
    }
    
    fclose(file);
    return 0;
}


void rmcomments(char* str, size_t linenum){
    size_t i = 0;
    size_t qoutecounter = 0;
    size_t lastquotecol = 0;
    char c;
    char c_prev;
    char cpline[256];

    strcpy(cpline, str);

    while ((c = str[i++]) != '\0'){
        if (c == '"'){
            qoutecounter++;
            lastquotecol = i-1;
        }
        if (qoutecounter%2 != 0){ // if quote open
            continue;
        } else {
            if (c == '/' && c_prev == '/'){
                i = i - 2;
                str[i] = '\0';
                break;
            }
            c_prev = c;
        }
    }
    if (qoutecounter%2 != 0){
        printf("Error: no closing quotation mark (%ld,%ld)\n%s\n", linenum, lastquotecol, cpline);
        for (size_t i = 0; i < lastquotecol; i++){
            printf(" ");
        }
        printf("^\n");
        errfound = 1;
    }
}

void checkparentesis(char* str, size_t linenum){
    size_t i = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (c == '('){
            parentesis_in_count++;
            lastparentesis_in_loc = i;
            strcpy(lastparentesisline, str);
            lastparentesis_numline = linenum;
        } else if (c == ')') {
            parentesis_out_count++;
            lastparentesis_out_loc = i;
        }
    }
}

void checkbrackets(char* str, size_t linenum){
    size_t i = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (c == '['){
            brackets_in_count++;
            lastbracket_in_loc = i;
            strcpy(lastbracketline, str);
            lastbracket_numline = linenum;
        } else if (c == ']') {
            brackets_out_count++;
            lastbracket_out_loc = i;
        }
    }
}

void checkbraces(char* str, size_t linenum){
    size_t i = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (c == '{'){
            braces_in_count++;
            lastbrace_in_loc = i;
            strcpy(lastbraceline, str);
            lastbrace_numline = linenum;
        } else if (c == '}') {
            braces_out_count++;
            lastbrace_out_loc = i;
        }
    }
}

/*
void rmalphanumerics(char* str);
void rmspaces(char* str);
void rmsemicolon(char* str);

void rmalphanumerics(char* str){
    size_t i = 0;
    size_t j = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (!isalnum(c)){
            str[j++] = c;
        }
    }
    str[j] = '\0';
}

void rmspaces(char* str){
    size_t i = 0;
    size_t j = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (!isspace(c)){
            str[j++] = c;
        }
    }
    str[j] = '\0';
}

void rmsemicolon(char* str){
    size_t i = 0;
    size_t j = 0;
    char c;

    while ((c = str[i++]) != '\0'){
        if (c != ';'){
            str[j++] = c;
        }
    }
    str[j] = '\0';
}
 */