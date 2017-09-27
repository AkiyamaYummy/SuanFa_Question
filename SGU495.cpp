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
int main(){
    //freopen("in.txt","r",stdin);
    ll N,M; scanf("%d%d",&N,&M);
    double dp = 0,bl = (N-1)/(double)N;
    for(ll i=0;i<M;i++)dp = 1+bl*dp;
    printf("%.9f\n",dp);
    return 0;
}
