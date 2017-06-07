#include <cstdio>
#include <cstring>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define BASE 100000000
ll N,M,line[15],in,dp[15][1<<15],s1,s2,sum;
int main(){
    while(scanf("%d%d",&N,&M)==2){
        for(ll i=0;i<N;i++){
            line[i] = 0;
            for(ll j=0;j<M;j++){
                scanf("%d",&in);
                line[i] = in|(line[i]<<1);
            }
        }
        memset(dp,0,sizeof dp);
        sum = 0;
        for(ll i=0;i<N;i++){
            s1 = line[i];
            for(ll j=s1;1;j=(j-1)&s1){
                if((j&(j<<1)) != 0)continue;
                if(i == 0)dp[i][j] ++;
                else{
                    s2 = line[i-1]&(~j);
                    for(ll k=s2;1;k=(k-1)&s2){
                        if((k&(k<<1)) != 0)continue;
                        dp[i][j] = (dp[i][j]+dp[i-1][k])%BASE;
                        if(k == 0)break;
                    }
                }
                if(i == N-1)sum = (sum+dp[i][j])%BASE;
                if(j == 0)break;
            }
        }
        printf("%d\n",sum);
    }
	return 0;
}
