#include<bits/stdc++.h>
using namespace std;
#define int long long
using namespace std;
int ch[500050][2],fa[500050],tag[500050],siz[500050],val[500050],siz2[500000+50];
void clear(int x){ch[x][0]=ch[x][1]=fa[x]=tag[x]=siz2[x]=siz[x]=0;}
int getch(int x){return x==ch[fa[x]][1];}
int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
void pushup(int x){clear(0);if(x)siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1+siz2[x];}
void pushdown(int x){
    if(tag[x]){
        if(ch[x][0])swap(ch[ch[x][0]][0],ch[ch[x][0]][1]),tag[ch[x][0]]^=1;
        if(ch[x][1])swap(ch[ch[x][1]][0],ch[ch[x][1]][1]),tag[ch[x][1]]^=1;
        tag[x]=0;   
    }
}

//黑盒  旋转到当前块的根
//也就是说，我们对于同一块内的splay进行选择，他之后还是中序遍历的结果还是对应着原树中的一条实链
void updata(int x){
    if(!isroot(x))updata(fa[x]);
    pushdown(x);
}
void rorate(int x){
    int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
    fa[x]=z;
    if(!isroot(y))ch[z][chy]=x;
    ch[y][chx]=ch[x][chx^1];
    fa[ch[x][chx^1]]=y;
    ch[x][chx^1]=y;
    fa[y]=x;
    pushup(y),pushup(x);
}
void splay(int x){
    updata(x);
    for(int f=fa[x];f=fa[x],!isroot(x);rorate(x)){
        if(!isroot(f))rorate(getch(x)==getch(f)?f:x);
    }
}

//access 在原树中把从根到x的所有点放在一条实链里，使根到x成为一条实路径，并且在同一棵 Splay 里。并且 下面没有实边。
void access(int x){
    int y=0;
    while(x){
        splay(x);
        siz2[x]+=siz[ch[x][1]]-siz[y];
        ch[x][1]=y;
        pushup(x);
        y=x;
        x=fa[x];
    }
}
// makeroot(x)在原树中，把x当成根
void makeroot(int x){
    access(x);// 此操作后 x的splay块的 根 变成了 原树的根
    splay(x);
    swap(ch[x][0],ch[x][1]);
    tag[x]^=1;
}
int find(int x){
    access(x);
    splay(x);
    while (ch[x][0])x=ch[x][0];
    splay(x);
    return x;
}
void link(int x,int y){
    if(find(x)!=find(y))makeroot(x),fa[x]=y;
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);   
    //在辅助树上，y的子树就包含了 路径上的信息
}
void cut(int x,int y){
    split(x,y);
    if(ch[y][0]==x&&!ch[x][1])ch[y][0]=fa[x]=0;
}
int que(int x,int y){
    split(x,y);
    return siz[y];
}
void sets(int x,int y){
    splay(x);
    val[x]=y;
    pushup(x);
}
void solve(){
    map<int,vector<pair<int,int>>>mp;
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)siz[i]=1;
    for(int i=1;i<=n-1;++i){
        int u,v,c;
        cin>>u>>v>>c;
        mp[c].push_back({u,v});
        makeroot(u);
        makeroot(v);
        fa[u]=v;
        siz2[v]+=siz[u];
    }
    int ans=0;
    for(auto j:mp){
        for(auto pii:j.second){
            int x=pii.first,y=pii.second;
            split(x,y);
            ch[y][0]=fa[x]=0;
            pushup(x);
            makeroot(x);
            makeroot(y);
        }
        for(auto pii:j.second){
            int x=pii.first,y=pii.second;
            makeroot(x),makeroot(y);
            ans+=(siz[x])*(siz[y]);
        }
        for(auto pii:j.second){
            int x=pii.first,y=pii.second;
            makeroot(x);
            makeroot(y);
            fa[x]=y;
            siz2[y]+=siz[x];
        }
    }
    cout<<ans<<"\n";
}
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(0);
    solve();
}