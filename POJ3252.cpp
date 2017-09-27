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
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
typedef pair<ll,P2> P3;
P3 p3(ll a,ll b,ll c){
    return P3(a,P2(b,c));
}
ll dp[37][75],ini = 37,bits[37],len;
ll dfs(ll b,bool pf,ll z,bool pp){
    ll res;
    if(b == -1)res = (z>=0 && pp);
    else if(!pf && pp && dp[b][z+ini]!=-1)res = dp[b][z+ini];
    else{
        res = 0;ll bc = pf?bits[b]:1;
        for(ll i=0;i<=bc;i++)
            res += dfs(b-1,i==bc&&pf,(pp||i)?(z+(i?-1:1)):0,pp||i);
        if(!pf && pp)dp[b][z+ini] = res;
    }
    return res;
}
ll solve(ll a){
    len = 0;
    while(a){
        bits[len++] = a%2;
        a /= 2;
    }
    return dfs(len-1,1,0,0);
}
int main(){
    //freopen("in.txt","r",stdin);
    ll lo,hi;
    memset(dp,-1,sizeof dp);
    while(scanf("%d%d",&lo,&hi) == 2){
        printf("%d\n",solve(hi)-solve(lo-1));
    }
    return 0;
}
