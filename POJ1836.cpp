#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 1010
ll N,dp[2][MAXN];
double line[MAXN];
ll bin(double a,double *A,ll lo,ll hi){
    while(lo < hi){
        ll mi = (lo+hi)/2;
        if(A[mi] == a)return mi;
        if(A[mi] < a)lo = mi+1;
        else hi = mi;
    }return lo;
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    double lis[MAXN];
    while(cin>>N){
        for(ll i=0;i<N;i++)cin>>line[i];
        for(ll i=0,l=0;i<N;i++){
            ll r = bin(line[i],lis,0,l);
            lis[r] = line[i];
            if(r == l)l++;
            dp[0][i] = i+1-l;
        }
        for(ll i=N-1,l=0;i>=0;i--){
            ll r = bin(line[i],lis,0,l);
            lis[r] = line[i];
            if(r == l)l++;
            dp[1][i] = N-i-l;
        }
        ll min_mem = N;
        for(ll i=0;i<N-1;i++){
            if(min_mem>dp[0][i]+dp[1][i+1])
                min_mem = dp[0][i]+dp[1][i+1];
        }
        cout<<min_mem<<endl;
    }
    return 0;
}