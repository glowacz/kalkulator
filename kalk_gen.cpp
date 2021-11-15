#include <bits/stdc++.h>
#define ll long long
using namespace std;

//const long long N = 1000000000000000000; 10^\18
//const long long N = 1000000000; //10^9
const long long N = 2000000000;
const long long B = 100;
const long long E = 9;
const long long O = 10000;
//const long long N = 1000;

string op = "+/%*^";
int sys = 10, nr_op, l_op;
long long a, b;
string a1, b1;

random_device rd;
mt19937 eng(chrono::steady_clock::now().time_since_epoch().count());

string let_to_num(string str){
    for(int i=0; i<str.size(); i++){
        if(str[i]-'0' >= 10) str[i] -= 7;
    }
    return str;
}

string num_to_let(string str){
    for(int i=0; i<str.size(); i++){
        if(str[i]-'0' >= 10) str[i] += 7;
    }
    return str;
}

ll sys_to_dec(string a, ll sys){
    if(a == "0") return 0;
    ll curr = 0, pow = 1;
    for(int i = a.size()-1; i>=0; i--){
        //cout <<i<<"\n";
        curr += (a[i]-'0')*pow;
        pow *= sys;
    }
    return curr;
}

string dec_to_sys(ll a, ll sys){
    if(a == 0) return "0";
    string str;
    ll ch;
    while( a != 0 ){
        str += (a % sys)+'0';
        a /= sys;
    }
    str = num_to_let(str);
    reverse(str.begin(), str.end());
    return str;
}

int main(){
    srand(time(0));
    l_op = rand()%O+1;
    l_op = O;
    l_op = 2;
    uniform_int_distribution<> wyb_op(0, 0);
    uniform_int_distribution<> wyb_sys(2, 16);
    uniform_int_distribution<long long> distr(1, N);
    uniform_int_distribution<long long> distr_b(0, B);
    uniform_int_distribution<long long> distr_e(0, E);
    for(int i=0; i<l_op; i++){
    //uniform_int_distribution<long long> distr_small(1, N/100000);
    //uniform_int_distribution<long long> distr_small(1, M);

    sys = wyb_sys(eng);
    a = distr(eng);
    //a = 2;
    //b = distr_small(eng);
    b = distr(eng);

    nr_op = wyb_op(eng);

    //a = distr_e(eng); b = distr_e(eng); //malutkie liczby
    //a = distr_b(eng); b = distr_b(eng); //male liczby

    if(op[nr_op] == '^'){
        a = distr_b(eng);
        b = distr_e(eng);
    }

    if(nr_op%2 == 1 && a < b) swap(a, b);
    //cout <<"a = "<<a<<",   b = "<<b<<"\n";
    //if(nr_op == 3) a *= b;

    a1 = dec_to_sys(a, sys);
    b1 = dec_to_sys(b, sys);
    
    cout <<op[nr_op]<<" "<<sys<<" \n\n"<<a1<<" \n\n"<<b1<<" \n\n\n";
    }
    return 0;
}