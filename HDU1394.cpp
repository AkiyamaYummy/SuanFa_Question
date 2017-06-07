#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 5000
ll N,line[MAXN],A[MAXN],d,m;
int main(){
    while(cin>>N){
        memset(A,0,sizeof(ll)*N);
        for(ll i=0;i<N;i++)cin>>line[i];
        for(ll i=0;i<N;i++){
            for(ll j=0;j<i;j++){
                if(line[i] < line[j])A[line[i]]++;
            }
        }
        d = m = 0;
        for(ll i=0;i<N;i++)d += A[i];
        m = d;
        for(ll i=N-1;i>=0;i--){
            ll n = line[i];
            d = d-A[n]+n;
            if(m > d)m = d;
            A[n] = 0;
            for(ll i=0;i<n;i++)A[i]++;
        }
        cout<<m<<endl;
    }
	return 0;
}
