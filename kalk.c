#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#define A 9
#define B 16
#define L 2
#define BUF 100000

char *read(FILE* file, size_t base_len){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*base_len);
    //if(!str) return str;
    ch=getc(file);
    while(EOF != ch && ch != '\n'){
        //printf("read\n");
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

void str_cpy(char *a, char *b){ //aktualnie nieuzywane (jest ewidentnie wolniejsze)
    int i = 0;
    while(b[i] != '\0'){
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

int str_len(char *a){
    int i = 0, len = 0;
    while(a[i] != '\0') i++;
    return i;
}

int str_cmp(char *a, char *b){
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0'){
        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;
        i++;
    }
    if(a[i] == '\0' && b[i] == '\0') return 0;
    if(a[i] == '\0') return -1;
    return 1;
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
    //printf("hello\n");
    //printf("hello2\n");
    int n = strlen(a), m = strlen(b);
    int is_zero = 1, good_sys = 1;
    let_to_num(a);
    let_to_num(b);
    //printf("a=%s\nb=%s\nn=%i\nm=%i\nsys=%i\n", a, b, n, m, sys);
    for(int i=0; i<n; i++){
        if(a[i]-'0' >= sys || a[i]-'0' < 0) {
            //printf("a, %i\n", i); 
            good_sys = 0;
        }
    }
    for(int i=0; i<m; i++){
        if(b[i]-'0' >= sys || b[i]-'0' < 0){
            //printf("b, %i\n", i); 
            good_sys = 0;
        }
        if(b[i] != '0') is_zero = 0;
    }
    num_to_let(a);
    num_to_let(b);
    if( good_sys == 0 ) return 1;
    if( (op == '/' || op == '%') && is_zero ) return 2;
    //if(a[0] == '0') return 3;
    //if(b[0] == '0') return 3;
    return 0;
}

int input_analysis_conv(char *a, int sys){
    if(a[0] == '0') return 3;
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

char *add(char *a, char *b, char **c1, int sys){
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

    *c1 = malloc(n+A);
    char *c = *c1;
    int cy[n+A];
    //char *c = malloc(n+A);

    for(i=n; i>=0; i--) cy[i] = 0;
    //printf("hello\n");
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
        //printf("hello\n");
        j_a--;
        j_b--;
    }
    c[0] = cy[0]+'0';
    c[n+1] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    //fprintf(out, "%s\n\n\n", c);
    
    //free(c);
    //printf("hello\n");
    return c;
}

char *mult(char *a, char *b, char **c1, int sys){
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    let_to_num(a);
    let_to_num(b);

    int cy_a[n+A], cy_b[m+A], cy[n+m+A], cy_main[n+m+A];
    *c1 = malloc(n+m+A);
    char *c = *c1;

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

    return c;
}

char *subtr(char *a, char *b, char **c1, int sys){
    int n, m, i, j_b;
    n = strlen(a);
    m = strlen(b);
    j_b = m-1;
    int cy[n+A];
    *c1 = malloc(n+A);
    char *c = *c1, *a1 = malloc(n+A);

    let_to_num(a);
    let_to_num(b);

    str_cpy(a1, a);
    //strcpy(a1, a);
    //a1 = a;

    for(i=n; i >= 0; i--) cy[i] = 0;

    for(i=n-1; i>=0; i--) {
        if(j_b < 0) cy[i] = a1[i]-'0';
        else cy[i] = a1[i]-b[j_b];

        if(cy[i] < 0){
            a1[i-1] -= 1;
            cy[i] += sys;
        }
        c[i] = cy[i]+'0';
        j_b--;
    }
    c[n] = '\0';
    
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);
    
    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;
    
    free(a1);
    
    return c;
}

char *div_pom(char *a, char *b, char **c1, int sys, int *cy){
    //char *a = *a1;
    //char *c1 = malloc(strlen(a)+A);
    //char *tmp1 = malloc(strlen(a)+A);
    char tmp1[strlen(a)+A];
    char *tmp = tmp1;
    char *c = *c1;
    //c[0] = '\0';
    str_cpy(c, b);
    int i = 1;
    
    while(a[0] == '0') a++;
    
    while( strlen(c) < strlen(a) || (strlen(c) == strlen(a) && str_cmp(c, a) < 0) )
    {
        tmp = add(c, b, &tmp, sys);
        //printf("dl tmp = %i\n", strlen(tmp));
        str_cpy(c, tmp);
        //printf("dl tmp = %i\n", strlen(tmp));
        i++;
        //printf("akt (c) = %s\ni = %i\n", c, i);
        //printf("dl c = %i\ndl a = %i\n", strlen(c), strlen(a));
    }
    
    if(str_cmp(a, c) != 0) 
    {
        i--;
        tmp = subtr(c, b, &tmp, sys);
        str_cpy(c, tmp);
    }
    
    *cy = i;
    
    //*a1 = c;
    //free(c1);

    //printf("div pom przed free\n");
    //printf("wynik: %s\n", c);
    //printf("wynik(cyfra nad kreska): %i\n", i);

    //free(tmp1);

    //printf("div pom po free\n");

    /*if(i == 0){
        c[0] = '0';
        c[1] = '\0';
    }*/
    
    return c;
}

char *div_(char *a, char *b, char **c1, int sys)
{
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    int cy_a[n+A], cy_b[m+A], cy_curr[n+A], cy = 0;
    //*c1 = (char *) realloc(*c1, n+A);
    *c1 = malloc(n+A);
    //char *curr1 = malloc(m+A), *prev1 = malloc(m+A), *temp1 = malloc(m+A), ch;
    char curr1[m+A], prev1[m+A], temp1[m+A], ch; //bylo dynamicznie, ale czasem pojawial sie problem z free
    char *c = *c1, *curr = curr1, *prev = prev1, *temp = temp1;

    for(i=0; i<n; i++) c[i] = '0';

    //printf("hello\n");

    for(i=m-1; i<n; i++)
    {
        //printf("i=%i\n", i);
        if(i == m-1)
        {
            ch = a[i+1];
            a[i+1] = '\0';
            str_cpy(curr, a);
            //curr[strlen(curr)] = '\0';
            curr[strlen(a)] = '\0';
        }
        else
        {
            ch = a[i+1];
            a[i+1] = '\0';
        }
        //printf("curr=%s\n", curr);
        str_cpy(prev, curr);
        prev[strlen(prev)] = '\0';
        //curr = div_pom(&curr, b, sys, &cy);
        temp = div_pom(curr, b, &temp, sys, &cy);
        str_cpy(curr, temp);
        //curr[strlen(curr)] = '\0';
        curr[strlen(temp)] = '\0';
        //printf("po pomnozeniu: %s\n", curr);
        c[i] = cy+'0';
        //printf("cyfra do wyniku: %i\n", cy);
        //curr = subtr(prev, curr, sys);
        temp = subtr(prev, curr, &temp, sys);
        str_cpy(curr, temp);
        curr[strlen(temp)] = '\0';
        //printf("po odjeciu: %s\n", curr);
        //printf("strlen po odjeciu: %li\n", strlen(curr));
        a[i+1] = ch;
        //printf("cyfra do dopisania: %c\n", ch);
        int len = strlen(curr);
        curr[strlen(curr)] = ch;
        //printf("strlen po dopisaniu: %li\n", strlen(curr));
        curr[len+1] = '\0';
        //printf("po dopisaniu: %s\n", curr);
    }
    
    c[n] = '\0';
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    //printf("div_ przed free\n");
    //printf("c=%s\n", c);

    /*free(curr1);
    free(prev1);
    free(temp1);*/

    //printf("div_ po free\n");
    
    return c;
}

char *mod(char *a, char *b, char **c1, int sys){
    int n = strlen(a), m = strlen(b);
    char *tmp1 = malloc(n+A);
    char *tmp = tmp1;
    //char tmp[n+A];
    *c1 = malloc(n+A);
    char *c = *c1;
    tmp = div_(a, b, &tmp, sys);
    str_cpy(c, tmp);
    tmp = mult(c, b, &tmp, sys);
    str_cpy(c, tmp);
    tmp = subtr(a, c, &tmp, sys);
    str_cpy(c, tmp);
    free(tmp1);
    return c;
}

/*char *sys_conv(int sys1, int sys2, char **b1){
    int akt = sys2, i = 0, pom[B];
    //char *wyn = malloc(B);
    *b1 = malloc(B);
    char *c = *b1;
    //char *wyn = malloc(B);
    while( akt != 0 ){
        pom[i] = akt % sys1;
        akt /= sys1;
        i++;
    }
    int n = i;
    for(i=0; i<n; i++) {
        b[i] = pom[n-i-1]+'0';
    }
    b[n] = '\0';
    num_to_let(b);
    return b;
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
    char *akt = malloc(n+A), *c;
    char *wyn = malloc(n*4+A), *pom = malloc(n*4+A), *tmp = malloc(n+A);
    str_cpy(akt, a);

    while( akt[0] != '0' ){
        c = mod(akt, b, sys);
        pom[i] =  dig_conv(c, sys, sys2)+'0';
        tmp = div_(akt, b, sys);
        str_cpy(akt, tmp);
        i++;
    }
    int m = i;
    for(i=0; i<m; i++) {
        wyn[i] = pom[m-i-1];
    }
    wyn[m] = '\0';
    num_to_let(wyn);

    return wyn;
}

char *qck_pow(char *b, char *e, int sys){
    char *pom = malloc(strlen(e)+A);
    if(str_cmp(e, "0") == 0) return "1";
    if(str_cmp(e, "1") == 0) {
        str_cpy(pom, b);
        return pom;
    }
    else if(sys == 2){
        pom = div_(e, "10", sys);
        if(str_cmp(mult(pom, "10", sys), e) == 0) return mult(qck_pow(b, pom, sys), qck_pow(b, pom, sys), sys);
        else return mult(qck_pow(b, subtr(e, "1", sys), sys), b, sys);
    }
    else{
        pom = div_(e, "2", sys);
        if(str_cmp(mult(pom, "2", sys), e) == 0) return mult(qck_pow(b, pom, sys), qck_pow(b, pom, sys), sys);
        else return mult(qck_pow(b, subtr(e, "1", sys), sys), b, sys);
    }
}*/

int main(int argc, char *argv[])
//int main()
{
    //printf("hello\n");
    //FILE *in = fopen("in_tes.txt", "r");
    FILE *in = fopen(argv[1], "r");
    //FILE *out = fopen("wzo.out", "w");
    FILE *out = fopen("out.txt", "w");
    char *a, *b, *c, *d, *bin, *line, op, ch;
    int sys, sys1, sys2, n, m, line_len, err;   
    size_t bufsize = BUF;
    //FILE *out = stdout;
    while(1){
    //printf("przed read\n");
    line = read(in, L);
    //printf("po read\n");
    bin = read(in, L);
    line_len = strlen(line);
    if(line_len == 0) break;
    //line[line_len-1] = '\0';
    line[line_len] = '\0';
    line_len = strlen(line);
    op = line[0];
    //printf("dl_linii=%i\n", line_len);
    //printf("linia=%s\n", line);

    if(op >= 48 && op <= 57){
        //konwersja
        if(line[1] == ' '){
            sys1 = line[0]-'0';
            if(line_len == 3) sys2 = line[2]-'0';
            else sys2 = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        else{
            sys1 = 10+line[1]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
            if(line_len == 4) sys2 = line[3]-'0';
            else sys2 = 10+line[4]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        //a = read(in, 4); 
        /*getline(&a, &bufsize, in);
        getline(&bin, &bufsize, in);
        getline(&bin, &bufsize, in);
        a[strlen(a)-2] = '\0';*/

        a = read(in, L);
        bin = read(in, L);
        bin = read(in, L);

        n = strlen(a);

        a[n] = '\0';
        fprintf(out, "%s\n\n%s\n\n", line, a);
        
        //while(strlen(a) > 1 && a[0] == '0') a++;
        
        err = input_analysis_conv(a, sys1);
        if( err != 0 ){
            if( err == 1 ) fprintf( out, "NaN\n\n\n" );
            if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n\n" );
            continue;
        }
    }
    else{
        //działanie
        if(line_len == 3) sys = line[2]-'0';
        else sys = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych

        //printf("sys=%i\n", sys);

        a = read(in, L);
        bin = read(in, L);
        b = read(in, L);
        bin = read(in, L);
        bin = read(in, L);

        n = strlen(a);
        m = strlen(b);

        /*a[n-1] = '\0';
        b[m-1] = '\0';*/

        a[n] = '\0';
        b[m] = '\0';

        n = strlen(a);
        m = strlen(b);

        fprintf(out, "%s\n\n%s\n\n%s\n\n", line, a, b);

        //while(strlen(a) > 1 && a[0] == '0') a++;
        //while(strlen(b) > 1 && b[0] == '0') b++;

        err = input_analysis(a, b, sys, op);
        if( err != 0 ) {
            if( err == 1 ) fprintf( out, "NaN\n\n\n" );
            if( err == 2 ) fprintf( out, "DIVISION_BY_ZERO\n\n\n" );
            if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n\n" );
            //fprintf( out, "error code %i\n\n", err );
            continue;
        }
    }
    
    //printf("a=%s\nb=%s\n", a, b);
    
    //if(op == '+') add(a, b, sys, out);
    if(op == '+') 
    {
        fprintf(out, "%s\n\n\n", add(a, b, &c, sys));
    }
    else if(op == '-') 
    {
        fprintf(out, "%s\n\n\n", subtr(a, b, &c, sys));
    }
    else if(op == '*') 
    {
        //c = malloc(n+m+A);
        fprintf(out, "%s\n\n\n", mult(a, b, &c, sys));
    }
    else if(op == '/') 
    {
        fprintf(out, "%s\n\n\n", div_(a, b, &c, sys));
    }
    
    else if(op == '%') 
    {
        fprintf(out, "%s\n\n\n", mod(a, b, &c, sys));
    }
    /*else if(op == '^') {
        //let_to_num(a);
        //let_to_num(b);
        //if( str_cmp(b, "0") == 0 ) return a;
        c = qck_pow(a, b, sys);
        //num_to_let(c);
        fprintf(out, "%s\n\n\n", c);
    }
    else {
        b = sys_conv(sys1, sys2, &b);
        fprintf(out, "%s\n\n\n", num_conv(a, b, sys1, sys2));
    }*/
    
    //printf("main przed free\n");
    free(a);
    free(b);
    //printf("main przed free c\n");
    free(c); //czasami (rzadko) przy div_ byl problem z free(c)
    //printf("main po free c\n");
    free(line);
    free(bin);
    //printf("main po free\n");
    }
    return 0;
}
