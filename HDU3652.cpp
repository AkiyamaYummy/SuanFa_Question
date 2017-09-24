#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
typedef pair<P2,ll> P3;
ll bits[10],dp[10][104],len,base[10];
ll dfs(ll b,bool pf,bool p1,bool p13,ll pm){
    ll m = pm*8+pf*4+p1*2+p13;
    if(b == -1){
        return (p13&&!pm)?1:0;
    }else if(dp[b][m] != -1){
        return dp[b][m];
    }else{
        ll res = 0,bitcon = pf?bits[b]:9;
        ll A,E; bool B,C,D;
        for(ll i=0;i<=bitcon;i++){
            A = b-1;
            B = pf&&(i==bitcon);
            C = (i==1);
            D = p13||(p1&&i==3);
            E = (pm+base[b]*i)%13;
            res += dfs(A,B,C,D,E);
        }
        return dp[b][m] = res;
    }
}
ll solve(ll a){
    len = 0;
    while(a){
        bits[len++] = a%10;
        a /= 10;
    }
    memset(dp,-1,sizeof dp);
    return dfs(len-1,1,0,0,0);
}
int main(){
    //freopen("in.txt","r",stdin);
    ll n,b = 1;
    for(ll i=0;i<10;i++){
        base[i] = b;
        b *= 10;
    }
    while(scanf("%d",&n) == 1){
        printf("%d\n",solve(n));
    }
	return 0;
}
