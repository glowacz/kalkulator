#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3000;
const int N1 = 30;
const int N2 = 300;
const int B = 15;
const int E = 3;
const int O = 100;

string op = "+*/%^k";
int sys = 10, nr_op, l_op, n, m;
string a1, b1, cy = "0123456789ABCDEF";

random_device rd;
mt19937 eng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    srand(time(0));
    l_op = rand()%O+1;
    l_op = O;
    l_op = 5;
    
    uniform_int_distribution<> wyb_op(0, 4);
    uniform_int_distribution<> wyb_sys(2, 16);
    uniform_int_distribution<> dl(N-B, N);
    uniform_int_distribution<> dl1(N1-B, N1);
    uniform_int_distribution<> dl2(N1, N2);
    uniform_int_distribution<> distr_b(1, B);
    uniform_int_distribution<> distr_e(1, E);
    uniform_int_distribution<> wyb_cy(0, 15);

    for(int i=0; i<l_op; i++){
        a1 = "";
        b1 = "";

        sys = wyb_sys(eng);

        nr_op = wyb_op(eng);

        n = dl(eng);
        m = dl(eng);

        //n = dl1(eng); m = dl1(eng); //dl 20-30
        //n = dl2(eng); m = dl2(eng); //dl 280-300

        //n = N-N2, m = N; //zawsze duze

        //n = distr_e(eng); m = distr_e(eng); //malutkie liczby
        //n = distr_b(eng); m = distr_b(eng); //male liczby

        if(op[nr_op] == '^'){
            n = distr_b(eng);
            m = distr_e(eng);
        }

        if(op[nr_op] == 'k'){
            a1 += cy[wyb_cy(eng)%(sys-1)+1];
            for(int i=1; i<n; i++) a1 += cy[wyb_cy(eng)%sys];
            cout <<sys<<" "<<wyb_sys(eng)<<"\n\n"<<a1<<"\n\n\n";
            continue;
        }

        a1 += cy[wyb_cy(eng)%(sys-1)+1];
        b1 += cy[wyb_cy(eng)%(sys-1)+1];
        for(int i=1; i<n; i++) a1 += cy[wyb_cy(eng)%sys];
        for(int i=1; i<m; i++) b1 += cy[wyb_cy(eng)%sys];

        //cout <<op[nr_op]<<" "<<sys<<" \n\n"<<a1<<" \n\n"<<b1<<" \n\n\n";
        cout <<op[nr_op]<<" "<<sys<<"\n\n"<<a1<<"\n\n"<<b1<<"\n\n\n";
    }
    return 0;
}