#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 1010
#define MAXE 10010
ll N,K,eid,head[MAXN],minw[MAXN],minx[MAXN];
struct edge{
    ll next,to,w,x;
}edges[MAXE];
typedef pair<ll,ll> P2;
typedef pair<P2,ll> P3;
void add(ll u,ll v,ll w,ll x){
    edges[eid].to = v;
    edges[eid].w = w;
    edges[eid].x = x;
    edges[eid].next = head[u];
    head[u] = eid;
    eid ++;
}
void init(){
    memset(head,-1,sizeof(ll)*(N+1));
    eid = 0;
    for(ll i=0;i<=N;i++)
        minw[i] = minx[i] = 1e10;
}
bool can_push(ll n,ll w,ll x){
    if(w<minw[n] || x<minx[n]){
        if(w < minw[n]){
            minw[n] = w; minx[n] = x;
        }
        return 1;
    }
    return 0;
}
ll dij(ll S,ll E){
    ll n,w,x,s,sw,sx; P3 p;
    priority_queue<P3,vector<P3>,greater<P3> > que;
    que.push(P3(P2(0,0),S));
    while(!que.empty()){
        p = que.top(); que.pop();
        n = p.second; w = p.first.first;
        x = p.first.second;
        if(n == E)return p.first.first;
        for(ll i=head[n];i!=-1;i=edges[i].next){
            s = edges[i].to;sx = x+edges[i].x;
            sw = w+edges[i].w;
            if(sx<=K && can_push(s,sw,sx)){
                que.push(P3(P2(sw,sx),s));
            }
        }
    }
    return -1;
}
int main(){
    ll M,u,v,w,x;
    while(cin>>K>>N>>M){
        init();
        while(M--){
            cin>>u>>v>>w>>x;
            add(u,v,w,x);
        }
        cout<<dij(1,N)<<endl;
    }
    return 0;
}