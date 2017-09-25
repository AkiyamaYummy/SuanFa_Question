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
ll len,bits[20],B,dp[20][1500];
ll dfs(ll b,bool pf,ll pb){
    if(pb < 0)return 0;
    if(b == -1)return pb==0;
    if(!pf && dp[b][pb]!=-1)return dp[b][pb];
    ll res = 0,bc = pf?bits[b]:9;
    for(ll i=0;i<=bc;i++)
        res += dfs(b-1,pf&&(i==bc),pb+(b-B)*i);
    if(!pf)dp[b][pb] = res;
    return res;
}
ll solve(ll a){
    len = 0;
    while(a){
        bits[len++] = a%10;
        a /= 10;
    }
    ll res = 0;
    for(ll i=0;i<len;i++){
        B = i;
        memset(dp,-1,sizeof dp);
        res += dfs(len-1,1,0);
    }
    return res-len+1;
}
int main(){
    //freopen("in.txt","r",stdin);
    ll lo,hi,T; cin>>T;
    while(T--){
        cin>>lo>>hi;
        cout<<solve(hi)-solve(lo-1)<<endl;
    }
    return 0;
}
