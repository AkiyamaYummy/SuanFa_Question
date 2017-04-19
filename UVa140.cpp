#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
string line;
vector<unsigned int> nb[26],nodes,res;
uint _max=0,_min=10,value;
bool is_in[26];
int cmap[26];
void nb_init(){
    char c;
    memset(is_in,0,sizeof is_in);
    nodes.clear();
    for(uint i=0;i<26;i++)
        nb[i].clear();
    for(uint i=0;i<line.length();i++){
        if(i==0||line[i-1]==';')c=line[i];
        else if(line[i]!=':'&&line[i]!=';'){
            nb[c-'A'].push_back(line[i]-'A');
            nb[line[i]-'A'].push_back(c-'A');
            is_in[c-'A']=is_in[line[i]-'A']=1;
        }
    }
    for(uint i=0;i<26;i++)
        if(is_in[i]){
            nodes.push_back(i);
            sort(nb[i].begin(),nb[i].end());
            nb[i].erase(unique(nb[i].begin(),nb[i].end()),nb[i].end());
        }
}
void run(){
    _max=0;
    for(uint i=0;i<nodes.size();i++)
        cmap[nodes[i]]=i;
    for(uint i=0;i<nodes.size();i++){
        for(uint j=0;j<nb[nodes[i]].size();j++){
            value=abs(cmap[nodes[i]]-cmap[nb[nodes[i]][j]]);
            //cout<<(char)(nodes[i]+'A')<<' '<<(char)(nb[nodes[i]][j]+'A')<<' '<<value<<endl;
            if(value>=_min)
                return;
            if(value>_max)_max=value;
        }
    }
    if(_max<_min){
        _min=_max;
        res=nodes;
    }
}
int main(){
    while(cin>>line){
        if(line[0]=='#')break;
        else {
            nb_init();
            _min=10;
            do{
                run();
            }while(next_permutation(nodes.begin(),nodes.end()));
        }
        for(uint i=0;i<res.size();i++)cout<<(char)(res[i]+'A')<<' ';
        cout<<"-> "<<_min<<endl;
    }
}
