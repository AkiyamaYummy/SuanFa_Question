#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXN 110
#define MAXD 200010
#define BASE 100005
int N,F[MAXN],S[MAXN],dp[MAXD],maxm,minm,res;
void qwe(int i,int j){
    if(j-F[i]>=minm&&j-F[i]<=maxm){
        j += BASE;
        if(dp[j]<dp[j-F[i]]+S[i])
            dp[j] = dp[j-F[i]]+S[i];
        j -= BASE;
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d",&N) == 1){
        minm = 0; maxm = 0;
        for(int i=1;i<=N;i++){
            scanf("%d%d",&F[i],&S[i]);
            if(F[i] > 0)maxm += F[i];
            else minm += F[i];
        }
        for(int i=minm;i<=maxm;i++)
            dp[i+BASE] = -(1<<30);
        dp[BASE] = 0;
        for(int i=1;i<=N;i++){
            if(F[i] > 0){
                for(int j=maxm;j>=minm;j--)
                    qwe(i,j);
            }else{
                for(int j=minm;j<=maxm;j++)
                    qwe(i,j);
            }
        }
        res = 0;
        for(int i=0;i<=maxm;i++)
            if(dp[i+BASE]>=0)
                if(i+dp[i+BASE] > res)
                    res = dp[i+BASE]+i;
        printf("%d\n",res);
    }
    return 0;
}
