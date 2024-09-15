#include<bits/stdc++.h>
using namespace std;
const int N = 400050;
struct LCT {
    int ch[N][2], fa[N], tag[N], val[N], siz[N];
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = val[x] = siz[x] = 0; }
    int getch(int x) { return ch[fa[x]][1] == x; }
    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    void pushup(int x) { siz[x] = val[x] ^ siz[ch[x][0]] ^ siz[ch[x][1]]; }
    void pushdown(int x) {
        if (tag[x]) {
            if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
            if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }
    void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        pushup(y), pushup(x);
    }
    void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
            if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
    }
    void access(int x) {
        int y = 0;
        while (x) {
            splay(x);
            ch[x][1] = y;
            pushup(x);
            y = x;
            x = fa[x];
        }
    }
    void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
    }
    int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
    }
    int findfa(int x) {
        access(x), splay(x);
        pushdown(x), x = ch[x][0];
        while (pushdown(x), ch[x][1]) x = ch[x][1];
        return x;
    }
    void link(int x, int y) {
        //if (find(x) != find(y)) makeroot(x), fa[x] = y;
        access(x),splay(x),fa[x]=y;
    }
    void cut(int x, int y) {
        access(x),splay(x);
        ch[x][0]=fa[ch[x][0]]=0;
        //if (ch[y][0] == x && !ch[x][1])ch[y][0] = fa[x] = 0;
        if (ch[y][0] == x && fa[x]==y)ch[y][0] = fa[x] = 0,pushup(y);
    }
} tree;
set<pair<int,int>>ps[400000+50];
int idx=0,bl[400000+50];
int get(int id,int x){
    auto& s=ps[id];
    auto it =s.lower_bound({x,0});
    if(it->first==x)return it->second;
    int old=it->second,oldv=it->first;
    s.erase(it);
    bl[++idx]=id;
    int fa=tree.findfa(old);
    if(fa)tree.cut(old,fa);
    tree.link(old,idx);
    if(fa)tree.link(idx,fa);
    s.insert({x,old});
    s.insert({oldv,idx});
    return old;
}
void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;++i)ps[i].insert({m+1,++idx}),bl[idx]=i;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int a,b;
            cin>>a>>b;
            int v1=get(a,b),v2=get(a+1,b);
            int f1=tree.findfa(v1),f2=tree.findfa(v2);
            if(f1)tree.cut(v1,f1);
            if(f2)tree.cut(v2,f2);
            if(f1)tree.link(v2,f1);
            if(f2)tree.link(v1,f2);
        }
        else{
            int a;
            cin>>a;
            cout<<bl[tree.find(ps[a].begin()->second)]<<"\n";
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    solve();
}