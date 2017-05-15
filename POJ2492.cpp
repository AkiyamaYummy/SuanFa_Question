#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 2010
ll N,fa[MAXN],rela[MAXN];
void init(){
    for(ll i=0;i<=N;i++)fa[i] = i;
    memset(rela,0,sizeof(ll)*(N+1));
}
ll _mult(ll a,ll b){
    return (a+b)%2;
}
ll _find(ll a){
    if(fa[a] == a)return a;
    ll r = _find(fa[a]);
    if(r != fa[a])rela[a] = _mult(rela[a],rela[fa[a]]);
    return fa[a] = r;
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll M,T,a,b,af,bf;cin>>T; bool can;
    for(ll i=1;i<=T;i++){
        cin>>N>>M; can = 1;
        init();
        while(M--){
            cin>>a>>b;
            if(can){
                af = _find(a); bf = _find(b);
                if(af != bf){
                    fa[af] = bf;
                    rela[af] = _mult(1,_mult(rela[a],rela[b]));
                }else if(rela[a] == rela[b]){
                    can = 0;
                }
            }
        }
        cout<<"Scenario #"<<i<<":"<<endl;
        cout<<(can?"No suspicious bugs found!":"Suspicious bugs found!")<<endl;
        cout<<endl;
    }
    return 0;
}
