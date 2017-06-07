#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 100000
#define MAXNO 262144
ll lazy[MAXNO],sum,N;
void change(ll lo1,ll hi1,ll c,ll lo2,ll hi2,ll ini){
    if(lazy[ini] == c)return;
    else if(lo1==lo2 && hi1==hi2){
        lazy[ini] = c;
        return;
    }else if(lazy[ini] >= 0){
        if(ini*2+1 < MAXNO)
            lazy[ini*2] = lazy[ini*2+1] = lazy[ini];
        lazy[ini] = -1;
    }
    ll mi = (lo2+hi2)/2;
    if(lo1 <= mi && hi1 >= mi+1){
        change(lo1,mi,c,lo2,mi,ini*2);
        change(mi+1,hi1,c,mi+1,hi2,ini*2+1);
    }else if(lo1 >= mi+1){
        change(lo1,hi1,c,mi+1,hi2,ini*2+1);
    }else{
        change(lo1,hi1,c,lo2,mi,ini*2);
    }
}
void get_sum(ll lo,ll hi,ll ini){
    if(lazy[ini] >= 0){
        sum += (hi-lo+1)*lazy[ini];
        return;
    }else{
        ll mi = (hi+lo)/2;
        get_sum(lo,mi,ini*2);
        get_sum(mi+1,hi,ini*2+1);
    }
}
int main(){
    ll T,Q,a,b,c,t = 0; scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(lazy,0,sizeof lazy);
        scanf("%d",&Q); sum = 0;
        while(Q--){
            scanf("%d%d%d",&a,&b,&c);c --;
            change(a,b,c,1,N,1);
        }
        get_sum(1,N,1);
        printf("Case %d: The total value of the hook is %d.\n",++t,sum+N);
    }
	return 0;
}
