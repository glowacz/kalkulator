#include <bits/stdc++.h>
#define ll long long
using namespace std;

char op;
ll sys, a, b, res;
string a1, b1, ln, bin;

ll qck_pow(ll b, ll e){
    if(e == 0) return 1;
    if(e%2 == 0) return qck_pow(b, e/2)*qck_pow(b, e/2);
    return qck_pow(b, e-1)*b;
}

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
    ll curr = 0, pow = 1;
    for(int i = a.size()-1; i>=0; i--){
        //cout <<i<<"\n";
        curr += (a[i]-'0')*pow;
        pow *= sys;
    }
    return curr;
}

string dec_to_sys(ll a, ll sys){
    string str;
    ll ch;
    while( a != 0 ){
        str += (a % sys)+'0';
        a /= sys;
    }
    str = num_to_let(str);
    reverse(str.begin(), str.end());
    if(str.size() == 0) return "0";
    return str;
}

int main(){
    ifstream in;
    in.open("in_tes.txt");
    while(1){
    in >>op;
    in >>sys;
    getline(in, bin);
    
    if( sys == 10 ){
        in >>a;
        getline(in, bin);
        in >>b;
        a1 = dec_to_sys(a, sys);
        b1 = dec_to_sys(b, sys);
    }
    else{
        in >>a1;
        getline(in, bin);
        in >>b1;
        
        a1 = let_to_num(a1);
        b1 = let_to_num(b1);

        a = sys_to_dec(a1, sys);
        b = sys_to_dec(b1, sys);

        a1 = num_to_let(a1);
        b1 = num_to_let(b1);

        //cout <<"sys="<<sys<<"\na="<<a<<"\nb="<<b<<"\n";
    }

    if(in.eof()) break;
    getline(in, bin);
    getline(in, bin);

    if( (op == '/' || op == '%') && b == 0 ) {
        cout <<op <<" " <<sys<<"\n\n"<<a1<<"\n\n"<<b1<<"\n\nDIVISION_BY_ZERO\n\n\n";
        continue;
    }
    
    if(op == '+') res = a+b;
    else if(op == '-') res = a-b;
    else if(op == '*') res = a*b;
    else if(op == '/') res = a/b;
    else if(op == '^') res = qck_pow(a, b);
    else if(op == '%') res = a%b;

    
    if(sys == 10) {
        cout <<op <<" " <<sys<<"\n\n"<<a<<"\n\n"<<b<<"\n\n";
        cout <<res;
    }
    //else cout <<"res="<<res<<"\n"<<dec_to_sys(res, sys);
    else {
        cout <<op <<" " <<sys<<"\n\n"<<a1<<"\n\n"<<b1<<"\n\n";
        if(res != 0) cout <<dec_to_sys(res, sys);
        else cout <<"0";
        //cout <<"res="<<res<<"\n"<<dec_to_sys(res, sys);
    }

    cout <<"\n\n\n";
    }

    return 0;
}