#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXP 100010
#define MAXN 10010
ll C,N,dp[MAXP],w[MAXN];
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll n,D,k,con;
    while(cin>>C>>N){
        con = 0;
        for(ll i=1;i<=N;i++){
            cin>>n>>D;
            for(k=1;k*2-1<=n;k=k<<1){
                w[con++] = k*D;
            }k--;
            w[con++] = (n-k)*D;
        }
        memset(dp,0,sizeof(ll)*(C+1));
        for(ll j=0;j<con;j++){
            for(ll i=C;i>0;i--){
                if(w[j]>i)continue;
                if(dp[i]<dp[i-w[j]]+w[j])
                    dp[i] = dp[i-w[j]]+w[j];
            }
        }
        cout<<dp[C]<<endl;
    }
    return 0;
}
