#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 11
#define MAXB 2048
typedef pair<ll,ll> P2;
ll N,C1,C2,base,W[MAXN],V[MAXB],dp[MAXB],mode[MAXB];
ll D(ll s){
    if(dp[s] >= 0)return dp[s];
    if(s == 0)return dp[s] = 0;
    if(V[s]<=C1 || V[s]<=C2){
        mode[s] = 1*(V[s]<=C1?1:0)+2*(V[s]<=C2?1:0);
        return dp[s] = 1;
    }
    ll Min = N,bs;
    for(ll ss=(s-1)&s;ss;ss=(ss-1)&s){
        bs = ss^s;
        if(D(bs)+D(ss) < Min)Min = dp[bs]+dp[ss];
        if((mode[bs]|mode[ss])==3&&mode[bs]&&mode[ss]){
            return dp[s] = 1;
        }
    }
    return dp[s] = Min;
}
int main(){
    ll T,t=0; scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&N,&C1,&C2);
        for(ll i=0;i<N;i++)scanf("%d",&W[i]);
        base = 1<<N; memset(V,0,sizeof(ll)*base);
        for(ll i=0;i<base;i++){
            for(ll j=0;j<N;j++){
                if(i&(1<<j))V[i] += W[j];
            }
        }
        memset(dp,-1,sizeof(ll)*base);
        memset(mode,0,sizeof(ll)*base);
        printf("Scenario #%d:\n%d\n\n",++t,D(base-1));
    }
	return 0;
}
