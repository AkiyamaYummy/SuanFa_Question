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
ll vid,*dfn,*low,*insta,*block;
stack<ll> sta;
void tarjan(ll r,ll f,vector<vector<ll>> &res,const graph &G,bool mode){
    ll *head = G.head;edge *E = G.E;
    bool haskip = 0;
    sta.push(r);
    insta[r] = 1;
    dfn[r] = low[r] = ++vid;
    ll s,t;
    for(ll i=head[r];i!=-1;i=E[i].next){
        s = E[i].to;
        if(s == f && mode && !haskip){
            haskip = 1; continue;
        }
        if(!dfn[s]){
            tarjan(s,r,res,G,mode);
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
void mainTarjan(ll nodecon,vector<vector<ll>> &res,const graph &G,bool mode){
    // mode == 1 shuang lian tong mode == 0 qiang lian tong
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
            tarjan(i,-1,res,G,mode);
        }
    }
}
ll dfs(ll r,ll f,const graph &G,ll *V,ll &mindif,const ll &sum){
    ll _sum = V[r],*head = G.head,s;
    edge *E = G.E;
    for(ll i=head[r];i!=-1;i=E[i].next){
        s = E[i].to;
        if(s == f)continue;
        _sum += dfs(s,r,G,V,mindif,sum);
    }
    mindif = min(mindif,abs(_sum*2-sum));
    return _sum;
}
int main(){
    //freopen("in.txt","r",stdin);
    ll n,m,v[10007],a,b,V[10007],sum,mindif;
    set<P2>::iterator it;
    P2 es[40007];
    set<P2> edgeset;
    graph G(10007,40007),tG(10007,20007);
    while(cin>>n>>m){
        G.init(); sum = 0;
        tG.init(); edgeset.clear();

        for(ll i=1;i<=n;i++)
            cin>>v[i], sum += v[i];
        while(m --){
            cin>>a>>b;
            a ++; b ++;
            G.add(a,b); G.add(b,a);
            es[G.eid/2-1] = P2(a,b);
        }

        vector<vector<ll>> res;
        mainTarjan(n,res,G,1);
        /*
        for(ll i=0;i<res.size();i++){
            for(ll j=0;j<res[i].size();j++)
                cout<<res[i][j]<<(j==res[i].size()-1?"\n":" ");
        }
        */
        memset(V,0,sizeof V);
        for(ll i=1;i<=n;i++)V[block[i]] += v[i];

        for(ll i=0;i<G.eid/2;i++){
            a = block[es[i].first];
            b = block[es[i].second];
            if(a < b)swap(a,b);
            if(a != b)edgeset.insert(P2(a,b));
        }
        for(it=edgeset.begin();it!=edgeset.end();it++){
            tG.add(it->first,it->second);
            tG.add(it->second,it->first);
        }
        mindif = sum;
        dfs(1,-1,tG,V,mindif,sum);
        if(res.size() == 1)cout<<"impossible"<<endl;
        else cout<<mindif<<endl;
    }
    return 0;
}
