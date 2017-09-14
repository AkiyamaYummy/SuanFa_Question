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
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
typedef pair<ll,P2> P3;
P3 p3(ll a,ll b,ll c){
    return P3(a,P2(b,c));
}
#define MAXN 1007
#define MAXE 20007
#define INF 0x3f3f3f3f
struct edge{
    ll next,to,len;
    edge(ll a=0,ll b=0,ll c=0){
        next = c; to = a;
        len = b;
    }
};
void add(ll ho,ll to,ll len,edge *E,ll *head,ll &eid){
    E[eid] = edge(to,len,head[ho]);
    head[ho] = eid++;
}
ll n,s,e,eid,head[MAXN],d[4][MAXN];
edge E[MAXE];
priority_queue<P2,vector<P2>,greater<P2> >que;
ll dij(){
    while(!que.empty())que.pop();
    que.push(P2(0,s));
    memset(d[0],INF,sizeof d[0]);
    memset(d[1],INF,sizeof d[1]);
    d[0][s] = 0;
    memset(d[2],0,sizeof d[2]);
    memset(d[3],0,sizeof d[3]);
    d[2][s] = 1;
    ll t,p,len,son;
    while(!que.empty()){
        t = que.top().second; p = que.top().first;
        que.pop();
        if(p > d[1][t])continue;
        for(ll i=head[t];i!=-1;i=E[i].next){
            son = E[i].to; len = E[i].len;
            if(p+len < d[0][son]){
                d[1][son] = d[0][son];
                d[0][son] = p+len;
                d[3][son] = d[2][son];
                d[2][son] = 0;
                que.push(P2(p+len,son));
            }else if(p+len > d[0][son]&&p+len < d[1][son]){
                d[1][son] = p+len;
                d[3][son] = 0;
                que.push(P2(p+len,son));
            }
            if(p+len == d[0][son]&&p == d[0][t]){
                d[2][son] += d[2][t];
            }else if(p+len == d[1][son]&&p == d[0][t]){
                d[3][son] += d[2][t];
            }else if(p+len == d[0][son]&&p == d[1][t]){
                d[2][son] += d[3][t];
            }else if(p+len == d[1][son]&&p == d[1][t]){
                d[3][son] += d[3][t];
            }
        }
    }
    if(d[1][e]-1 == d[0][e]){
        return d[2][e]+d[3][e];
    }else return d[2][e];
}
int main(){
    //freopen("in.txt","r",stdin);
    ll m,a,b,c,T; cin>>T;
    while(T--){
        cin>>n>>m;
        eid = 0;
        memset(head,-1,sizeof head);
        while(m--){
            cin>>a>>b>>c;
            add(a,b,c,E,head,eid);
        }
        cin>>s>>e;
        cout<<dij()<<endl;
    }
    return 0;
}
