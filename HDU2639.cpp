#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
#define MAXN 110
#define MAXV 1010
int N,V,K,dp[MAXV][35],v[MAXN],c[MAXN],res[35];
void get(int *r,int *b1,int *b2){
    int m[2*K],c1=0,c2=0,c3=0;
    while(c3 < 2*K){
        if(c1 == K)m[c3++] = b2[c2++];
        else if(c2 == K)m[c3++] = b1[c1++];
        else if(b1[c1] > b2[c2])m[c3++] = b1[c1++];
        else m[c3++] = b2[c2++];
    }
    c1 = 0;memset(r,0,sizeof(int)*K);
    for(int i=0;i<2*K;i++){
        if(i==0||m[i]!=m[i-1])r[c1++] = m[i];
        if(c1 == K)break;
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,b1[35],b2[35]; scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof dp);
        scanf("%d%d%d",&N,&V,&K);
        for(int i=0;i<N;i++)scanf("%d",&v[i]);
        for(int i=0;i<N;i++)scanf("%d",&c[i]);
        for(int i=0;i<N;i++){
            for(ll j=V;j>=0;j--){
                if(j < c[i])break;
                for(ll k=0;k<K;k++){
                    b1[k] = dp[j-c[i]][k]+v[i];
                    b2[k] = dp[j][k];
                }
                get(dp[j],b1,b2);
            }
        }
        memset(res,0,sizeof res);
        for(ll j=V;j>=0;j--){
            for(ll k=0;k<K;k++){
                b1[k] = res[k];
                b2[k] = dp[j][k];
            }
            get(res,b1,b2);
        }
        printf("%d\n",res[K-1]);
    }
    return 0;
}
