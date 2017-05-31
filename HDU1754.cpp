#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 200010
#define MAXNO 524288
ll m[MAXNO],r[MAXN],N;
void change(ll _r,ll a){
    ll ini;
    if(r[_r] == -1){
        ll lo = 1,hi = N;ini = 1;
        while(lo < hi){
            ll mi = (lo+hi)/2;
            if(_r <= mi){
                hi = mi;
                ini = ini*2;
            }else{
                lo = mi+1;
                ini = ini*2+1;
            }
        }
        r[_r] = ini;
    }else{
        ini = r[_r];
    }
    m[ini] = a;
    while(ini){
        ini /= 2;
        m[ini] = max(m[ini*2],m[ini*2+1]);
    }
}
ll get_max(ll lo1,ll hi1,ll lo2,ll hi2,ll ini){
    if(lo1 == lo2&&hi1 == hi2){
        return m[ini];
    }
    ll mi = (lo2+hi2)/2;
    if(lo1 >= mi+1){
        return get_max(lo1,hi1,mi+1,hi2,ini*2+1);
    }else if(hi1 <= mi){
        return get_max(lo1,hi1,lo2,mi,ini*2);
    }else{
        return max(get_max(lo1,mi,lo2,mi,ini*2),
                   get_max(mi+1,hi1,mi+1,hi2,ini*2+1));
    }
}
int main(){
	//freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll M,a,b; char c;
    while(scanf("%d%d",&N,&M)==2){
        memset(m,0,sizeof m);
        memset(r,-1,sizeof r);
        for(ll i=1;i<=N;i++){
            scanf("%d",&a);
            change(i,a);
        }
        while(M--){
            do{
                c = getchar();
            }while(!(c>='A'&&c<='Z'));
            scanf("%d%d",&a,&b);
            if(c == 'Q')printf("%d\n",get_max(a,b,1,N,1));
            else change(a,b);
        }
    }
	return 0;
}
