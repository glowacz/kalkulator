#include <bits/stdc++.h>
using namespace std;

//const long long N = 1000000000000000000; 10^\18
//const long long N = 1000000000; //10^9
const long long N = 20;
const long long M = 14;
//const long long N = 1000;

char op[5] = {'+', '-', '*', '/', '^'};
int sys = 10, nr_op;
long long a, b;

random_device rd;
mt19937 eng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    srand(time(0));
    
    uniform_int_distribution<> wyb_op(4, 4);
    uniform_int_distribution<long long> distr(1, N);
    //uniform_int_distribution<long long> distr_small(1, N/100000);
    uniform_int_distribution<long long> distr_small(1, M);

    a = distr(eng);
    //a = 2;
    b = distr_small(eng);
    //b = distr(eng);

    nr_op = wyb_op(eng);

    if(nr_op%2 == 1 && a < b) swap(a, b);
    //cout <<"a = "<<a<<",   b = "<<b<<"\n";
    if(nr_op == 3) a *= b;

    cout <<op[nr_op]<<" "<<sys<<"\n"<<a<<"\n"<<b<<"\n";
    return 0;
}