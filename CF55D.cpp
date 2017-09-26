#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#include <ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
typedef pair<ll,P2> P3;
P3 p3(ll a,ll b,ll c){
    return P3(a,P2(b,c));
}
ll len,bits[20],dp[20][2527][57][2],mod = 2520,h[3007];//2520
ll dfs(ll b,bool pf,ll m,ll l,bool pp){
    //dp[b][m][h[l]][pp]
    if(b == -1)return m%l==0&&pp;
    if(!pf && dp[b][m][h[l]][pp]!=-1)return dp[b][m][h[l]][pp];
    ll res = 0,bc = pf?bits[b]:9;
    for(ll i=0;i<=bc;i++){
        res += dfs(b-1,i==bc&&pf,(m*10+i)%mod,i?(i*l/__gcd(i,l)):l,pp||i);
    }
    if(!pf)dp[b][m][h[l]][pp] = res;
    return res;
}
ll solve(ll a){
    len = 0;
    while(a){
        bits[len++] = a%10;
        a /= 10;
    }
    return dfs(len-1,1,0,1,0);
}
int main(){
    //freopen("in.txt","r",stdin);
    ll con = 0;
    for(ll i=1;i<=2520;i++){
        if(mod%i==0){
            //cout<<i<<" "<<con++<<endl;
            h[i] = con++;
        }
    }
    ll T,lo,hi; cin>>T;
    memset(dp,-1,sizeof dp);
    while(T--){
        cin>>lo>>hi;
        cout<<solve(hi)-solve(lo-1)<<endl;
    }
    return 0;
}
