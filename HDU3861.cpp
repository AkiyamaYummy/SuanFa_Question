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

bool binMatch(ll x,ll *os,bool *used,const graph &G){
    ll *head = G.head; edge *E = G.E;
    for(ll i=head[x];i!=-1;i=E[i].next){
        ll s = E[i].to;
        if(!used[s]){
            used[s]=1;
            if(os[s]==-1||binMatch(os[s],os,used,G)){
                os[s]=x;
                return 1;
            }
        }
    }
    return 0;
}
ll mainBinMatch(ll nodecon,ll *other_side,const graph &G){
    ll res = 0;
    static bool *used = new bool[G._maxn];
    memset(other_side,-1,sizeof(ll)*G._maxn);
    for(ll i=1;i<=nodecon;i++){
        memset(used,0,sizeof(bool)*G._maxn);
        if(binMatch(i,other_side,used,G))res ++;
    }
    return res;
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

ll inn[100007],outn[100007];
int main(){
    //freopen("in.txt","r",stdin);
    graph G(5007,100007),rG(10007,100007);
    ll T,n,m,a,b,os[10007]; cin>>T;
    while(T--){
        G.init(); rG.init();
        cin>>n>>m;
        while(m --){
            cin>>a>>b;
            G.add(a,b);
            inn[G.eid-1] = b;
            outn[G.eid-1] = a;
        }
        vector<vector<ll>> res;
        mainTarjan(n,res,G);
        for(ll i=0;i<G.eid;i++){
            a = outn[i]; b = inn[i];
            if(block[a] != block[b]){
                rG.add(block[a],block[b]+res.size());
                rG.add(block[b]+res.size(),block[a]);
            }
        }
        cout<<(res.size()-mainBinMatch(res.size()*2,os,rG)/2)<<endl;
    }
    return 0;
}
