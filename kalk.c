#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#define A 9
#define B 16
#define BIG_BUFF 100000
#define L 4

char *read(FILE* file, size_t base_len);

void str_cpy(char *a, char *b);

int str_len(char *a); //currently not utilized, it is significantly slower than strlen from <string.h>

int str_cmp(char *a, char *b);

void let_to_num(char *str);

void num_to_let(char *str);

int input_analysis(char *a, char *b, int sys, char op);

int input_analysis_conv(char *a, int sys);

int pow_(int b, int e);

char *add(char *a, char *b, char **c1, int sys);

char *mult(char *a, char *b, char **c1, int sys);

char *subtr(char *a, char *b, char **c1, int sys);

char *div_help(char *a, char *b, char **c1, int sys, int *dig);

char *div_(char *a, char *b, char **c1, int sys);

char *mod(char *a, char *b, char **c1, int sys);

char *sys_conv(int sys1, int sys2, char **b1);

int dig_conv(char *str, int sys1, int sys2);

char *num_conv(char *a, char *b, char **c1, int sys, int sys2);

char *basic_pow(char *b, char *e, char **c1, int sys);

int main(int argc, char *argv[])
{
    FILE *in, *out;
    in = fopen("in.txt", "r");
    if(argc == 1) out = fopen("out.txt", "w");
    
    char *a, *b, *c, *bin, *line, op, file_name[B], file_index[B];
    int sys, sys1, sys2, n, m, line_len, err, i = 1;
    
    while(1)
    {
        a = (char *)malloc(1), b = (char *)malloc(1), c = (char *)malloc(1), bin = (char *)malloc(1), line = (char *)malloc(1);

        line = read(in, L);
        
        bin = read(in, L);
        
        line_len = strlen(line);
        if(line_len == 0) break;
        line[line_len] = '\0';
        line_len = strlen(line);

        if( argc == 2 && str_cmp(argv[1], "1") == 0 )
        {
            str_cpy(file_name, "out");
            file_index[0] = i+'0'; file_index[1] = '\0';
            strcat( file_name, file_index );
            strcat(file_name, ".txt");
            out = fopen(file_name, "w");
        }
        
        op = line[0];

        if(op >= 48 && op <= 57)
        {
            //conversion
            if(line[1] == ' ')
            {
                sys1 = line[0]-'0';
                if(line_len == 3) sys2 = line[2]-'0';
                else sys2 = 10+line[3]-'0'; //makes use of the fact that there are no base-20 or larger systems in project requirements
            }
            else
            {
                sys1 = 10+line[1]-'0'; //makes use of the fact that there are no base-20 or larger systems in project requirements
                if(line_len == 4) sys2 = line[3]-'0';
                else sys2 = 10+line[4]-'0'; //makes use of the fact that there are no base-20 or larger systems in project requirements
            }
            
            a = read(in, L);
            
            bin = read(in, L);
            bin = read(in, L);

            n = strlen(a);

            a[n] = '\0';
            
            fprintf(out, "%s\n\n%s\n\n", line, a);
            
            err = input_analysis_conv(a, sys1);
            if( err != 0 )
            {
                if( err == 1 ) fprintf( out, "NaN\n\n" );
                if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n" );
                continue;
            }
        }
        else
        {
            //operation
            if(line_len == 3) sys = line[2]-'0';
            else sys = 10+line[3]-'0'; //makes use of the fact that there are no base-20 or larger systems in project requirements

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

            err = input_analysis(a, b, sys, op);
            if( err != 0 ) 
            {
                if( err == 1 ) fprintf( out, "NaN\n\n" );
                if( err == 2 ) fprintf( out, "DIVISION_BY_ZERO\n\n" );
                if( err == 3 ) fprintf( out, "TRAILING_ZEROES\n\n" );
                if( err == 4 ) fprintf( out, "SUBTRACTING_BIGGER_NUMBER_FROM_SMALLER\n\n" );
                i++;
                continue;
            }
        }
        
        if(op == '+')
        {
            fprintf(out, "%s\n\n", add(a, b, &c, sys));
        }
        else if(op == '-')
        {
            fprintf(out, "%s\n\n", subtr(a, b, &c, sys));
        }
        else if(op == '*')
        {
            fprintf(out, "%s\n\n", mult(a, b, &c, sys));
        }
        else if(op == '/') 
        {
            fprintf(out, "%s\n\n", div_(a, b, &c, sys));
        }
        
        else if(op == '%') 
        {
            fprintf(out, "%s\n\n", mod(a, b, &c, sys));
        }
        else if(op == '^') 
        {
            fprintf(out, "%s\n\n", basic_pow(a, b, &c, sys));
        }
        else 
        {
            b = sys_conv(sys1, sys2, &b);
            fprintf(out, "%s\n\n\n", num_conv(a, b, &c, sys1, sys2));
        }
        i++;
        
        free(a); free(b); 
        free(c);
        free(line); free(bin);
    }
    
    return 0;
}

char *read(FILE* file, size_t base_len)
{
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, base_len);
    ch=getc(file);
    while(EOF != ch && ch != '\n')
    {
        str[len++] = ch;
        if(len == base_len)
        {
            str = realloc(str, base_len+=L);
            if(!str) return str;
        }
        ch=getc(file);
    }
    str[len++] = '\0';
    return realloc(str, len);
}

void str_cpy(char *a, char *b)
{
    int i = 0;
    while(b[i] != '\0')
    {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

int str_len(char *a) //currently not utilized, it is significantly slower than strlen from <string.h>
{
    int i = 0, len = 0;
    while(a[i] != '\0') i++;
    return i;
}

int str_cmp(char *a, char *b)
{
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0')
    {
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
    for(int i=0; i<strlen(str); i++)
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
    if( (op == '-') && (n < m || (n == m && str_cmp(a, b) < 0) ) ) return 4;
    
    return 0;
}

int input_analysis_conv(char *a, int sys)
{   
    int n = strlen(a);
    int good_sys = 1;
    
    if(a[0] == '0' && n > 1) return 3;

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

    int dig[n+A];

    *c1 = (char *)realloc(*c1, n+A);
    if(!*c1) printf("invalid pointer\n");
    char *c = *c1;

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
    
    *c1 = (char *)realloc(*c1, n+m+A);
    char *c = *c1;

    for(i=0; i<n; i++) dig_a[i] = a[i]-'0';
    for(i=0; i<m; i++) dig_b[i] = b[i]-'0';

    for(i=n+m-1; i >= 0; i--) dig_main[i] = 0;

    for(j=m-1; j>=0; j--)
    {
        i_c = n+j;
        for(i=i_c; i >= i_c-n; i--) dig[i] = 0;
        for(i=n-1; i >= 0; i--)
        {
            dig[i_c] += dig_b[j]*dig_a[i];
            if(dig[i_c] >= sys)
            {
                dig[i_c-1] = dig[i_c]/sys;
                dig[i_c] %= sys;
            }
            i_c--;
        }
        for(i = n+j; i>=i_c; i--)
        {
            dig_main[i] += dig[i];
            if(dig_main[i] >= sys)
            {
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
    
    *c1 = (char *)realloc(*c1, n+A);
    char *c = *c1, *a1 = (char *)malloc(n+A);

    let_to_num(a);
    let_to_num(b);

    str_cpy(a1, a);

    for(i=n; i >= 0; i--) dig[i] = 0;

    for(i=n-1; i>=0; i--) 
    {
        if(j_b < 0) dig[i] = a1[i]-'0';
        else dig[i] = a1[i]-b[j_b];

        if(dig[i] < 0)
        {
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
    int i = 1;

    char *tmp1 = (char *)malloc(strlen(a)+A);
    char *c = *c1, *tmp = tmp1;
    //char *tmp = (char *)malloc(strlen(a)+A);
    //char *c = *c1;
    
    str_cpy(c, b);
 
    while(a[0] == '0') a++;
    
    while( strlen(c) < strlen(a) || (strlen(c) == strlen(a) && str_cmp(c, a) < 0) )
    {
        //printf("tmp1 = %s, %i\n", tmp1, &tmp1);
        //printf("tmp = %s\n", tmp);
        //tmp = add(c, b, &tmp, sys);
        tmp = add(c, b, &tmp1, sys);
        str_cpy(c, tmp);
        i++;
    }
    //printf("hello\n");
    
    if(str_cmp(a, c) != 0) 
    {
        i--;
        //tmp = subtr(c, b, &tmp, sys);
        tmp = subtr(c, b, &tmp1, sys);
        str_cpy(c, tmp);
    }
    
    *dig = i;

    //printf("tmp1 = %s\n", tmp1);
    //printf("tmp = %s\n", tmp);
    free(tmp1);
    //free(tmp);
    
    return c;
}

char *div_(char *a, char *b, char **c1, int sys)
{
    int n, m, i, j, i_c;
    n = strlen(a);
    m = strlen(b);

    int dig_a[n+A], dig_b[m+A], dig_curr[n+A], dig = 0;
    
    *c1 = (char *)realloc(*c1, n+A);
    char *curr1 = (char *)malloc(m+A), *prev1 = (char *)malloc(m+A), *tmp1 = (char *)malloc(m+A), ch;
    char *c = *c1, *curr = curr1, *prev = prev1, *tmp = tmp1;

    for(i=0; i<n; i++) c[i] = '0';

    for(i=m-1; i<n; i++)
    {
        if(i == m-1)
        {
            ch = a[i+1];
            a[i+1] = '\0';
            str_cpy(curr, a);
        }
        else
        {
            ch = a[i+1];
            a[i+1] = '\0';
        }
        
        str_cpy(prev, curr);
        
        tmp = div_help(curr, b, &tmp1, sys, &dig);
        str_cpy(curr, tmp);
        
        c[i] = dig+'0';

        //printf("%d\n", dig);
        
        tmp = subtr(prev, curr, &tmp1, sys);
        str_cpy(curr, tmp);
        
        a[i+1] = ch;
        
        int len = strlen(curr);
        curr[len] = ch;
        curr[len+1] = '\0';
    }
    
    c[n] = '\0';
    
    num_to_let(c);

    while(c[0] == '0') c++;
    if(strlen(c) == 0) c--;

    free(curr1);
    free(prev1);
    free(tmp1);
    
    return c;
}

char *mod(char *a, char *b, char **c1, int sys)
{
    int n = strlen(a), m = strlen(b);
    
    *c1 = (char *)realloc(*c1, n+A);
    char *tmp1 = (char *)malloc(n+A);
    char *c = *c1, *tmp = tmp1;
    
    tmp = div_(a, b, &tmp1, sys);
    str_cpy(c, tmp);
    
    tmp = mult(c, b, &tmp1, sys);
    str_cpy(c, tmp);
    
    tmp = subtr(a, c, &tmp1, sys);
    str_cpy(c, tmp);
    
    free(tmp1);
    
    return c;
}

char *sys_conv(int sys1, int sys2, char **b1)
{
    int curr = sys2, i = 0, pom[B];

    //*b1 = (char *)malloc(B);
    *b1 = (char *)realloc(*b1, B);
    char *b = *b1;

    while( curr != 0 )
    {
        pom[i] = curr % sys1;
        curr /= sys1;
        i++;
    }
    
    int n = i;
    
    for(i=0; i<n; i++)
    {
        b[i] = pom[n-i-1]+'0';
    }
    b[n] = '\0';
    
    num_to_let(b);
    
    return b;
}

int dig_conv(char *str, int sys1, int sys2)
{
    int res = 0, n = strlen(str);
    
    let_to_num(str);
    
    for(int i = 0; i<n; i++) res += (str[i]-'0') * pow_( sys1, (n-i-1) );
    
    num_to_let(str);
    
    return res;
}

char *num_conv(char *a, char *b, char **c1, int sys, int sys2)
{
    int i = 0, n = strlen(a);
    int cy[n*4+A];
    
    *c1 = (char *)realloc(*c1, n*4+A);
    char *curr1 = (char *)malloc(n+A), *inv1 = (char *)malloc(n*4+A);
    char *c = *c1, *curr = curr1, *inv = inv1;
    
    str_cpy(curr, a);

    while( curr[0] != '0' )
    {
        c = mod(curr, b, c1, sys);
        
        inv[i] =  dig_conv(c, sys, sys2)+'0';
        
        c = div_(curr, b, c1, sys);
        str_cpy(curr, c);
        
        i++;
    }
    
    int m = i;
    //printf("%d\n%d\n%d\n", n, m, n*4+A);
    //for(i=0; i<m; i++) c[i] = inv[m-i-1];
    *c1 = (char *)realloc(*c1, n*4+A);
    c = *c1; //uzywanie jednej zmiennej do wielu rzeczy tak sie konczy :(
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!IMPORTANTTTTTT
    //DLUGO NIE USUWAC AKURAT TYCH KOMENTARZY
    for(i=0; i<m; i++) c[i] = inv[m-i-1];
    c[m] = '\0';
    
    num_to_let(c);

    free(curr1);
    free(inv1);

    if( str_cmp(a, "0") == 0 ) return "0";
    return c;
}

char *basic_pow(char *b, char *e, char **c1, int sys)
{
    int n, m;
    n = strlen(b);
    m = strlen(e);
    
    *c1 = (char *)realloc(*c1, BIG_BUFF);
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
    }

    free(tmp1);
    free(curr_e1);

    return c;
}
