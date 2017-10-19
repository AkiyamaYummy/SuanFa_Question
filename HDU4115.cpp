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
    ll *head = G.head,s,t;edge *E = G.E;
    bool haskip = 0;
    sta.push(r);
    insta[r] = 1,dfn[r] = low[r] = ++vid;
    for(ll i=head[r];i!=-1;i=E[i].next){
        s = E[i].to;
        if(s == f && mode && !haskip){
            haskip = 1; continue;
        }
        if(!dfn[s]){
            tarjan(s,r,res,G,mode);
            if(low[s] < low[r])low[r] = low[s];
        }else if(dfn[s] < low[r]&&insta[s])
            low[r] = dfn[s];
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
    memset(low,0,sizeof(ll)*(nodecon+1));
    memset(dfn,0,sizeof(ll)*(nodecon+1));
    vid = 0;
    for(ll i=0;i<nodecon;i++){
        if(!dfn[i]){
            memset(insta,0,sizeof(ll)*(nodecon+1));
            tarjan(i,-1,res,G,mode);
        }
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    ll T,n,m,a,b,c,B[10007],it[10007][2],t=0; scanf("%d",&T);
    graph G(20007,80007);
    start:
    while(T --){
        G.init();
        scanf("%d%d",&n,&m);
        for(ll i=0;i<n;i++){
            scanf("%d",&B[i]); B[i] --;
            it[i][0] = B[i];
            it[i][1] = (B[i]+1)%3;
        }
        while(m --){
            scanf("%d%d%d",&a,&b,&c);
            a --; b --;
            for(ll i=0;i<2;i++)for(ll j=0;j<2;j++)
                if((it[a][i]==it[b][j]&&c)||(it[a][i]!=it[b][j]&&!c)){
                    G.add(a*2+i,b*2+1-j),G.add(b*2+j,a*2+1-i);
                }
        }
        vector<vector<ll>> res;
        mainTarjan(n*2,res,G,0);
        for(ll i=0;i<n;i++){
            if(block[i*2] == block[i*2+1]){
                printf("Case #%d: no\n",++t);
                goto start;
            }
        }
        printf("Case #%d: yes\n",++t);
    }
    return 0;
}
