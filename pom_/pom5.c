#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    char *s;
    size_t buffsize = 1, size;
    s = malloc(buffsize * sizeof(char));
    getline(&s, &buffsize, in);

    // size = _msize(s);
    // printf("ss %d", size);
    // exit(1);
    // // scanf("%s", s);

    // char *s2;
    // s2 = malloc(buffsize * sizeof(char));
    // getline(&s2, &buffsize, in);
    // // scanf("%s", s2);

    // if (s[strlen(s) - 1] == '\n')
    // {
    //     printf("endl \n");
    //     s[strlen(s) - 2] = '\0';
    //     // s[strlen(s) - 1] = '\0';
    // }

    // s = realloc(s, 10);

    int d = strlen(s);
    printf("%d", d);

    // FILE *out = fopen("output.txt", "w");
    // fputs((s), out);
    // // printf("%c", s[7]);
    // // printf("%s", s);
}