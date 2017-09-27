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
double dp[1007][1007][3];//0 pre  1 dra  2 esc
bool has[1007][1007][3];
#define NW DP(w-1,b,(t+1)%3)
#define NB DP(w,b-1,(t+1)%3)
double DP(ll w,ll b,ll t){
    double res;
    if(w == 0)res = 0;
    else if(b == 0)res = t?(t==2&&w>1?1:0):1;
    else if(has[w][b][t])res = dp[w][b][t];
    else{
        double getw = w/((double)w+b),getb = b/((double)w+b);
        if(t == 0)res = getw+getb*NB;
        else if(t == 1)res = getb*NB;
        else res = getw*NW+getb*NB;
        has[w][b][t] = 1;
        dp[w][b][t] = res;
    }
    return res;
}
int main(){
    //freopen("in.txt","r",stdin);
    ll w,b;
    memset(has,0,sizeof has);
    while(scanf("%d%d",&w,&b) == 2){
        printf("%.9f\n",DP(w,b,0));
    }
    return 0;
}
