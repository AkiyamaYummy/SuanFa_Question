#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 20000
ll dp[MAXN][22],pos[22],wei[22],P,W,M;
ll jdz(ll n){return n*(n>0?1:-1);}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll mp,mw,w;
    while(cin>>P>>W){
        mp = mw = 0;
        memset(dp,0,sizeof dp);
        for(ll i=1;i<=P;i++){
            cin>>pos[i];
            if(jdz(pos[i])>mp)mp=jdz(pos[i]);
        }
        for(ll i=1;i<=W;i++){
            cin>>wei[i];
            mw += wei[i];
        }
        M = mp*mw;
        dp[M][0] = 1;
        for(ll i=1;i<=W;i++)
            for(ll j=2*M;j>=0;j--)
                for(ll k=1;k<=P;k++){
                    w = pos[k]*wei[i];
                    if(j-w<=2*M && j-w>=0)
                        dp[j][i] += dp[j-w][i-1];
                }
        cout<<dp[M][W]<<endl;
    }
    return 0;
}
