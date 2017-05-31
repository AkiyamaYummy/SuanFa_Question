#include<iostream>
#include<cstring>
#include<map>
#include<string>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 50
ll N;double pic[MAXN][MAXN];map<string,ll> _m;
void init(){
    _m.clear();
    memset(pic,0,sizeof pic);
    for(ll i=0;i<N;i++)pic[i][i] = 1;
}
int main(){
    ll M,w1,w2,T = 0;double h;
    string s,s1,s2;
    start:
    while(cin>>N && N){
        init();
        for(ll i=0;i<N;i++){
            cin>>s; _m[s] = i;
        }
        cin>>M;
        while(M--){
            cin>>s1>>h>>s2;
            w1 = _m[s1]; w2 = _m[s2];
            if(pic[w1][w2] < h)
                pic[w1][w2] = h;
        }
        for(ll k=0;k<N;k++){
            for(ll i=0;i<N;i++){
                for(ll j=0;j<N;j++){
                    if(pic[i][k]*pic[k][j]>pic[i][j]){
                        pic[i][j] = pic[i][k]*pic[k][j];
                    }
                }
                if(pic[i][i] > 1){
                    cout<<"Case "<<++T<<": Yes"<<endl;
                    goto start;
                }
            }
        }
        cout<<"Case "<<++T<<": No"<<endl;
    }
    return 0;
}
