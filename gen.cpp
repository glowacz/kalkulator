#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll N = 1000000000000000000; //10^\18
const ll N1 = 1000000000; //10^9
//const ll N = 2000000000;
//const ll N = 20000;
const ll M = 2000;
const ll B = 10;
const ll E = 18;
const ll O = 1000;
//const ll N = 1000;

string op = "+*-/%^k";
int sys = 10, nr_op, l_op;
ll a, b;
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
    //l_op = 10;
    uniform_int_distribution<> wyb_op(3, 3);
    uniform_int_distribution<> wyb_sys(2, 16);
    uniform_int_distribution<ll> distr(M, N);
    uniform_int_distribution<ll> distr_mult(N1/M, N1);
    uniform_int_distribution<ll> distr_small(1, M);
    uniform_int_distribution<ll> distr_b(0, B);
    uniform_int_distribution<ll> distr_e(0, E);
    uniform_int_distribution<ll> distr_tiny(1, 9);
    
    for(int i=0; i<l_op; i++){

    sys = wyb_sys(eng);
    a = distr(eng);
    b = distr(eng);
    //b = distr_small(eng);
    //a = 0;

    nr_op = wyb_op(eng);

    if(op[nr_op] == '*'){
        a = distr_mult(eng);
        b = distr_mult(eng);
    }

    if(op[nr_op] == '/') b = distr_mult(eng); //duzy wynik dzielenia, latwo wywala

    /*while( a % b == 0 ) { //nie zachodzi podzielność
        a = distr_small(eng); b = distr_small(eng);
    }*/
    
    //b = distr_small(eng)*10; a = distr_small(eng)*b; b = a/b;
    //b = distr_small(eng); a = distr_small(eng)*b; //zachodzi podzielność
    //a = distr_small(eng); b = distr_small(eng); //male liczby
    //b = distr_tiny(eng); //b 1-cyfrowe (wynik dzielenia wielocyfrowy)
    //b = distr_tiny(eng); b = a/b; //wynik dzielenia 1-cyfrowy
    //a = distr_tiny(eng); b = distr_tiny(eng); //liczby jednocyfrowe
    //a = distr_e(eng); b = distr_e(eng); //malutkie liczby
    //a = distr_b(eng); b = distr_b(eng); //b male liczby

    if(op[nr_op] == '^'){
        a = distr_b(eng);
        b = distr_e(eng);
    }

    if( nr_op == 2 && a < b ) swap(a, b);
    //if( nr_op >=2 && nr_op <= 4 && a < b ) swap(a, b);
    
    
    //cout <<"a = "<<a<<",   b = "<<b<<"\n";
    //if(nr_op == 3) a *= b;

    a1 = dec_to_sys(a, sys);
    b1 = dec_to_sys(b, sys);
    
    //cout <<op[nr_op]<<" "<<sys<<" \n\n"<<a1<<" \n\n"<<b1<<" \n\n\n";
    cout <<op[nr_op]<<" "<<sys<<"\n\n"<<a1<<"\n\n"<<b1<<"\n\n\n";
    }
    return 0;
}