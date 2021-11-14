#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//#include <math.h>
//#define max(x, y) (x > y) ? (x) : (y)
#define A 10

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

int input_analysis(char *a, char *b, int sys, char op){
    int n = strlen(a), m = strlen(b);
    int is_zero = 1, good_sys = 1;
    let_to_num(a);
    let_to_num(b);
    //printf("a=%s\nb=%s\nn=%i\nm=%i\nsys=%i\n", a, b, n, m, sys);
    for(int i=0; i<n; i++){
        if(a[i]-'0' >= sys || a[i]-'0' < 0) {
            //printf("bad sys at i=%i\n%i\n", i, a[i]-'0'); 
            good_sys = 0;
        }
    }
    for(int i=0; i<m; i++){
        if(b[i]-'0' >= sys || b[i]-'0' < 0) good_sys = 0;
        if(b[i] != '0') is_zero = 0;
    }
    num_to_let(a);
    num_to_let(b);
    if( good_sys == 0 ) return 1;
    if( (op == '/' || op == '%') && is_zero ) return 2;
    //if( (op == '/' || op == '%' || op == '-') && (n<m || (n == m && strcmp(a, b) < 0) ) ) return 3;
    return 0;
}

int input_analysis_conv(char *a, int sys){
    int n = strlen(a);
    int good_sys = 1;
    let_to_num(a);
    for(int i=0; i<n; i++){
        if(a[i]-'0' >= sys || a[i]-'0' < 0) good_sys = 0;
    }
    num_to_let(a);
    if(good_sys == 0) return 1;
    return 0;
}

int pow_(int b, int e){
    int res = 1;
    for(int i = 0; i < e; i++) res *= b;
    return res;
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
    char *c = malloc(n+A);

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
    int cy[n+1];
    char *a1 = malloc(n+A), *c = malloc(n+A);

    let_to_num(a);
    let_to_num(b);

    strcpy(a1, a);

    for(i=n; i >= 0; i--) cy[i] = 0;

    for(i=n-1; i>=0; i--) {
        //printf("%i\n", i);
        if(j_b < 0) cy[i] = a1[i]-'0';
        else cy[i] = a1[i]-b[j_b];

        if(cy[i] < 0){
            a1[i-1] -= 1;
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

    //printf("mnozenie\n%i %i\n", n, m);

    int cy_a[n+A], cy_b[m+A], cy[n+m+A], cy_main[n+m+A];
    char *c = malloc(n+m+A);

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
    //for(i=0; i<n+m; i++) printf("%i", cy_main[i]);
    //printf("\n");
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
    char *c = malloc(strlen(a)+A);
    //char c = [strlen(a)+A];
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
    //printf("dzielenie\n");
    //printf("a=%s\nb=%s\n", a, b); //printf("b=%s\n", b);
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);
    //printf("a=%s\nb=%s\nn=%i\nm=%i\n", a, b, n, m); //printf("b=%s\n", b);

    int cy_a[n+A], cy_b[m+A], cy = 0, cy_curr[n+A];
    char *c = malloc(n+A), *curr = malloc(m+A), *prev = malloc(m+A), ch;

    for(i=0; i<n; i++) c[i] = '0';

    for(i=m-1; i<n; i++){

        if(i == m-1){
            ch = a[i+1];
            //printf("char do dopisania: %c\n", ch);
            a[i+1] = '\0';
            //curr = a;
            strcpy(curr, a);
        }
        else{
            ch = a[i+1];
            //printf("char do dopisania: %c\n", ch);
            a[i+1] = '\0';
        }
        //prev = curr;
        strcpy(prev, curr);
        //printf("curr: %s\n", curr);
        curr = div_pom(curr, b, sys, &cy);
        //printf("wyn div_pom: %s\n", curr);
        c[i] = cy+'0';
        //printf("cyfra nad kreska: %c\n", c[i]);
        //printf("odejmowanie: %s\n%s\n", prev, curr);
        curr = subtr(prev, curr, sys);
        //printf("po odjeciu: %s\n", curr);
        a[i+1] = ch;
        curr[strlen(curr)] = ch;
        curr[strlen(curr)] = '\0';
        //printf("po dopisaniu: %s\n", curr);
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

char *mod(char *a, char *b, int sys){
    //printf("przed mod\na = %s\nb = %s\n", a, b);
    char *c;
    c = div_(a, b, sys);
    //printf("wynik dzielenia: %s\n", c);
    c = mult(c, b, sys);
    c = subtr(a, c, sys);
    //printf("po mod\na = %s\nb = %s\n", a, b);
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
    int i = 0, n = strlen(a);
    int cy[n*4+A];
    //char *akt = a, *prev, *wyn = malloc(n*4), *pom = malloc(n*4);
    //char *akt = (char*)malloc(n+A*sizeof(char)), *prev = malloc(n+A), *wyn = malloc(n*4+A), *pom = malloc(n*4+A), *c = malloc;
    //char *akt, *c, *wyn = (char*)malloc((n*4+A)*sizeof(char)), *pom = (char*)malloc((n*4+A)*sizeof(char));
    char *akt = malloc(n+A), *c;
    //char *akt, *c;
    char *wyn = malloc(n*4+A), *pom = malloc(n*4+A), *tmp = malloc(n+A);
    strcpy(akt, a);
    //printf("hello3\n");

    while( akt[0] != '0' ){
        //prev = akt;
        
        //strcpy(prev, akt);
        
        //printf("akt=%s\n", akt);
        //printf("prev=%s\n", prev);
        c = mod(akt, b, sys);
        pom[i] =  dig_conv(c, sys, sys2)+'0';
        tmp = div_(akt, b, sys);
        strcpy(akt, tmp);
        //printf("reszta z dzielenia: %s\n", c);
        //printf("akt2=%s\n", akt);
        //printf("akt(po dzieleniu)=%s\n", akt);
        //printf("prev=%s\n", prev);
        //printf("po mnozeniu=%s\n", mult(akt, b, sys));
        //printf("%s\n", subtr(prev, mult(akt, b, sys), sys));
        //pom[i] =  dig_conv(subtr(prev, mult(akt, b, sys), sys), sys, sys2)+'0';
        //printf("%c\n", pom[i]);
        i++;
    }
    int m = i;
    for(i=0; i<m; i++) {
        wyn[i] = pom[m-i-1];
    }
    wyn[m] = '\0';
    //printf("wyn=%s\n", wyn);
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
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    //FILE *out = stdout;
    while(1){
    //char *a, *b, *c, op, *line = malloc(10);
    size_t bufsize = 1;
    char *a = malloc(bufsize*sizeof(char)), *b = malloc(bufsize*sizeof(char)), *bin = malloc(bufsize*sizeof(char)), *c, op, *line = malloc(bufsize*sizeof(char)), ch;
    int sys, sys1, sys2, n, m, line_len, err;    
    //FILE *in = stdin;
    /*while(ch != '\n'){
        line[i++] = ch;
        putchar(ch);
        ch = getc(in);
    }*/
    getline(&line, &bufsize, in);
    line_len = strlen(line);
    if(line_len == 0) break;
    line[line_len-2] = '\0';
    getline(&bin, &bufsize, in);
    op = line[0];
    //printf("op=%c\n", op);
    //printf("%i", line[0] == EOF);
    //printf("dl_linii=%i\n", line_len);

    if(op >= 48 && op <= 57){
        //printf("%c\n", line[1]);
        //printf("%i\n", line_len);
        //konwersja
        if(line[1] == ' '){
            sys1 = line[0]-'0';
            if(line_len == 5) sys2 = line[2]-'0';
            else sys2 = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        else{
            sys1 = 10+line[1]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
            if(line_len == 6) sys2 = line[3]-'0';
            else sys2 = 10+line[4]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        //a = read(in, 4); 
        getline(&a, &bufsize, in);
        getline(&bin, &bufsize, in);
        getline(&bin, &bufsize, in);
        a[strlen(a)-2] = '\0';
        fprintf(out, "%s\n\n%s\n\n", line, a);
        err = input_analysis_conv(a, sys1);
        if( err != 0 ){
            if( err == 1 ) fprintf( out, "NaN\n\n" );
            //fprintf(out, "error\n\n");
            continue;
        }
        //printf("sys1: %i\nsys2: %i\n", sys1, sys2);
    }
    else{
        //działanie
        //printf("działanie\n");
        //printf("sys = %i\n", sys);
        if(line_len == 5) sys = line[2]-'0';
        else sys = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        
        getline(&a, &bufsize, in);
        getline(&bin, &bufsize, in);
        getline(&b, &bufsize, in);
        getline(&bin, &bufsize, in);
        getline(&bin, &bufsize, in);

        a[strlen(a)-2] = '\0';
        b[strlen(b)-2] = '\0';

        fprintf(out, "%s\n\n%s\n\n%s\n\n", line, a, b);

        err = input_analysis(a, b, sys, op);
        if( err != 0 ) {
            if( err == 1 ) fprintf( out, "NaN\n\n" );
            if( err == 2 ) fprintf( out, "DIVISION_BY_ZERO\n\n" );
            //fprintf( out, "error code %i\n\n", err );
            continue;
        }
    }
    
    //printf("a=%s\nb=%s\n", a, b);
    
    if(op == '+') fprintf(out, "%s\n\n\n", add(a, b, sys));
    else if(op == '-') fprintf(out, "%s\n\n\n", subtr(a, b, sys));
    else if(op == '*') fprintf(out, "%s\n\n\n", mult(a, b, sys));
    else if(op == '/') {
        fprintf(out, "%s\n\n\n", div_(a, b, sys));
        //div_pom(a, b, sys);
        //div_pom(a, b, sys);
    }
    else if(op == '^') {
        fprintf(out, "%s\n\n\n", qck_pow(a, b, sys));
    }
    else if(op == '%') {
        //fprintf(out, "mialo nie byc modulo\n\n");
        fprintf(out, "%s\n\n\n", mod(a, b, sys));
    }
    else {
        b = sys_conv(sys1, sys2);
        //printf("sys1 = %i\nsys2 = %i\n", sys1, sys2);
        //printf("base2 in sys1 = %s\n", b);
        //sys_conv(sys1, sys2);
        //num_conv(a, b, sys1);
        fprintf(out, "%s\n\n\n", num_conv(a, b, sys1, sys2));
    }
    /*free(a);
    free(b);
    free(line);
    free(bin);*/
    //printf("%i", bin[0] == EOF);
    }
    return 0;
}
