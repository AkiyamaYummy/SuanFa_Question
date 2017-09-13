#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <map>
#include <set>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll,ll> P2;
typedef pair<ll,P2> P3;
P3 p3(ll a,ll b,ll c){return P3(a,P2(b,c));}
#define MAXN 50007
#define MAXE 100007
struct edge{
    ll to,next,len;
    edge(ll a=0,ll b=0,ll c=0){
        to = a; next = b; len = c;
    }
}E[MAXE];
ll eid,head[MAXN];
void add(ll h,ll t,ll len){
    E[eid] = edge(t,head[h],len);
    head[h] = eid++;
}
#define INF 0x3f3f3f3f3f3f3f3f
void spfa(ll sta,ll *d){
    memset(d,0x3f,sizeof(ll)*(MAXN));
    d[sta] = 0;
    queue<ll> que; que.push(sta);
    bool in[MAXN]; memset(in,0,sizeof in);
    while(!que.empty()){
        ll f = que.front();que.pop();
        in[f] = 0;
        for(ll i=head[f];i!=-1;i=E[i].next){
            ll s = E[i].to;
            if(d[f]+E[i].len < d[s]){
                d[s] = d[f]+E[i].len;
                if(!in[s]){
                    in[s] = 1;
                    que.push(s);
                }
            }
        }
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    ll T,n,m,a,b,c,res,f; scanf("%I64d",&T);
    ll d[MAXN],v[MAXN];
    while(T--){
        memset(head,-1,sizeof head);
        eid = 0;
        scanf("%I64d%I64d",&n,&m);
        for(ll i=1;i<=n;i++)scanf("%I64d",&v[i]);
        while(m--){
            scanf("%I64d%I64d%I64d",&a,&b,&c);
            add(a,b,c);
            add(b,a,c);
        }
        spfa(1,d);
        res = 0;
        f = 1;
        for(ll i=1;i<=n;i++){
            if(d[i] == INF)f = 0;
            if(f)res += v[i]*d[i];
        }
        if(f)printf("%I64d\n",res);
        else printf("No Answer\n");
    }
	return 0;
}
