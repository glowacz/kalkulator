#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#define A 9
#define B 16
#define BIG_BUFF 100000
#define L 2

char *read(FILE* file, size_t base_len)
{
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*base_len);
    //if(!str) return str;
    ch=getc(file);
    while(EOF != ch && ch != '\n')
    {
        str[len++] = ch;
        if(len == base_len)
        {
            str = realloc(str, sizeof(*str)*(base_len+=2));
            if(!str) return str;
        }
        ch=getc(file);
    }
    str[len++] = '\0';
    return realloc(str, sizeof(*str)*len);
}

void str_cpy(char *a, char *b)  //aktualnie nieuzywane (jest ewidentnie wolniejsze od strspy z biblioteki)
{
    int i = 0;
    while(b[i] != '\0')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

int str_len(char *a)
{
    int i = 0, len = 0;
    while(a[i] != '\0') i++;
    return i;
}

int str_cmp(char *a, char *b)
{
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

void let_to_num(char *str)
{
    for(int i=0; i<strlen(str); i++)
    {
        if(str[i]-'0' >= 10) str[i] -= 7;
    }
}

void num_to_let(char *str)
{
    int i;
    for(i=0; i<strlen(str); i++)
    {
        if(str[i]-'0' >= 10) str[i] += 7;
    }
}

int input_analysis(char *a, char *b, int sys, char op)
{
    int n = strlen(a), m = strlen(b);
    int a_is_zero = 1, b_is_zero = 1, good_sys = 1;
    let_to_num(a);
    let_to_num(b);
    for(int i=0; i<n; i++)
    {
        if(a[i]-'0' >= sys || a[i]-'0' < 0) good_sys = 0;
        if(a[i] != '0') a_is_zero = 0;
    }
    for(int i=0; i<m; i++)
    {
        if(b[i]-'0' >= sys || b[i]-'0' < 0) good_sys = 0;
        if(b[i] != '0') b_is_zero = 0;
    }
    num_to_let(a);
    num_to_let(b);
    if( good_sys == 0 ) return 1;
    if( (op == '/' || op == '%') && b_is_zero ) return 2;
    if(a[0] == '0' && !a_is_zero) return 3;
    if(b[0] == '0' && !b_is_zero) return 3;
    return 0;
}

int input_analysis_conv(char *a, int sys)
{
    if(a[0] == '0') return 3;
    int n = strlen(a);
    int good_sys = 1;
    let_to_num(a);
    for(int i=0; i<n; i++)
    {
        if(a[i]-'0' >= sys || a[i]-'0' < 0) good_sys = 0;
    }
    num_to_let(a);
    if(good_sys == 0) return 1;
    return 0;
}

int pow_(int b, int e)
{
    int res = 1;
    for(int i = 0; i < e; i++) res *= b;
    return res;
}

char *add(char *a, char *b, char **c1, int sys)
{
    int n, m, i, j_a, j_b;
    if(strlen(a) >= strlen(b))
    {
        n = strlen(a);
        m = strlen(b);
        j_b = m-1;
        j_a = INT_MAX;
    }
    else
    {
        n = strlen(b);
        m = strlen(a);
        j_a = m-1;
        j_b = INT_MAX;
    }

    let_to_num(a);
    let_to_num(b);

    *c1 = malloc(n+A);
    char *c = *c1;
    int dig[n+A];

    for(i=n; i>=0; i--) dig[i] = 0;
    for(i=n-1; i>=0; i--) 
    {
        if(j_a < 0) dig[i+1] += b[i]-'0';
        else if(j_b < 0) dig[i+1] += a[i]-'0';
        else if(strlen(a) >= strlen(b)) dig[i+1] += a[i]+b[j_b]-2*'0';
        else dig[i+1] += a[j_a]+b[i]-2*'0';

        if(dig[i+1] >= sys)
        {
            c[i+1] = dig[i+1]-sys+'0';
            dig[i] = 1;
        }
        else c[i+1] = dig[i+1]+'0';
        j_a--;
        j_b--;
    }
    c[0] = dig[0]+'0';
    c[n+1] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    return c;
}

char *mult(char *a, char *b, char **c1, int sys)
{
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    let_to_num(a);
    let_to_num(b);

    int dig_a[n+A], dig_b[m+A], dig[n+m+A], dig_main[n+m+A];
    *c1 = malloc(n+m+A);
    char *c = *c1;

    for(i=0; i<n; i++) dig_a[i] = a[i]-'0';
    for(i=0; i<m; i++) dig_b[i] = b[i]-'0';

    for(i=n+m-1; i >= 0; i--) dig_main[i] = 0;

    for(j=m-1; j>=0; j--) {
        i_c = n+j;
        for(i=i_c; i >= i_c-n; i--) dig[i] = 0;
        for(i=n-1; i >= 0; i--){
            dig[i_c] += dig_b[j]*dig_a[i];
            if(dig[i_c] >= sys) {
                dig[i_c-1] = dig[i_c]/sys;
                dig[i_c] %= sys;
            }
            i_c--;
        }
        for(i = n+j; i>=i_c; i--){
            dig_main[i] += dig[i];
            if(dig_main[i] >= sys){
                dig_main[i-1] += dig_main[i]/sys;
                dig_main[i] %= sys;
            }
        }
    }
    for(i=0; i<n+m; i++) c[i] = dig_main[i]+'0';
    c[n+m] = '\0';
    num_to_let(a);
    num_to_let(b);
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    return c;
}

char *subtr(char *a, char *b, char **c1, int sys)
{
    int n, m, i, j_b;
    n = strlen(a);
    m = strlen(b);
    j_b = m-1;
    int dig[n+A];
    *c1 = malloc(n+A);
    char *c = *c1, *a1 = malloc(n+A);

    let_to_num(a);
    let_to_num(b);

    str_cpy(a1, a);

    for(i=n; i >= 0; i--) dig[i] = 0;

    for(i=n-1; i>=0; i--) {
        if(j_b < 0) dig[i] = a1[i]-'0';
        else dig[i] = a1[i]-b[j_b];

        if(dig[i] < 0){
            a1[i-1] -= 1;
            dig[i] += sys;
        }
        c[i] = dig[i]+'0';
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

char *div_help(char *a, char *b, char **c1, int sys, int *dig)
{
    //char *a = *a1;
    //char *c1 = malloc(strlen(a)+A);
    char *tmp1 = malloc(strlen(a)+A);
    //char tmp1[strlen(a)+A];
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
    
    *dig = i;
    
    //*a1 = c;
    //free(c1);

    //printf("div help przed free\n");
    //printf("wynik: %s\n", c);
    //printf("wynik(cyfra nad kreska): %i\n", i);

    free(tmp1);

    //printf("div help po free\n");

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

    int dig_a[n+A], dig_b[m+A], dig_curr[n+A], dig = 0;
    //*c1 = (char *) realloc(*c1, n+A);
    *c1 = malloc(n+A);
    char *curr1 = malloc(m+A), *prev1 = malloc(m+A), *tmp1 = malloc(m+A), ch;
    //char curr1[m+A], prev1[m+A], tmp1[m+A], ch; //bylo dynamicznie, ale czasem pojawial sie problem z free
    char *c = *c1, *curr = curr1, *prev = prev1, *tmp = tmp1;

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
        //curr = div_help(&curr, b, sys, &dig);
        tmp = div_help(curr, b, &tmp, sys, &dig);
        str_cpy(curr, tmp);
        //curr[strlen(curr)] = '\0';
        curr[strlen(tmp)] = '\0';
        //printf("po pomnozeniu: %s\n", curr);
        c[i] = dig+'0';
        //printf("cyfra do wyniku: %i\n", cy);
        //curr = subtr(prev, curr, sys);
        tmp = subtr(prev, curr, &tmp, sys);
        str_cpy(curr, tmp);
        curr[strlen(tmp)] = '\0';
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

    free(curr1);
    free(prev1);
    free(tmp1);

    //printf("div_ po free\n");
    
    return c;
}

char *mod(char *a, char *b, char **c1, int sys)
{
    int n = strlen(a), m = strlen(b);
    char *tmp1 = malloc(n+A);
    char *tmp = tmp1;
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

char *sys_conv(int sys1, int sys2, char **b1)
{
    int curr = sys2, i = 0, pom[B];
    //char *wyn = malloc(B);
    *b1 = malloc(B);
    char *b = *b1;
    //char *wyn = malloc(B);
    while( curr != 0 ){
        pom[i] = curr % sys1;
        curr /= sys1;
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

char *num_conv(char *a, char *b, char **c1, int sys, int sys2)
{
    int i = 0, n = strlen(a);
    int cy[n*4+A];
    *c1 = malloc(n*4+A);
    char *curr1 = malloc(n+A), *inv1 = malloc(n*4+A);
    char *c = *c1, *curr = curr1, *inv = inv1;
    //char *wyn = malloc(n*4+A), *tmp = malloc(n+A);
    str_cpy(curr, a);

    while( curr[0] != '0' )
    {
        c = mod(curr, b, &c, sys);
        inv[i] =  dig_conv(c, sys, sys2)+'0';
        //tmp = div_(curr, b, sys);
        c = div_(curr, b, &c, sys);
        str_cpy(curr, c);
        i++;
    }
    int m = i;
    for(i=0; i<m; i++) 
    {
        c[i] = inv[m-i-1];
    }
    c[m] = '\0';
    num_to_let(c);

    free(curr1);
    free(inv1);

    return c;
}

char *basic_pow(char *b, char *e, char **c1, int sys)
{
    int n, m;
    n = strlen(b);
    m = strlen(e);
    
    *c1 = malloc(BIG_BUFF);
    char *tmp1 = malloc(BIG_BUFF), *curr_e1 = malloc(m+A);
    char *c = *c1, *tmp = tmp1, *curr_e = curr_e1;
    
    c[0] = '1'; c[1] = '\0';
    curr_e[0] = '0'; curr_e[1] = '\0';
    
    int i = 0;
    while( str_cmp(e, curr_e) != 0 )
    {
        tmp = mult(c, b, &tmp, sys);
        str_cpy(c, tmp);
        tmp = add(curr_e, "1", &tmp, sys);
        str_cpy(curr_e, tmp);
        i++;
        //if(i > 20) printf("spore wykladniki\n");
    }

    free(tmp1);
    free(curr_e1);

    return c;
}

/*char *qck_pow(char *b, char *e, int sys){
    char *help = malloc(strlen(e)+A);
    if(str_cmp(e, "0") == 0) return "1";
    if(str_cmp(e, "1") == 0) {
        str_cpy(help, b);
        return help;
    }
    else if(sys == 2){
        help = div_(e, "10", sys);
        if(str_cmp(mult(help, "10", sys), e) == 0) return mult(qck_pow(b, help, sys), qck_pow(b, help, sys), sys);
        else return mult(qck_pow(b, subtr(e, "1", sys), sys), b, sys);
    }
    else{
        help = div_(e, "2", sys);
        if(str_cmp(mult(help, "2", sys), e) == 0) return mult(qck_pow(b, help, sys), qck_pow(b, help, sys), sys);
        else return mult(qck_pow(b, subtr(e, "1", sys), sys), b, sys);
    }
}*/

int main(int argc, char *argv[])
//int main()
{
    FILE *in;
    if(argc == 2) in = fopen(argv[1], "r");
    else in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    //FILE *out = stdout;
    
    char *a, *b, *c, *d, *bin, *line, op, ch;
    int sys, sys1, sys2, n, m, line_len, err;
    
    while(1)
    {
    line = read(in, L);
    bin = read(in, L);
    line_len = strlen(line);
    if(line_len == 0) break;
    line[line_len] = '\0';
    line_len = strlen(line);
    op = line[0];
    //printf("dl_linii=%i\n", line_len);
    //printf("linia=%s\n", line);

    if(op >= 48 && op <= 57)
    {
        //konwersja
        if(line[1] == ' ')
        {
            sys1 = line[0]-'0';
            if(line_len == 3) sys2 = line[2]-'0';
            else sys2 = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        else
        {
            sys1 = 10+line[1]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
            if(line_len == 4) sys2 = line[3]-'0';
            else sys2 = 10+line[4]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych
        }
        a = read(in, L);
        bin = read(in, L);
        bin = read(in, L);

        n = strlen(a);

        a[n] = '\0';
        fprintf(out, "%s\n\n%s\n\n", line, a);
        
        //while(strlen(a) > 1 && a[0] == '0') a++;
        
        err = input_analysis_conv(a, sys1);
        if( err != 0 )
        {
            if( err == 1 ) fprintf( out, "NaN\n\n\n" );
            if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n\n" );
            continue;
        }
    }
    else
    {
        //działanie
        if(line_len == 3) sys = line[2]-'0';
        else sys = 10+line[3]-'0'; //korzysta z faktu, że nie ma systemów 20stkowych i większych

        a = read(in, L);
        bin = read(in, L);
        b = read(in, L);
        bin = read(in, L);
        bin = read(in, L);

        n = strlen(a);
        m = strlen(b);

        a[n] = '\0';
        b[m] = '\0';

        n = strlen(a);
        m = strlen(b);

        fprintf(out, "%s\n\n%s\n\n%s\n\n", line, a, b);

        //while(strlen(a) > 1 && a[0] == '0') a++;
        //while(strlen(b) > 1 && b[0] == '0') b++;

        err = input_analysis(a, b, sys, op);
        if( err != 0 ) 
        {
            if( err == 1 ) fprintf( out, "NaN\n\n\n" );
            if( err == 2 ) fprintf( out, "DIVISION_BY_ZERO\n\n\n" );
            if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n\n" );
            //fprintf( out, "error code %i\n\n", err );
            continue;
        }
    }
    
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
    else if(op == '^') 
    {
        //c = qck_pow(a, b, sys);
        //c = qck_pow(a, b, sys);
        //if( m > 2 ) printf("spore wykladniki\n");
        fprintf(out, "%s\n\n\n", basic_pow(a, b, &c, sys));
    }
    else 
    {
        b = sys_conv(sys1, sys2, &b);
        //printf("base 2 in sys 1:\n%s\n", b);
        fprintf(out, "%s\n\n\n", num_conv(a, b, &c, sys1, sys2));
    }
    
    }

    free(a); free(b); free(line); free(bin);
    free(c); //czasami (rzadko) przy div_ byl problem z free(c)
    
    return 0;
}
