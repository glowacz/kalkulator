#include <bits/stdc++.h>
#define ll long long
using namespace std;

char op;
int sys;
long long a, b;
string ln;

ll qck_pow(ll b, ll e){
    if(e == 0) return 1;
    else{
        if(e%2 == 0) return qck_pow(b, e/2)*qck_pow(b, e/2);
        else return qck_pow(b, e-1)*b;
    }
}

/*string sys_to_dec(string a, string b, int sys){
    ll curr;
    for(int i = a.size()-1; i>=0; i++)
}*/

int main(){
    ifstream in;
    in.open("przyklad.in");
    in >>op;
    in >>sys;
    getline(in, ln);
    in >>a;
    getline(in, ln);
    in >>b;
    getline(in, ln);
    if(op == '+') cout <<a+b;
    else if(op == '-') cout <<a-b;
    else if(op == '*') cout <<a*b;
    else if(op == '/') cout <<a/b;
    else if(op == '^') cout <<qck_pow(a, b);

    cout <<"\n";
    
    return 0;
}