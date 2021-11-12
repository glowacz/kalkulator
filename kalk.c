#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//#include <math.h>
//#define max(x, y) (x > y) ? (x) : (y)

int pow_(int b, int e){
    int res = 1;
    for(int i = 0; i < e; i++) res *= b;
    return res;
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

void let_to_num(char *str){
    int i;
    for(i=0; i<strlen(str); i++){
        if(str[i]-'0' >= 10) str[i] -= 7;
    }
}

void num_to_let(char *str){
    int i;
    for(i=0; i<strlen(str); i++){
        if(str[i]-'0' >= 10) str[i] += 7;
    }
}

char *add(char *a, char *b, int sys){
    int n, m, i, j_a, j_b;
    if(strlen(a) >= strlen(b)){
        n = strlen(a);
        m = strlen(b);
        j_b = m-1;
        j_a = INT_MAX;
    }
    else{
        n = strlen(b);
        m = strlen(a);
        j_a = m-1;
        j_b = INT_MAX;
    }

    let_to_num(a);
    let_to_num(b);

    int cy[n+1];
    char *c = malloc(n+2);

    for(i=n; i >= 0; i--) cy[i] = 0;

    for(i=n-1; i>=0; i--) {
        if(j_a < 0) cy[i+1] += b[i]-'0';
        else if(j_b < 0) cy[i+1] += a[i]-'0';
        else if(strlen(a) >= strlen(b)) cy[i+1] += a[i]+b[j_b]-2*'0';
        else cy[i+1] += a[j_a]+b[i]-2*'0';

        if(cy[i+1] >= sys){
            c[i+1] = cy[i+1]-sys+'0';
            cy[i] = 1;
        }
        else c[i+1] = cy[i+1]+'0';
        j_a--;
        j_b--;
    }
    c[0] = cy[0]+'0';
    c[n+1] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);

    while(c[0] == '0') c++;
    return c;
}

char *subtr(char *a, char *b, int sys){
    int n, m, i, j_b;
    n = strlen(a);
    m = strlen(b);
    j_b = m-1;

    let_to_num(a);
    let_to_num(b);

    int cy[n+1];
    char *c = malloc(n+1);

    for(i=n; i >= 0; i--) cy[i] = 0;

    for(i=n-1; i>=0; i--) {
        //printf("%i\n", i);
        if(j_b < 0) cy[i] = a[i]-'0';
        else cy[i] = a[i]-b[j_b];

        if(cy[i] < 0){
            a[i-1] -= 1;
            cy[i] += sys;
        }
        //printf("%i\n", cy[i]);
        c[i] = cy[i]+'0';
        j_b--;
    }
    c[n] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);
    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;
    return c;
}

char *mult(char *a, char *b, int sys){
    //printf("mnozenie\n%s\n%s\n", a, b);
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    let_to_num(a);
    let_to_num(b);

    int cy_a[n], cy_b[m], cy[n+m], cy_main[n+m];
    char *c = malloc(n+m);

    for(i=0; i<n; i++) cy_a[i] = a[i]-'0';
    for(i=0; i<m; i++) cy_b[i] = b[i]-'0';

    for(i=n+m-1; i >= 0; i--) cy_main[i] = 0;

    for(j=m-1; j>=0; j--) {
        i_c = n+j;
        for(i=i_c; i >= i_c-n; i--) cy[i] = 0;
        for(i=n-1; i >= 0; i--){
            cy[i_c] += cy_b[j]*cy_a[i];
            if(cy[i_c] >= sys) {
                cy[i_c-1] = cy[i_c]/sys;
                cy[i_c] %= sys;
            }
            i_c--;
        }
        for(i = n+j; i>=i_c; i--){
            cy_main[i] += cy[i];
            if(cy_main[i] >= sys){
                cy_main[i-1] += cy_main[i]/sys;
                cy_main[i] %= sys;
            }
        }
    }
    for(i=0; i<n+m; i++) c[i] = cy_main[i]+'0';
    c[n+m] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    //printf("wynik odejmowania=%s\n", c);

    return c;
}

char *div_pom(char *a, char *b, int sys, int *cy){
    char *c = malloc(strlen(a));
    strcpy(c, b);
    int i = 1;
    while(a[0] == '0') a++;
    while(strlen(c) < strlen(a) || (strlen(c) == strlen(a) && strcmp(a, c) > 0) ){
        c = add(c, b, sys);
        i++;
    }
    if(strcmp(a, c) != 0) {
        i--;
        c = subtr(c, b, sys);
    }
    *cy = i;
    return c;
}

char *div_(char *a, char *b, int sys){
    //printf("a=%s, b=%s\n", a, b); printf("b=%s\n", b);
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    int cy_a[n], cy_b[m], cy = 0, cy_curr[n];
    char *c = malloc(n), *curr = malloc(m+1), *prev = malloc(m+1), ch;

    for(i=0; i<n; i++) c[i] = '0';

    for(i=m-1; i<n; i++){

        if(i == m-1){
            ch = a[i+1];
            //printf("char do dopisania: %c\n", ch);
            a[i+1] = '\0';
            curr = a;
        }
        else{
            ch = a[i+1];
            //printf("char do dopisania: %c\n", ch);
            a[i+1] = '\0';
        }
        prev = curr;
        curr = div_pom(curr, b, sys, &cy);
        c[i] = cy+'0';
        curr = subtr(prev, curr, sys);
        a[i+1] = ch;
        curr[strlen(curr)] = ch;
    }
    
    c[n] = '\0';
    //printf("c = %s\n", c);
    num_to_let(c);

    while(c[0] == '0') {
        //printf("c++\n");
        c++;
    }
    if(strlen(c) == 0) c--;
    //printf("%i\n", strlen(c));
    return c;
}

char *sys_conv(int sys1, int sys2){
    //printf("sys_conv\n");
    int akt = sys2, i = 0, pom[10];
    char *wyn = malloc(10);
    while( akt != 0 ){
        pom[i] = akt % sys1;
        //printf("pom[%i] = %i\n", i, pom[i]);
        akt /= sys1;
        i++;
        //printf("akt = %i\n", akt);
    }
    int n = i;
    //printf("n = %i\n", n);
    for(i=0; i<n; i++) {
        //printf("pom[%i] = %i\n", n-i-1, pom[n-i-1]);
        wyn[i] = pom[n-i-1]+'0';
    }
    wyn[n] = '\0';
    num_to_let(wyn);
    return wyn;
}

int dig_conv(char *str, int sys1, int sys2){
    int res = 0, n = strlen(str);
    let_to_num(str);
    for(int i = 0; i<n; i++) res += (str[i]-'0')*pow_(sys1, (n-i-1));
    num_to_let(str);
    return res;
}

char *num_conv(char *a, char *b, int sys, int sys2){
    int i = 0, cy[strlen(a)*4];
    //char *akt = a, *prev, *wyn = malloc(strlen(a)*4), *pom = malloc(strlen(a)*4);
    char *akt = malloc(strlen(a)), *prev = malloc(strlen(a)), *wyn = malloc(strlen(a)*4), *pom = malloc(strlen(a)*4);
    strcpy(akt, a);

    while( akt[0] != '0' ){
        //prev = akt;
        strcpy(prev, akt);
        printf("akt=%s\n", akt);
        printf("prev=%s\n", prev);
        akt = div_(akt, b, sys);
        printf("akt(po dzieleniu)=%s\n", akt);
        printf("prev=%s\n", prev);
        printf("po mnozeniu=%s\n", mult(akt, b, sys));
        //printf("%s\n", subtr(prev, mult(akt, b, sys), sys));
        pom[i] =  dig_conv(subtr(prev, mult(akt, b, sys), sys), sys, sys2)+'0';
        printf("%c\n", pom[i]);
        i++;
    }
    int n = i;
    for(i=0; i<n; i++) {
        wyn[i] = pom[n-i-1];
    }
    wyn[n] = '\0';
    num_to_let(wyn);
    
    return wyn;
}

char *qck_pow(char *b, char *e, int sys){
    //printf("--------------------------\npodst = %s\nwykl = %s\nsys = %i\n", b, e, sys);
    char *pom = malloc(strlen(e));
    if(strcmp(e, "0") == 0) return "1";
    if(strcmp(e, "1") == 0) return b;
    else if(sys == 2){
        ;
    }
    else{
        pom = div_(e, "2", sys);
        //printf("wynik dzielenia przez 2 = %s\n", pom);
        if(strcmp(mult(pom, "2", sys), e) == 0) return mult(qck_pow(b, pom, sys), qck_pow(b, pom, sys), sys);
        else return mult(qck_pow(b, subtr(e, "1", sys), sys), b, sys);
    }
}

int main()
{
    //char *a, *b, *c, op, *line = malloc(10);
    char *a, *b, *c, op, line[10];
    int sys, sys1, sys2;
    FILE *in = fopen("przyklad.in", "r");
    //FILE *in = stdin;

    fgets(line, 10, in);
    getc(in);
    getc(in);
    //printf("%sxD\n", line);
    op = line[0];

    if(op >= 48 && op <= 57){
        //printf("%c\n", line[1]);
        //printf("%i\n", strlen(line));
        //konwersja
        if(line[1] == ' '){
            sys1 = line[0]-'0';
            if(strlen(line) == 4) sys2 = line[2]-'0';
            else sys2 = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        else{
            sys1 = 10+line[1]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
            if(strlen(line) == 5) sys2 = line[3]-'0';
            else sys2 = 10+line[4]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        //printf("sys1: %i\nsys2: %i\n", sys1, sys2);
        a = read(in, 4); 
    }
    else{
        //działanie
        //printf("działanie\n");
        if(strlen(line) == 4) sys = line[2]-'0';
        else sys = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        //printf("%i\n", sys);
        a = read(in, 4);
        printf("a=%s\n", a);
        getc(in);
        getc(in);
        b = read(in, 4);
        printf("b=%s\n", b);
    }
    getc(in);
    //getc(in);
    putchar(a[0]);
    putchar(a[1]);
    //putchar(a[2]);
    if(a[2] == '\n') putchar('a');
    if(op == '+') fprintf(stdout, "%s\n", add(a, b, sys));
    else if(op == '-') fprintf(stdout, "%s\n", subtr(a, b, sys));
    else if(op == '*') fprintf(stdout, "%s\n", mult(a, b, sys));
    else if(op == '/') {
        fprintf(stdout, "%s\n", div_(a, b, sys));
        //div_pom(a, b, sys);
        //div_pom(a, b, sys);
    }
    else if(op == '^') {
        fprintf(stdout, "%s\n", qck_pow(a, b, sys));
    }
    else {
        b = sys_conv(sys1, sys2);
        printf("base2 in sys1 = %s\n", b);
        //sys_conv(sys1, sys2);
        //num_conv(a, b, sys1);
        fprintf(stdout, "%s\n", num_conv(a, b, sys1, sys2));
    }
    //free(a);
    return 0;
}
