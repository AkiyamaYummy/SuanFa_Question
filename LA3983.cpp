#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
ll C,d[MAXN],d2o[MAXN],td[MAXN],w[MAXN],que[MAXN];
ll p(ll x1,ll y1,ll x2,ll y2){
    return abs(x1-x2)+abs(y1-y2);
}
ll f(ll n){
    return d[n]-td[n+1]+d2o[n+1];
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll T,t,x,y,z,x_o,y_o,lo,hi;cin>>T;
    d[0] = d2o[0] = td[0] = w[0] = 0;
    while(T--){
        cin>>C;cin>>t;
        x_o = y_o = 0;
        lo = hi =0;
        for(ll i=1;i<=t;i++){
            cin>>x>>y>>z;
            w[i] = w[i-1]+z;
            d2o[i] = p(0,0,x,y);
            td[i] = td[i-1]+p(x_o,y_o,x,y);
            x_o = x; y_o = y;
        }
        lo = hi = 1;que[1] = 0;
        for(ll i=1;i<=t;i++){
            while(lo<=hi && w[i]-w[que[lo]]>C)lo++;
            d[i] = f(que[lo])+td[i]+d2o[i];
            while(lo<=hi && f(i)<=f(que[hi]))hi--;
            que[++hi] = i;
        }
        cout<<d[t]<<endl;
        if(T)cout<<'\n';
    }
    return 0;
}
