#include <bits/stdc++.h>

using namespace std;

int main(){
    int n,m,c[1010],dp[1010],_max;
    while(cin>>n && n){
        for(int i=0;i<n;i++)cin>>c[i];
        cin>>m;
        for(int i=1;i<n;i++)
            if(c[i-1] > c[i]){
                int t = c[i];
                c[i] = c[i-1];c[i-1]=t;
            }
        memset(dp,0,sizeof dp);
        for(int i=0;i<n-1;i++){
            for(int j=m-5;j>=0;j--){
                if(j < c[i]||dp[j-c[i]]+c[i]>m-5)continue;
                if(dp[j]<dp[j-c[i]]+c[i])
                    dp[j] = dp[j-c[i]]+c[i];
            }
        }
        _max = 0;
        for(int i=0;i<=m-5;i++)
            if(_max < dp[i])_max = dp[i];
        cout<<(m<5?m:m-(_max+c[n-1]))<<endl;
    }
}
