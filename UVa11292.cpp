#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
struct node{
    ll value;
    bool is_dragon;
    node(ll v,bool i){
        value = v;
        is_dragon = i;
    }
};
bool operator<(node a,node b){
    if(a.value==b.value){
        if(a.is_dragon)return 1;
        if(b.is_dragon)return 0;
    }
    return a.value<b.value;
}
ll n,m,a;
vector<node> line;
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    while(cin>>n>>m&&(n||m)){
        line.clear();
        for(ll i=0;i<n;i++){
            cin>>a;
            line.push_back(node(a,1));
        }
        for(ll i=0;i<m;i++){
            cin>>a;
            line.push_back(node(a,0));
        }
        sort(line.begin(),line.end());
        ll dra=0,con=0;
        for(ll i=0;i<line.size();i++){
            if(line[i].is_dragon){
                dra ++;
            }else if(dra){
                dra --;
                con += line[i].value;
            }
        }
        if(dra)cout<<"Loowater is doomed!"<<endl;
        else cout<<con<<endl;
    }

    return 0;
}
