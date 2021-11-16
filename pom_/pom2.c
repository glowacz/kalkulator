#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read(FILE* file, size_t base_len){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*base_len);
    //if(!str) return str;
    ch=getc(file);
    while(EOF != ch && ch != '\n'){
        str[len++] = ch;
        if(len == base_len){
            str = realloc(str, sizeof(*str)*(base_len+=2));
            if(!str) return str;
        }
        ch=getc(file);
    }
    str[len++] = '\0';
    return realloc(str, sizeof(*str)*len);
}

char *read(FILE* file, size_t base_len){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*base_len);
    if(!str) return str;
    while(EOF != (ch=getc(file)) && ch != '\n'){
        str[len++] = ch;
        if(len == base_len){
            str = realloc(str, sizeof(*str)*(base_len+=2));
            if(!str) return str;
        }
    }
    str[len++] = '\0';
    return realloc(str, sizeof(*str)*len);
}

int main()
{
    //char *a, *b, *c, op, *line = malloc(10);
    size_t bufsize = 0;
    char *a = malloc(bufsize*sizeof(char)), *b = malloc(bufsize*sizeof(char)), *bin = malloc(bufsize*sizeof(char)),*c, op, *line = malloc(bufsize*sizeof(char)), ch;
    int sys, sys1, sys2, i = 0, n;
    FILE *in = fopen("ex.in", "r");
    //FILE *in = stdin;
    ch = getc(in);
    //putchar(ch);
    while(ch != '\n'){
        line[i++] = ch;
        putchar(ch);
        ch = getc(in);
    }
    getc(in);
    getc(in);
    op = line[0];
    printf("op=%c\n", op);
    printf("line=%s\n", line);

    //printf("działanie\n");
    if(strlen(line) == 4) sys = line[2]-'0';
    else sys = 10+line[3]-'0';
    printf("sys = %i\n", sys);
    a = read(in, 4);
    printf("a=%s\n", a);
    getc(in);
    getc(in);
    b = read(in, 4);
    printf("b=%s\n", b);
    getc(in);
    getc(in);
    printf("a=%s\nb=%s\n", a, b);
    return 0;
}