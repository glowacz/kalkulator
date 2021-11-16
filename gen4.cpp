#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3000;
const int B = 10;
const int E = 4;
const int O = 10000;

string op = "+*/%^";
int sys = 10, nr_op, l_op, n, m;
string a1, b1, cy="0123456789ABCDEF";

random_device rd;
mt19937 eng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    ofstream out;
    out.open("in_2.txt");
    srand(time(0));
    l_op = rand()%O+1;
    l_op = O;
    l_op = 1;
    
    uniform_int_distribution<> wyb_op(2, 2);
    uniform_int_distribution<> wyb_sys(2, 16);
    uniform_int_distribution<> dl(N-B, N);
    uniform_int_distribution<> distr_b(1, B);
    uniform_int_distribution<> distr_e(1, E);
    uniform_int_distribution<> wyb_cy(0, 15);

    for(int i=0; i<l_op; i++){
    //uniform_int_distribution<long long> distr_small(1, N/100000);
    //uniform_int_distribution<long long> distr_small(1, M);

    sys = wyb_sys(eng);

    nr_op = wyb_op(eng);

    n = dl(eng);
    m = dl(eng);

    //n = N, m = N; //zawsze dosyc duze

    //n = distr_e(eng); m = distr_e(eng); //malutkie liczby
    //n = distr_b(eng); m = distr_b(eng); //male liczby

    n = 5;
    m = 3;

    if(op[nr_op] == '^'){
        n = distr_b(eng);
        m = distr_e(eng);
    }

    a1 += cy[wyb_cy(eng)%(sys-1)+1];
    b1 += cy[wyb_cy(eng)%(sys-1)+1];
    for(int i=1; i<n; i++) a1 += cy[wyb_cy(eng)%sys];
    for(int i=1; i<m; i++) b1 += cy[wyb_cy(eng)%sys];

    
    out <<op[nr_op]<<" "<<sys<<" \n\n"<<a1<<" \n\n"<<b1<<" \n\n\n";
    a1 = "";
    b1 = "";
    }
    out.close();
    return 0;
}