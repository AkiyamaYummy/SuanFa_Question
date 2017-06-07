#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 10010
vector<ll> pic[MAXN];
ll de[MAXN],N,mon[MAXN];
bool has_out[MAXN];
int main(){
	freopen("_in.txt","r",stdin);
    freopen("_out.txt","w",stdout);
    
    ll M,a,b,rk;
    start:
    while(cin>>N>>M){
        memset(has_out,0,sizeof(bool)*(N+1));
        rk = 0;
        memset(de,0,sizeof(ll)*(N+1));
        memset(mon,0,sizeof(ll)*(N+1));
        for(ll i=0;i<=N;i++)pic[i].clear();
        while(M--){
            cin>>b>>a;
            pic[a].push_back(b);
            de[b] ++;
        }
        queue<ll> que;
        for(ll i=1;i<=N;i++){
            if(de[i] == 0)que.push(i);
        }
        while(!que.empty()){
            ll r = que.front(); que.pop();
            has_out[r] = 1; rk++;
            for(ll i=0;i<pic[r].size();i++){
                ll s = pic[r][i];
                if(mon[s] < mon[r]+1)
                    mon[s] = mon[r]+1;
                de[s]--;
                if(has_out[s] || de[s]<0){
                    cout<<"-1"<<endl;
                    goto start;
                }
                if(de[s] == 0){
                    que.push(s);
                }
            }
        }
        if(rk != N){
            cout<<"-1"<<endl;
            goto start;
        }
        ll sum = 888*N;
        for(ll i=1;i<=N;i++)sum+=mon[i];
        cout<<sum<<endl;
    }
	return 0;
}