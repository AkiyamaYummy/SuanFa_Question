#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 510
typedef pair<ll,ll> P2;
ll dp[5010],N,M,Max;
struct s{ll P,Q,V;}S[5010];
bool operator<(s a,s b){return a.P+b.Q<b.P+a.Q;}
int main(){
    while(scanf("%d%d",&N,&M)==2){
        memset(dp,0,sizeof dp);
        for(ll i=0;i<N;i++)
            scanf("%d%d%d",&S[i].P,&S[i].Q,&S[i].V);
        sort(S,S+N);
        for(ll i=0;i<N;i++){
            for(ll j=M;j>=0;j--){
                if(j < S[i].P)break;
                if(M-j+S[i].P < S[i].Q)continue;
                if(dp[j-S[i].P]+S[i].V > dp[j]){
                    dp[j] = dp[j-S[i].P]+S[i].V;
                }
            }
        }
        Max = 0;
        for(ll i=0;i<=M;i++)
            if(Max<dp[i])Max = dp[i];
        printf("%d\n",Max);
    }
	return 0;
}
