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
struct RMQ{
    ll **st,maxl,maxh; double log2;
    RMQ(const ll &Maxl){
        log2 = log(2);
        maxl = Maxl;
        maxh = log(maxl)/log2;
        st = new ll*[maxh+1];
        for(ll i=0;i<=maxh;i++)
            st[i] = new ll[maxl+1-(1<<i)];
    }
    ~RMQ(){
        for(ll i=0;i<=maxh;i++)delete[] st[i];
        delete[] st;
    }
    void init(ll *arr,const ll &len){
        ll col = log(len)/log2;
        for(ll i=0;i<len;i++)st[0][i] = arr[i];
        for(ll i=1;i<=col;i++)for(ll j=0;j<=len-(1<<i);j++)
            st[i][j] = comp(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    ll find(ll lo,ll hi){ // zuo bi you kai
        ll col = log(hi-lo)/log2;
        return comp(st[col][lo],st[col][hi-(1<<col)]);
    }
    ll comp(ll a,ll b){
        return a<b?a:b;
    }
};
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
struct LCA_rmq{
    RMQ *r;
    ll *n_ft,*t_n,*n_p,*n_r,*r_n,dfst,nid,maxn;
    LCA_rmq(ll Maxn,ll maxl){
        maxn = Maxn,r = new RMQ(maxl);
        n_ft = new ll[maxn],n_p  = new ll[maxn];
        n_r  = new ll[maxn],r_n  = new ll[maxn];
        t_n  = new ll[maxl];
    }
    ~LCA_rmq(){
        delete[] n_ft;
        delete[] n_p;
        delete[] n_r;
        delete[] r_n;
        delete[] t_n;
        delete r;
    }
    void init(ll nodecon,const graph &T){
        dfst = nid = 0;
        memset(n_r,-1,sizeof(ll)*maxn);
        for(ll i=1;i<=nodecon;i++)if(n_r[i] == -1){
            dfs(i,-1,0,T);
            t_n[dfst ++] = -1;
        }
        r->init(t_n,dfst);
    }
    void dfs(ll r,ll f,ll p,const graph &T){
        ll *head = T.head; edge *E = T.E;
        n_r[r] = nid,r_n[nid++] = r;
        n_p[r] = p,n_ft[r] = dfst,t_n[dfst ++] = n_r[r];
        for(ll i=head[r];i!=-1;i=E[i].next){
            if(E[i].to == f)continue;
            dfs(E[i].to,r,p+E[i].len,T);
            t_n[dfst ++] = n_r[r];
        }
    }
    ll find_path(ll a,ll b){
        if(n_ft[a] > n_ft[b])swap(a,b);
        ll pa = n_p[a],pb = n_p[b];
        ll lca = r->find(n_ft[a],n_ft[b]+1);
        if(lca == -1)return -1;
        ll pc = n_p[r_n[lca]];
        return pa+pb-2*pc;
    }
};
int main(){
    //freopen("in.txt","r",stdin);
    ll n,m,q,a,b,c,res;
    graph G(10007,20007); LCA_rmq lr(10007,40007);
    while(scanf("%d%d%d",&n,&m,&q) == 3){
        G.init();
        while(m --){
            scanf("%d%d%d",&a,&b,&c);
            G.add(a,b,c);
            G.add(b,a,c);
        }
        lr.init(n,G);
        while(q --){
            scanf("%d%d",&a,&b);
            res = lr.find_path(a,b);
            if(res == -1)printf("Not connected\n");
            else printf("%d\n",res);
        }
    }
    return 0;
}
