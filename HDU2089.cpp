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
ll bits[10],len,dp[10][4];
ll dfs(ll b,bool p6,bool pm){
    //for(ll i=0;i<len-1-b;i++)cout<<" ";
    //cout<<b<<" "<<p6<<" "<<pm<<endl;
    ll ans = 0;
    if(b == -1)ans = 1;
    else if(dp[b][p6*2+pm] != -1)ans = dp[b][p6*2+pm];
    else{
        ll bitcon = pm?bits[b]:9;
        for(ll i=0;i<=bitcon;i++){
            if(!(p6&&i==2)&&i!=4)
                ans += dfs(b-1,i==6,(i==bitcon)&&pm);
        }
        dp[b][p6*2+pm] = ans;
    }
    //for(ll i=0;i<len-1-b;i++)cout<<" ";
    //cout<<ans<<endl;
    return ans;
}
ll solve(ll a){
    len = 0;
    memset(dp,-1,sizeof dp);
    while(a){
        bits[len++] = a%10;
        a /= 10;
    }
    return dfs(len-1,0,1);
}
int main(){
    //freopen("in.txt","r",stdin);
    ll n,m;
    while(scanf("%d%d",&n,&m)==2 && (n||m)){
        printf("%d\n",solve(m)-solve(n-1));
    }
    return 0;
}
