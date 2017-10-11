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
struct edge{
    ll to,next,len;
    edge(ll a=0,ll b=-1,ll c=0){
        to = a; next = b; len = c;
    }
};
struct graph{
    ll *head,eid,_maxn;
    edge *E;
    graph(ll maxn,ll maxe){
        head = new ll[maxn+1];
        E = new edge[maxe+1];
        _maxn = maxn;
        init();
    }
    ~graph(){
        delete[] head;
        delete[] E;
    }
    void init(){
        memset(head,-1,sizeof(ll)*_maxn);
        eid = 0;
    }
    void add(ll h,ll t,ll len=0){
        E[eid] = edge(t,head[h],len);
        head[h] = eid ++;
    }
};
#define INF 0x3f3f3f3f
void dij(ll sta,ll *d,const graph &G){
    ll *head = G.head; edge *E = G.E;
    memset(d,INF,sizeof(ll)*G._maxn);
    d[sta] = 0;
    priority_queue<P2,vector<P2>,greater<P2> >que;
    que.push(P2(0,sta));
    ll t,s,p,l;
    while(!que.empty()){
        t = que.top().second; p = que.top().first;
        que.pop();
        if(p > d[t])continue;
        for(ll i=head[t];i!=-1;i=E[i].next){
            s = E[i].to; l = E[i].len;
            if(p+l < d[s]){
                d[s] = p+l;
                que.push(P2(d[s],s));
            }
        }
    }
}
bool spfa(ll sta,ll *d,ll nodecon,const graph &G){
    memset(d,INF,sizeof(ll)*G._maxn);
    ll *head = G.head; edge *E = G.E;
    queue<ll> que; que.push(sta);
    static bool *in = new bool[G._maxn];
    memset(in,0,sizeof(bool)*G._maxn);
    static ll *times = new ll[G._maxn];
    memset(times,0,sizeof(ll)*G._maxn);
    d[sta] = 0; in[sta] = 1; times[sta] = 1;
    while(!que.empty()){
        ll f = que.front();que.pop();
        in[f] = 0;
        for(ll i=head[f];i!=-1;i=E[i].next){
            ll s = E[i].to;
            if(d[f]+E[i].len < d[s]){
                d[s] = d[f]+E[i].len;
                if(!in[s]){
                    in[s] = 1;
                    times[s] ++;
                    if(times[s] > nodecon)return 0;
                    que.push(s);
                }
            }
        }
    }
    return 1;
}
ll vid,*dfn,*low,*insta,*block;
stack<ll> sta;
void tarjan(ll r,vector<vector<ll>> &res,const graph &G){
    ll *head = G.head;edge *E = G.E;
    sta.push(r);
    insta[r] = 1;
    dfn[r] = low[r] = ++vid;
    ll s,t;
    for(ll i=head[r];i!=-1;i=E[i].next){
        s = E[i].to;
        if(!dfn[s]){
            tarjan(s,res,G);
            if(low[s] < low[r])low[r] = low[s];
        }else if(dfn[s] < low[r]&&insta[s]){
            low[r] = dfn[s];
        }
    }
    if(dfn[r] == low[r]){
        res.push_back(*(new vector<ll>()));
        do{
            t = sta.top(); sta.pop();
            insta[t] = 0;
            res.back().push_back(t);
            block[t] = res.size();
        }while(t != r);
    }
}
void mainTarjan(ll nodecon,vector<vector<ll>> &res,const graph &G){
    static bool first_time = 1;
    if(first_time){
        first_time = 0;
        dfn = new ll[G._maxn];
        low = new ll[G._maxn];
        insta = new ll[G._maxn];
        block = new ll[G._maxn];
    }
    memset(low,0,sizeof(ll)*G._maxn);
    memset(dfn,0,sizeof(ll)*G._maxn);
    vid = 0;
    for(ll i=1;i<=nodecon;i++){
        if(!dfn[i]){
            memset(insta,0,sizeof(ll)*G._maxn);
            tarjan(i,res,G);
        }
    }
}

ll inn[50007],outn[50007];
bool ind[20007],outd[20007];
int main(){
    //freopen("in.txt","r",stdin);
    ll n,m,a,b,inc,outc;
    graph G(20007,50007);
    while(cin>>n>>m){
        G.init();
        while(m--){
            cin>>a>>b;
            G.add(a,b);
            inn[G.eid-1] = b;
            outn[G.eid-1] = a;
        }
        vector<vector<ll>>res;
        mainTarjan(n,res,G);
        memset(ind,0,sizeof ind);
        memset(outd,0,sizeof outd);
        for(ll i=0;i<G.eid;i++){
            a = outn[i]; b = inn[i];
            if(block[a] != block[b]){
                ind[block[b]] = 1; outd[block[a]] = 1;
            }
        }
        inc = outc = 0;
        for(ll i=1;i<=res.size();i++){
            if(!ind[i])inc ++;
            if(!outd[i])outc ++;
        }
        cout<<(res.size()==1?0:max(inc,outc))<<endl;
    }
    return 0;
}
