#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 1010
ll N,uset[MAXN];
void uset_init(){
    for(ll i=0;i<=N;i++)uset[i] = i;
}
ll uset_find(ll a){
    ll r = a,b;
    while(uset[r] != r)r = uset[r];
    while(uset[a] != r){
        b = uset[a];
        uset[a] = r;
        a = b;
    }
    return r;
}
void uset_union(ll a,ll b){
    if(a > b)swap(a,b);
    uset[uset_find(b)] = uset_find(a);
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll M,a,b,sum;
    while(cin>>N && N){
        cin>>M;
        uset_init();
        while(M--){
            cin>>a>>b;
            uset_union(a,b);
        }
        sum = 0;
        for(ll i=1;i<=N;i++)
            if(i == uset_find(i))sum++;
        cout<<sum-1<<endl;
    }
    return 0;
}
