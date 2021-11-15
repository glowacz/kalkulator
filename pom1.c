#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *in = fopen("ex.in", "r");
    size_t bufsize = 1, n;
    char *line = (char *)malloc(1*sizeof(char)), *a = (char *)malloc(1*sizeof(char)), *b = (char *)malloc(1*sizeof(char)), *bin = (char *)malloc(1*sizeof(char));
    getline(&line, &bufsize, in);
    getline(&bin, &bufsize, in);
    getline(&a, &bufsize, in);
    getline(&bin, &bufsize, in);
    getline(&b, &bufsize, in);
    printf("%li\n", strlen(a)-1);
    a[strlen(a)-1] = '\0';
    printf("%li\n", strlen(a)-1);
    printf("a = %s\nb = %s\n", a, b);
    return 0;
}