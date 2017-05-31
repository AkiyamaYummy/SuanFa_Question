#include<iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 510
#define MAXL 1000000000000000
ll pic[MAXN][MAXN],N;
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll M,W,T,a1,a2,l;cin>>T;
start:
    while(T--){
        cin>>N>>M>>W;
        for(ll i=1;i<=N;i++)
            for(ll j=1;j<=N;j++)
                pic[i][j]=(i==j?0:MAXL);
        while(M--){
            cin>>a1>>a2>>l;
            if(l < pic[a1][a2])
                pic[a1][a2] = pic[a2][a1] = l;
        }
        while(W--){
            cin>>a1>>a2>>l;
            pic[a1][a2]=(-1)*l;
        }
        for(ll k=1;k<=N;k++)
            for(ll i=1;i<=N;i++){
                for(ll j=1;j<=N;j++){
                    pic[i][j]=min(pic[i][j],pic[i][k]+pic[k][j]);
                }
                if(pic[i][i] < 0){
                    cout<<"YES"<<endl;
                    goto start;
                }
            }
        cout<<"NO"<<endl;
    }
    return 0;
}
