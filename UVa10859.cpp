#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll M,N,father[1010],on,off;
bool has_mark[1010];
vector<ll> pic[1010];
ll dp(ll n,bool father_light,bool is_root){
    has_mark[n] = 1;
    ll value_on = 2000,value_off = 0;
    if(father_light)value_on += 1;
    if(is_root)value_on -= 1;
    for(ll i=0;i<pic[n].size();i++){
        if(pic[n][i]!=father[n]){
            father[pic[n][i]] = n;
            value_on += dp(pic[n][i],1,0);
            value_off += dp(pic[n][i],0,0);
        }
    }
    if(father_light){
        if(value_on/2000==value_off/2000){
            return (value_on%2000>value_off%2000)?value_on:value_off;
        }
        return min(value_on,value_off);
    }
    else return value_on;
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll T,a,b,value;cin>>T;
    while(T--){
        cin>>N>>M;
        for(ll i=0;i<M;i++){
            cin>>a>>b;
            pic[a].push_back(b);
            pic[b].push_back(a);
        }
        memset(has_mark,0,sizeof has_mark);
        memset(father,-1,sizeof father);
        value = 0;
        for(ll i=0;i<N;i++){
            if(!has_mark[i]){
                value += dp(i,1,1);
            }
        }
        for(ll i=0;i<N;i++)pic[i].clear();
        cout<<value/2000<<" "<<value%2000<<" "<<(M-value%2000)<<endl;
    }

    return 0;
}
