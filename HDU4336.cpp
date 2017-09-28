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
#define MAXS 1048587
ll n,sta;
bool has[MAXS];
double dp[MAXS],bl[MAXS];
double DP(const ll &s){
    double res = 1;
    if(s == 0)res = 0;
    else if(has[s])res = dp[s];
    else{
        ll gl = s,lb;
        double dbl = 0;
        while(gl){
            lb = gl&(-gl);
            gl = gl&(~lb);
            res += bl[lb]*DP(s&(~lb));
            dbl += bl[lb];
            if(bl[lb] == 0)return 0;
        }
        res /= dbl;
        has[s] = 1;
        dp[s] = res;
    }
    return res;
}
int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n) == 1){
        for(ll i=0;i<n;i++)scanf("%lf",&bl[1<<i]);
        sta = (1<<n);
        memset(has,0,sizeof has);
        printf("%.5lf\n",DP(sta-1));
    }
    return 0;
}
