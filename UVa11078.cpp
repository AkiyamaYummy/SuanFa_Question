#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll T,n,a,max_num,max_cha;cin>>T;
    while(T--){
        cin>>n;
        cin>>a;n--;
        max_num = a;
        cin>>a;n--;
        max_cha = max_num-a;
        while(n--){
            cin>>a;
            if(max_num-a>max_cha)
                max_cha=max_num-a;
            if(max_num<a)max_num=a;
        }
        cout<<max_cha<<endl;
    }

    return 0;
}
