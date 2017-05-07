#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 10010

vector<ll> sons[MAXN];
ll father[MAXN],len[MAXN],N;
ll l[MAXN][4];

ll dfs1(ll r){
    ll value,max1 = 0,max2 = 0;
    ll max1_neib = -1,max2_neib = -1;
    for(ll i=0;i<sons[r].size();i++){
        value = len[sons[r][i]]+dfs1(sons[r][i]);
        if(max1<value){
            max2 = max1;
            max2_neib = max1_neib;
            max1 = value;
            max1_neib = sons[r][i];
        }else{
            if(max2<value){
                max2 = value;
                max2_neib = sons[r][i];
            }
        }
    }
    l[r][0] = max1; l[r][1] = max2;
    l[r][2] = max1_neib; l[r][3] = max2_neib;
    return max1;
}
stack<ll> bfs_sta;
void bfs2(){
    ll r;
    bfs_sta.push(1);
    while(!bfs_sta.empty()){
        r = bfs_sta.top();
        bfs_sta.pop();
        for(ll i=0;i<sons[r].size();i++){
            bfs_sta.push(sons[r][i]);
        }
        if(r != 1){
            if(l[father[r]][2] != r){
                if(l[r][0] < len[r]+l[father[r]][0]){
                    l[r][1] = l[r][0];
                    l[r][3] = l[r][2];
                    l[r][0] = len[r]+l[father[r]][0];
                    l[r][2] = father[r];
                }else if(l[r][1]<len[r]+l[father[r]][0]){
                    l[r][1] = len[r]+l[father[r]][0];
                    l[r][3] = father[r];
                }
            }else{
                if(l[r][0] < len[r]+l[father[r]][1]){
                    l[r][1] = l[r][0];
                    l[r][3] = l[r][2];
                    l[r][0] = len[r]+l[father[r]][1];
                    l[r][2] = father[r];
                }else if(l[r][1]<len[r]+l[father[r]][1]){
                    l[r][1] = len[r]+l[father[r]][1];
                    l[r][3] = father[r];
                }
            }
        }
    }
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll L,F;
    father[1] = 0;
    while(cin>>N){
        for(ll i=0;i<=N;i++)sons[i].clear();
        for(ll i=2;i<=N;i++){
            cin>>F>>L;
            father[i] = F;
            len[i] = L;
            sons[F].push_back(i);
        }
        dfs1(1);
        /*
        for(ll i=1;i<=N;i++){
            cout<<l[i][0]<<" "<<l[i][1]<<" "<<l[i][2]<<" "<<l[i][3]<<endl;
        }
        */
        bfs2();
        for(ll i=1;i<=N;i++){
            cout<<l[i][0]<<endl;
        }
    }

    return 0;
}
