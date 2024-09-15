#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>g[200000+50];
int ctr=-1,n,k,sz[200000+50],del[200000+50];
void dfs(int u,int f=0){
    sz[u]=1;
    int mx=0;
    for(auto v:g[u]){
        if(del[v]||v==f)continue;
        dfs(v,u);
        if(ctr!=-1)return ;
        mx=max(mx,sz[v]);
        sz[u]+=sz[v];
    }
    mx=max(mx,n-sz[u]);
    if(mx<=n/2){
        ctr=u;
        sz[f]=n-sz[u];
    }
}
int tmp[200000+50],tot,cnt,lens[200000+50];
void dfs2(int u,int f,int len){
    if(len>k)return ;
    cnt+=lens[k-len]+(len==k);
    tmp[tot++]=len;
    for(auto v:g[u]){
        if(del[v]||v==f)continue;
        dfs2(v,u,len+1);
    }
}
void run(int u){
    for(auto v:g[u]){
        if(del[v])continue;
        dfs2(v,u,1);
        for(int i=0;i<tot;++i)lens[tmp[i]]++;
        tot=0;
    }
    for(int i=0;i<=k;++i)lens[i]=0;
    del[u]=1;
    for(auto v:g[u]){
        if(del[v])continue;
        n=sz[v];
        ctr=-1;
        dfs(v);
        run(ctr);
    }
}
void solve(){
    cin>>n>>k;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    run(ctr);
    cout<<cnt<<"\n";
}  
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}