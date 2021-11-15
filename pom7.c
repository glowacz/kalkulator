#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#define A 2
#define BUF 100000

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

int main()
{
    FILE *in = fopen("in_big.txt", "r");
    FILE *out = fopen("pom.out", "w");
    //FILE *out = stdout;
    char *a, *b, *c, op, *line, *bin;
    size_t bufsize = BUF;
    while(1){
    printf("----------------------------------------------\n");
    //char *a = malloc(BUF), *b = malloc(BUF), *bin = malloc(BUF), 
    //*c = malloc(BUF), *line = malloc(BUF), op, ch;
    int sys, sys1, sys2, n, m, line_len, err;    
    //FILE *in = stdin;
    /*while(ch != '\n'){
        line[i++] = ch;
        putchar(ch);
        ch = getc(in);
    }*/
    line = read(in, 2);

    line_len = strlen(line);

    if(line_len == 0) break;
    
    bin = read(in, 2);
    
    //printf("dlugosc bin1:\n%li\n", strlen(bin));
    
    a = read(in, 2);
    
    bin = read(in, 2);

    b = read(in, 2);
    
    bin = read(in, 2);

    bin = read(in, 2);

    //printf("dlugosc bin4:\n%li\n", strlen(bin));

    n = strlen(a);
    m = strlen(b);
    line[line_len-1] = '\0';
    a[n-1] = '\0';
    b[m-1] = '\0';
    printf("dlugosci:\n%i\n%i\n%i\n", line_len, n, m);
    printf("wartosci:\n|%s|\n|%s|\n|%s|\n", line, a, b);
    //line[line_len-2] = '\0';
    op = line[0];
    //printf("dl_linii=%i\n", line_len);
    //printf("linia=%s\n", line);
    //działanie
    /*if(line_len == 5) sys = line[2]-'0';
    else sys = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych

    a[strlen(a)-2] = '\0';
    b[strlen(b)-2] = '\0';

    fprintf(out, "%s\n\n%s\n\n%s\n\n", line, a, b);

    printf("Memory allocated for a: %li bytes\n", malloc_usable_size(a));
    printf("Memory allocated for b: %li bytes\n", malloc_usable_size(b));
    printf("Memory allocated for c: %li bytes\n", malloc_usable_size(c));*/

    free(a);
    free(b);
    free(line);

    //printf("dlugosc bin5:\n%li\n", strlen(bin));
    /*if(strlen(bin) == 0) {
        free(bin); 
        break;
    }*/

    free(bin);
    
    }
    return 0;
}
