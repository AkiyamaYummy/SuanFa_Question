#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll YSF(ll n,ll k){
    if(n==1)return 0;
    return (YSF(n-1,k)+k-1)%(n-1)+1;
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,k,m;
    while(cin>>n>>k>>m&&(n||k||m)){
        cout<<((YSF(n,k)+m-1)%n+1)<<endl;
    }
    return 0;
}
