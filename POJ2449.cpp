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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P2;
typedef pair<ll,P2> P3;
P3 p3(ll a,ll b,ll c){
    return P3(a,P2(b,c));
}
#define MAXN 1007
#define MAXE 100007
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
void dij(ll sta,ll *d,ll *head,edge *E){
    memset(d,INF,sizeof(ll)*MAXN);
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
ll n,k,s,e,eid1,eid2,head1[MAXN],head2[MAXN];
ll h[MAXN],otimes[MAXN];
edge E1[MAXE],E2[MAXE];
ll Astar(edge *E,ll *head){
    memset(otimes,0,sizeof otimes);
    priority_queue<P3,vector<P3>,greater<P3> >que;
    que.push(p3(h[s],0,s));
    ll t,p,son,len;
    while(!que.empty()){
        t = que.top().second.second;
        p = que.top().second.first;
        que.pop();
        otimes[t] ++;
        if(otimes[e] == k)return p;
        for(ll i=head[t];i!=-1;i=E[i].next){
            son = E[i].to; len = E[i].len;
            if(otimes[son] >= k)continue;
            que.push(p3(h[son]+len+p,len+p,son));
        }
    }
    return -1;
}
int main(){
    //freopen("in.txt","r",stdin);
    ll m,a,b,c;
    cin>>n>>m;
    eid1 = eid2 = 0;
    memset(head1,-1,sizeof head1);
    memset(head2,-1,sizeof head2);
    while(m--){
        cin>>a>>b>>c;
        add(a,b,c,E1,head1,eid1);
        add(b,a,c,E2,head2,eid2);
    }
    cin>>s>>e>>k; if(s==e)k++;
    dij(e,h,head2,E2);
    cout<<Astar(E1,head1)<<endl;
    return 0;
}
