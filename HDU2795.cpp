#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
#define MAXN 200000
#define MAXNO 524288
ll h,w,t[MAXNO],n,a;
ll change(ll v){
    ll lo = 1,hi = min(h,n),ini = 1,l,r,mi;
    if(w-t[ini] < v)return -1;
    while(lo != hi){
        l = ini*2; r = ini*2+1;
        mi = (lo+hi)/2;
        if(w-t[l] >= v){
            ini = l; hi = mi;
        }else{
            ini = r; lo = mi+1;
        }
    }
    t[ini] += v;
    do{
        ini /= 2;
        t[ini] = min(t[ini*2],t[ini*2+1]);
    }while(ini);
    return lo;
}
int main(){
    while(scanf("%d%d%d",&h,&w,&n)==3){
        memset(t,0,sizeof t);
        for(ll i=0;i<n;i++){
            scanf("%d",&a);
            printf("%d\n",change(a));
        }
    }
	return 0;
}
