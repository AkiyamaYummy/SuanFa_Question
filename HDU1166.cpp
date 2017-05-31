#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 50010
ll N,C[MAXN];
void add(ll r,ll a){
    while(r <= N){
        C[r] += a;
        r += (r&-r);
    }
}
ll sum(ll r){
    if(r == 0)return 0;
    ll s = 0;
    while(r){
        s += C[r];
        r -= (r&-r);
    }
    return s;
}
int main(){
	//freopen("_in.txt","r",stdin);
    //freopen("_out.txt","w",stdout);

    ll T,a,b,t=0; char ord[10]; scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        memset(C,0,sizeof(ll)*(N+1));
        printf("Case %d:\n",++t);
        for(ll i=1;i<=N;i++){
            scanf("%d",&a); add(i,a);
        }
        while(scanf("%s",ord)==1 && ord[0] != 'E'){
            scanf("%d%d",&a,&b);
            if(ord[0] == 'A'){
                add(a,b);
            }else if(ord[0] == 'S'){
                add(a,-b);
            }else{
                printf("%d\n",sum(b)-sum(a-1));
            }
        }
    }
	return 0;
}
