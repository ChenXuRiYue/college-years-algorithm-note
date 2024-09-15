**costf_dinic.cpp**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int V = 20100;
const int E = 201000;
template<typename T>
struct MinCostGraph {
    int s, t, vtot;
    int head[V], etot;
    T dis[V], flow, cost;
    int pre[V];
    bool vis[V];
    struct edge {
        int v, nxt;
        T f, c;
    } e[E * 2];
    void addedge(int u, int v, T f, T c, T f2 = 0) {
        e[etot] = {v, head[u], f, c};
        head[u] = etot++;
        e[etot] = {u, head[v], f2, -c};
        head[v] = etot++;
    }
    bool spfa() {
        T inf = numeric_limits<T>::max() / 2;
        //如果要用0这个点的话，i要从0开始
        for(int i = 0; i <= vtot; ++i) {
            dis[i] = inf;
            vis[i] = false;
            pre[i] = -1;
        }
        dis[s] = 0;
        vis[s] = true;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            for(int i = head[u]; ~i; i = e[i].nxt) {
                int v = e[i].v;
                if(e[i].f && dis[v] > dis[u] + e[i].c) {
                    dis[v] = dis[u] + e[i].c;
                    pre[v] = i;
                    if(!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            q.pop();
            vis[u] = false;
        }
        return dis[t] != inf;
    }
    void augment() {
        int u = t;
        T f = numeric_limits<T>::max();
        while(~pre[u]) {
            f = min(f, e[pre[u]].f);
            u = e[pre[u] ^ 1].v;
        }

        flow += f;
        cost += f * dis[t];
        u = t;
        while(~pre[u]) {
            e[pre[u]].f -= f;
            e[pre[u] ^ 1].f += f;
            u = e[pre[u] ^ 1].v;
        }
    }
    pair<T, T> solve() {
        flow = 0;
        cost = 0;
        while(spfa())augment();
        return {flow, cost};
    }
    void init(int s_, int t_, int vtot_) {
        s = s_;
        t = t_;
        vtot = vtot_;
        etot = 0;
        //如果要用0这个点的话，i要从0开始
        for(int i = 0; i <= vtot; ++i)head[i] = -1;
    }
};
MinCostGraph<int> g;
void solve() {
    int n, m, S, T;
    cin >> n >> m >> S >> T;
    g.init(S, T, n + 10);
    for(int i = 1; i <= m; ++i) {
        int u, v, f, c;
        cin >> u >> v >> f >> c;
        g.addedge(u, v, f, c);
    }
    auto [flow, cost] = g.solve();
    cout << flow << " " << cost;
}
```
**dinic**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int V = 1e5+11;
const int E = V*30;
template<typename T>
struct FlowGraph {
    int s, t, vtot;
    int head[V], etot;
    int dis[V], cur[V];
    struct edge {
        int v, nxt;
        T f;
    } e[E * 2];

    void addedge(int u, int v, T f) {
        e[etot] = {v, head[u], f};
        head[u] = etot++;
        e[etot] = {u, head[v], 0};
        head[v] = etot++;
    }

    bool bfs() {
        //如果要用0这个点的话，i要从0开始
        for(int i = 0; i <= vtot; i++) {
            dis[i] = 0;
            cur[i] = head[i];
        }
        queue<int> q;
        q.push(s);
        dis[s] = 1;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i = head[u]; ~i; i = e[i].nxt) {
                if(e[i].f && !dis[e[i].v]) {
                    int v = e[i].v;
                    dis[v] = dis[u] + 1;
                    if(v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, T m) {
        if(u == t) return m;
        T flow = 0;
        for(int i = cur[u]; ~i; cur[u] = i = e[i].nxt) {
            if(e[i].f && dis[e[i].v] == dis[u] + 1) {
                T f = dfs(e[i].v, min(m, e[i].f));
                e[i].f -= f;
                e[i ^ 1].f += f;
                m -= f;
                flow += f;
                if(!m) break;
            }
        }
        if(!flow) dis[u] = -1;
        return flow;
    }

    T dinic() {
        T flow = 0;
        while(bfs()) flow += dfs(s, numeric_limits<T>::max());
        return flow;
    }
    void init(int s_, int t_, int vtot_) {
        s = s_, t = t_, vtot = vtot_;
        etot = 0;
        //如果要用0这个点的话，i要从0开始
        for(int i = 0; i <= vtot; i++) head[i] = -1;
    }
};
FlowGraph<int> g;
void solve(){

}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    solve();
}
```

**lct3.cpp**

```cpp
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
```

**lct4.cpp**

```cpp
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
```



**moban_O(nm).cpp**
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
//二分图最小顶点覆盖 = 二分图最大匹配
//二分图的最小边覆盖 = 顶点总数 - 孤立点数 - 二分图最大匹配
//二分图的最大独立集 = 顶点总数 - 最小顶点覆盖
//二分图的最大完全图 = 补图的最大独立集
struct augment_path {
    vector<vector<int>> g;
    vector<int> pa, pb,vis;  // 访问
    int n, m,dfn,res;       
    augment_path(int _n, int _m) : n(_n), m(_m),pa(_n,-1),pb(_m,-1),vis(_n,0){
        g.resize(n);
        res=dfn=0;
    }
    void add(int from, int to) {
        g[from].push_back(to);
    }
    bool dfs(int v) {
        vis[v] = dfn;
        for (int u : g[v]) 
            if (pb[u] == -1) {
                pb[u] = v;pa[v] = u;
                return true;
            }
        for (int u : g[v]) 
            if (vis[pb[u]] != dfn && dfs(pb[u])) {
                pa[v] = u;pb[u] = v;
                return true;
            }
        return false;
    }
    int solve() {
        while (true) {
            dfn++;
            int cnt = 0;
            for (int i = 0; i < n; i++) 
                if (pa[i] == -1 && dfs(i)) cnt++;
            if(cnt == 0)break;
            res += cnt;
        }
        return res;
    }
};
void solve(){
	int n,m,e;
	cin>>n>>m>>e;
	augment_path au(n,m);
	for(int i=1;i<=e;++i){
        int u,v;
        cin>>u>>v;
        --u,--v;
        au.add(u,v);
    }
    cout<<au.solve()<<"\n";
}
signed main(){
	std::ios::sync_with_stdio(false);cin.tie(0);
	solve();
}
```

