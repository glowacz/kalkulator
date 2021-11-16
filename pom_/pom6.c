#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *in = fopen("in_pom2.txt", "r");
    char *a = malloc(1), *b = malloc(1), *bin = malloc(1);
    size_t bufsize = 1, n, m;

    getline(&a, &bufsize, in);
    getline(&bin, &bufsize, in);
    getline(&b, &bufsize, in);
    getline(&bin, &bufsize, in);
    getline(&bin, &bufsize, in);
    
    n = strlen(a);
    m = strlen(b);
    a[n-2] = '\0';
    n = strlen(a);
    printf("%li\n%li\n", n, m);
    printf("|%s|\n|%s|\n", a, b);
    
    
    return 0;
}