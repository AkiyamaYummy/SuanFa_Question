#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll n,a,con[101],_max;
    while(cin>>n&&n){
        memset(con,0,sizeof con);
        _max = 0;
        while(n--){
            cin>>a;con[a]++;
            if(_max<a)_max = a;
        }
        for(ll i=1;i<=100;i++){
            while(con[i]--)
                cout<<i<<((i==_max&&con[i]==0)?'\n':' ');
        }
    }

    return 0;
}
