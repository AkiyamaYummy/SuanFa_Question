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
#define MAXN 1007
#define MAXE 2007
struct edge{
    ll to,next;
    edge(ll a=0,ll b=0){
        to = a; next = b;
    }
}E[MAXE];
ll eid,head[MAXN];
void add(ll h,ll t){
    E[eid] = edge(t,head[h]);
    head[h] = eid++;
}

ll vid,dfn[MAXN],low[MAXN],insta[MAXN],block[MAXN];
stack<ll> sta;
void tarjan(ll r,vector<vector<ll>> &res){
    sta.push(r);
    insta[r] = 1;
    dfn[r] = low[r] = ++vid;
    ll s,t;
    for(ll i=head[r];i!=-1;i=E[i].next){
        s = E[i].to;
        if(!dfn[s]){
            tarjan(s,res);
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
void mainTarjan(ll nodecon,vector<vector<ll>> &res){
    memset(low,0,sizeof low);
    memset(dfn,0,sizeof dfn);
    vid = 0;
    for(ll i=1;i<=nodecon;i++){
        if(!dfn[i]){
            memset(insta,0,sizeof insta);
            tarjan(i,res);
        }
    }
}
bool inb[MAXN];
ll ins[MAXE],outs[MAXE];
int main(){
    //freopen("in.txt","r",stdin);
    ll n,m,v[1007],a,b,con1,con2,Min;
    while(scanf("%d%d",&n,&m) == 2){
        for(ll i=1;i<=n;i++)scanf("%d",&v[i]);
        memset(head,-1,sizeof head);
        eid = 0;
        while(m--){
            scanf("%d%d",&a,&b);
            add(a,b);
            ins[eid-1] = b;
            outs[eid-1] = a;
        }
        vector<vector<ll>> res;
        mainTarjan(n,res);
        /*
        cout<<"\n";
        for(ll i=0;i<res.size();i++){
            for(ll j=0;j<res[i].size();j++)
                cout<<res[i][j]<<(j==res[i].size()-1?"\n":" ");
        }cout<<"\n";
        for(ll i=1;i<=n;i++)cout<<block[i]<<(i==n?"\n":" ");
        */
        memset(inb,0,sizeof inb);
        for(ll i=0;i<eid;i++){
            if(block[ins[i]] != block[outs[i]])
                inb[block[ins[i]]-1] = 1;
        }
        con1 = con2 = 0;
        for(ll i=0;i<res.size();i++){
            if(!inb[i]){
                con1 ++;
                Min = 1e9;
                for(ll j=0;j<res[i].size();j++){
                    Min = min(Min,v[res[i][j]]);
                }
                con2 += Min;
            }
        }
        printf("%d %d\n",con1,con2);
    }
    return 0;
}
