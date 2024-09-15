#include<bits/stdc++.h>
using namespace std;
#define t node
const int N = 4000005;
struct Node {
    int ch[26];//现在不要管
    int len;//最大长度
    int fa;//父节点
}node [ N + 5];
int last=1,tot=1;
void extend(int c){
    if (node[last].ch[c]){
        int p = last, q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) last = q;
        else{
            int nq = last = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = nq;
            for(; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
    else{
        int p = last, np = last = ++tot;
        node[np].len = node[p].len + 1;
        for(; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
        if (!p) node[np].fa = 1;
        else{
            int q = node[p].ch[c];
            if (node[q].len == node[p].len + 1) node[np].fa = q;
            else{
                int nq = ++tot;
                node[nq] = node[q], node[nq].len = node[p].len + 1;
                node[np].fa = node[q].fa = nq;
                for(; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
            }
        }
    }
}
//==========板子=================================
vector<int>g[N];
string s[N];
int a[N];
int fa[N];
int find(int f){
    if(f==fa[f])return f;
    return fa[f]=find(fa[f]);
}
void slove() {
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
        fa[i]=i;
        cin>>s[i];
        last=1;
        for(int j=0;j<s[i].length();++j)extend(s[i][j]-'a');
    }
    for(int i=1;i<=n;++i){
        for(int j=0,p=1;j<s[i].size();++j){
            p=t[p].ch[s[i][j]-'a'];
            g[p].push_back(i);
        }
    }
    for(int i=2;i<=tot;++i)a[i]=i;

    sort(a+2,a+tot+1,[&](int x,int y){
        return t[x].len>t[y].len;
    });
    long long ans=0;
    for(int i=2;i<=tot;++i){
        for(int j=0;j<(int)g[a[i]].size()-1;++j){
            int x=g[a[i]][j],y=g[a[i]][j+1];
            int px=find(x),py=find(y);
            if(px!=py){
                fa[px]=py;
                ans+=t[a[i]].len;
            }
        }
        if(t[a[i]].fa)g[t[a[i]].fa].push_back(g[a[i]][0]);
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    slove();
}