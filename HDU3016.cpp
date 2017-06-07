#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
#define MAXN 100010
ll N,t[MAXN*4],d[MAXN],L,R;
struct blo{
    ll h,v; P2 p,s;
    blo():h(0),v(0),p(0,0),s(0,0){}
    blo(ll a,ll b,ll c,ll d){
        h = a; p.first = b; p.second = c;
        v = d;
    }
}b[MAXN];
bool operator < (blo a,blo b){
    return a.h < b.h;
}
void cover(ll lo1,ll hi1,ll lo2,ll hi2,ll ini,ll v){
    if(t[ini] == v)return;
    if(lo1 == lo2 && hi1 == hi2){
        t[ini] = v;
        return;
    }
    if(t[ini] > 0){
        t[ini*2] = t[ini*2+1] = t[ini];
        t[ini] = -1;
    }
    ll mi = (lo2+hi2)/2;
    if(lo1 <= mi && hi1 >= mi+1){
        cover(lo1,mi,lo2,mi,ini*2,v);
        cover(mi+1,hi1,mi+1,hi2,ini*2+1,v);
    }else if(hi1 <= mi){
        cover(lo1,hi1,lo2,mi,ini*2,v);
    }else{
        cover(lo1,hi1,mi+1,hi2,ini*2+1,v);
    }
}
ll f(ll r){
    ll lo = L,hi = R,mi,ini = 1;
    while(lo < hi){
        if(t[ini] > 0)return t[ini];
        mi = (lo+hi)/2;
        if(r <= mi){hi = mi;ini *= 2;}
        else{lo = mi+1;ini = ini*2+1;}
    }
    return t[ini];
}
ll dp(ll r){
    if(d[r] != -1)return d[r];
    ll v = b[r].v,s1 = b[r].s.first,s2 = b[r].s.second;
    if(s1 == s2)return d[r] = v+dp(s1);
    else return d[r] = v+max(dp(s1),dp(s2));
}
int main(){
    ll res,h,l,r,v;
    while(scanf("%d",&N)==1){
        L = MAXN; R = 0;
        for(ll i=1;i<=N;i++){
            scanf("%d%d%d%d",&h,&l,&r,&v);
            if(L > l)L = l;
            if(R < r)R = r;
            b[i] = blo(h,l,r,v);
        }
        b[0] = blo(0,L,R,0);
        sort(b,b+N+1);
        memset(t,0,sizeof t);
        for(ll i=1;i<=N;i++){
            b[i].s.first = f(b[i].p.first);
            b[i].s.second = f(b[i].p.second);
            cover(b[i].p.first,b[i].p.second,L,R,1,i);
        }
        memset(d,-1,sizeof d); d[0] = 100;
        res = dp(N);
        printf("%d\n",(res<0?-1:res));
    }
	return 0;
}
