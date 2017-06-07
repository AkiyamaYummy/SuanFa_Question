#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
#define MAXN 50000
#define MAXNO 131072
ll l[MAXNO],r[MAXNO],N,code[MAXN];
stack<ll> last;
bool is_full[MAXNO];
void init(ll lo,ll hi,ll ini){
    l[ini] = r[ini] = hi-lo+1;
    is_full[ini] = 1;
    if(hi == lo){
        code[lo] = ini;
        return;
    }
    ll mi = (hi+lo)/2;
    init(lo,mi,ini*2); init(mi+1,hi,ini*2+1);
}
void C(ll inl,ll ord){
    ll ini = code[inl];
    if(ord == -1 || l[ini] == ord)return;
    l[ini] = r[ini] = ord;
    is_full[ini] = ord;
    while(ini > 1){
        ini /= 2;
        is_full[ini] = is_full[ini*2]&&is_full[ini*2+1];
        l[ini] = is_full[ini*2]?(l[ini*2]+l[ini*2+1]):l[ini*2];
        r[ini] = is_full[ini*2+1]?(r[ini*2+1]+r[ini*2]):r[ini*2+1];
    }
}
ll S(ll inl){
    ll is_right,neib,ini = code[inl],res = 0;
    if(!is_full[ini])return 0;
    while(ini != 1 && is_full[ini/2])ini /= 2;
    res += l[ini];
    if(ini == 1)return res;
    is_right = ini&1; neib = ini^1;
    res += is_right?r[neib]:l[neib];
    while(1){
        while(ini != 1 && (ini&1) == is_right)ini /= 2;
        if(ini == 1)break;
        neib = ini^1;
        res += is_right?l[neib]:r[neib];
        if(!is_full[neib])break;
        ini /= 2;
    }
    return res;
}
int main(){
    char inc; ll ord,inl,M;
    while(scanf("%d%d",&N,&M)==2){
        init(1,N,1); while(!last.empty())last.pop();
        while(M--){
            do{
                inc = getchar();
            }while(!isalpha(inc));
            if(inc == 'D')ord = 0;
            else if(inc == 'R')ord = 1;
            else ord = 2;
            if(ord != 1){
                scanf("%d",&inl);
                if(ord == 0)last.push(inl);
            }else{
                if(last.empty()){
                    ord = -1;
                }else{
                    inl = last.top(); last.pop();
                }
            }
            if(ord == 2)printf("%d\n",S(inl));
            else C(inl,ord);
        }
    }
	return 0;
}

