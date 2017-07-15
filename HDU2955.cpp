#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAXM 110
ll M,V[MAXM],sum; double N,C[MAXM],dp[10010];
double s(double a1,double a2){
    return 1-(1-a1)*(1-a2);
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll T; cin>>T;
    while(T--){
        cin>>N>>M; sum = 0;
        for(ll i=0;i<M;i++){
            cin>>V[i]>>C[i];
            sum += V[i];
        }
        dp[0] = 0;
        for(ll i=1;i<=sum;i++)dp[i] = 1;
        for(ll i=0;i<M;i++){
            for(ll j=sum;j>=0;j--){
                if(j-V[i] < 0)break;
                dp[j] = min(dp[j],s(dp[j-V[i]],C[i]));
            }
        }
        for(ll i=sum;i>=0;i--){
            if(dp[i] <= N){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
}
