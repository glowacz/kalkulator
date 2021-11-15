#include <stdio.h>
#include <stdlib.h>

/*char *read(FILE *file, size_t bufize){
    size_t len = 0;
    char ch;
    while( EOF != (ch=getc(file)) && ch != '\n' ){
        if()
    }
}*/

int main(){
    FILE *in = fopen("ex.in", "r");
    FILE *out = fopen("shit.txt", "w");
    char *str;
    printf("%s", str);
    fprintf( out, "gowno");
    return 0;
}