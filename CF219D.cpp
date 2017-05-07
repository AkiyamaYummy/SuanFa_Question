#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 200010
struct E{
    ll next,host,neib;
    bool is_ok;
};
ll N,head[MAXN],con,anti[MAXN],min_a; E edge[2*MAXN];
void add(ll h,ll n){
    edge[con].host = h;
    edge[con].neib = n;
    edge[con].is_ok = 1;
    edge[con].next = head[h];
    head[h] = con;
    con++;
    swap(h,n);
    edge[con].host = h;
    edge[con].neib = n;
    edge[con].is_ok = 0;
    edge[con].next = head[h];
    head[h] = con;
    con++;
}
ll dfs_1(ll n,ll f){
    anti[n] = 0;
    for(ll i=head[n];i!=-1;i=edge[i].next){
        if(f != edge[i].neib){
            if(!edge[i].is_ok){
                anti[n]++;
                anti[n] += dfs_1(edge[i].neib,n);
            }else{
                anti[n] += dfs_1(edge[i].neib,n);
            }
        }
    }
    return anti[n];
}
void dfs_2(ll n,ll f,ll ance){
    ll a,an;
    for(ll i=head[n];i!=-1;i=edge[i].next){
        if(f != edge[i].neib){
            a = ance;
            an = anti[n]-anti[edge[i].neib]-(edge[i].is_ok?0:1);
            a += an;
            if(edge[i].is_ok)a ++;
            dfs_2(edge[i].neib,n,a);
        }
    }
    anti[n] += ance;
    if(anti[n] < min_a)min_a = anti[n];
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll host,neib;
    while(cin>>N){
        memset(head,-1,sizeof(ll)*(N+1));
        min_a = N+1; con = 0;
        for(ll i=0;i<N-1;i++){
            cin>>host>>neib;
            add(host,neib);
        }
        dfs_1(1,-1); dfs_2(1,-1,0);
        cout<<min_a<<endl;
        bool has_f = 0;
        for(ll i=1;i<=N;i++){
            if(anti[i] == min_a){
                cout<<(has_f?" ":"")<<i;
                has_f = 1;
            }
        }cout<<'\n';
    }

    return 0;
}
