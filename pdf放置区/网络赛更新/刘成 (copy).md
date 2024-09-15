[TOC]



#### 1.  ALL small

##### **decanter.cpp**

```cpp
// 查询 第x小的序列 是什么？
const int MAXN=1e5+50;int n=10;;
int fact[MAXN] = {1}, P[MAXN], A[MAXN]; // fact需要在外部初始化
void decanter(int x, int n)             // x为排列的排名，n为排列的长度
{
    x--;
    vector<int> rest(n, 0);
    iota(rest.begin(), rest.end(), 1); // 将rest初始化为1,2,...,n
    for (int i = 1; i <= n; ++i)
    {
        A[i] = x / fact[n - i];
        x %= fact[n - i];
    }
    for (int i = 1; i <= n; ++i)
    {
        P[i] = rest[A[i]];
        rest.erase(lower_bound(rest.begin(), rest.end(), P[i]));
    }
    for(int i=1;i<=n;++i)cout<<P[i]<<"\n";
}
```

##### **euler.cpp**

```cpp
void euler(int n)
{
	int m=0;
	for(int i=2;i<=n;i++)
	{
		if(!phi[i]) prime[++m]=i,phi[i]=(i-1); //是质数
		for(int j=1;i*prime[j]<=n&&j<=m;j++)
		{
			phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]); //不能整除或能整除
			if(i%prime[j]==0) break;
		}
	}
	for(int i=1;i<=n;i++) phi[i]+=phi[i-1];
}
```

##### **hash**

```cpp
struct my_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  // 针对 std::pair<int, int> 作为主键类型的哈希函数
  size_t operator()(pair<uint64_t, uint64_t> x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
};
```

#### 2 . **Descartes 笛卡尔树**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int ls[maxn],rs[maxn],siz[maxn],stk[maxn],w[maxn];
void bulid(int n){
    for(int i=1;i<=n;++i)siz[i]=ls[i]=rs[i]=stk[i]=0;
    int top=0;
    for(int i=1;i<=n;++i){
        int k=top;
        while(k&&w[i]<=w[stk[k]])k--;
        if(k)rs[stk[k]]=i;
        if(k<top)ls[i]=stk[k+1];
        stk[++k]=i,top=k;
    }
}
void solve(){

}
signed main(){
    std::ios::sync_with_stdio(false); 
    solve();
}

```

-----

#### 3.  GSA

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000000+50;
//求n个字符串中所有不同子串的个数。
struct GSA {
    struct State {
        int fa, len, next[26];
    } G[N];
    int cnt = 1;
    void insert(const string &s) {
        int p = 1;
        for (auto &c : s) {
            int &q = G[p].next[c - 'a'];
            if (!q) q = ++cnt;
            p = q;
        }
    }
    int insert(int last, int ch) { 
        int cur = G[last].next[ch], p;
        G[cur].len = G[last].len + 1;
        for (p = G[last].fa; p && !G[p].next[ch]; p = G[p].fa) 
            G[p].next[ch] = cur;
        int q = G[p].next[ch];
        if (q == 0) G[cur].fa = 1;
         else if (G[p].len + 1 == G[q].len) G[cur].fa = q;
         else {
            int r = ++cnt;
            G[r].fa = G[q].fa;
            for (int i = 0; i < 26; ++i)
                if (G[G[q].next[i]].len)  G[r].next[i] = G[q].next[i];
            G[r].len = G[p].len + 1;
            for (; p && G[p].next[ch] == q; p = G[p].fa)  G[p].next[ch] = r;
            G[cur].fa = G[q].fa = r;
        }
        return cur;
    }
    int ans=0;// add
    void bfs() {
        queue<pair<int, int>> Q;
        for (int i = 0; i < 26; ++i)
            if (G[1].next[i]) Q.emplace(1, i);
        while (Q.size()) {
            auto j = Q.front();auto f=j.first,ch=j.second;Q.pop();
            int p = insert(f, ch);
            ans+=G[p].len-G[G[p].fa].len;  //   add
            for (int i = 0; i < 26; ++i)
                if (G[p].next[i]) Q.emplace(p, i);
        }
    }
}gsa;
void slove(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
        string s;
        cin>>s;
        gsa.insert(s);
    }
    gsa.bfs();
    cout<<gsa.ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false); 
    cout.tie(0);cin.tie(0);
    slove();
}
```

-----------

#### 4. hebin

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
const int M = 2e5 + 5;
struct node {
    int cnt = 0;//出现次数
    int mx = 0;//出现次数最多的编号的和
    int l = 0, r = 0;
}tr[M * 20];
#define ls(x) (tr[x].l)
#define rs(x) (tr[x].r)
#define cnt(x) (tr[x].cnt)
#define mx(x) (tr[x].mx)
int tot = 1;
int root[N], c[N], n;
int ans[N];
vector<int>g[N];
void pushup(int x) {
    if (cnt(ls(x)) > cnt(rs(x))) {
        cnt(x) = cnt(ls(x));
        mx(x) = mx(ls(x));
    }
    else if (cnt(ls(x)) < cnt(rs(x))) {
        cnt(x) = cnt(rs(x));
        mx(x) = mx(rs(x));
    }
    else {
        cnt(x) = cnt(ls(x));
        mx(x) = mx(ls(x)) + mx(rs(x));
    }
}
void upd(int now, int l, int r, int pos, int k) {
    if (l == r) {
        cnt(now) += k;
        mx(now) = l;
    }
    else {
        int mid = (l + r) / 2;
        if (pos <= mid) {
            if (!ls(now))ls(now) = ++tot;
            upd(ls(now), l, mid, pos, k);
        }
        else {
            if (!rs(now))rs(now) = ++tot;
            upd(rs(now), mid + 1, r, pos, k);
        }
        pushup(now);
    }
}
void upd(int now, int pos, int k) {
    upd(now, 1, n, pos, k);
}
int merge(int a, int b, int l, int r) {
    if (!a) return b;
    if (!b) return a;
    if (l == r) {
        cnt(a) += cnt(b);
        mx(a) = l;
        return a;
    }
    int mid = (l + r) / 2;
    ls(a) = merge(ls(a), ls(b), l, mid);
    rs(a) = merge(rs(a), rs(b), mid + 1, r);
    pushup(a);
    return a;
}
void dfs(int u, int fa) {
    root[u] = ++tot;
    for (int v : g[u]) {
        if (v == fa)continue;
        dfs(v, u);
        merge(root[u], root[v], 1, n);
    }
    upd(root[u], c[u], 1);
    ans[u] = mx(root[u]);
}
void slove() {
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> c[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)cout << ans[i] << " ";
    cout << "\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    slove();
}
```

#### 5. kmp

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010, M = 1000010;
char s[N],p[N];
int ne[N];
int n,m;
vector<int>ans;
void build_next(string &p){
    for(int i=2,j=0;i<=m;++i)
   {
      while(j&&p[i]!=p[j+1])j=ne[j];
      if(p[i]==p[j+1])j++;
      ne[i]=j;
   }
}
void kmp(){
    cin>>s+1;
    cin>>p+1;
    n=strlen(s+1);
    m=strlen(p+1);
    build_next();
    for(int i=1 ,j=0;i<=n;++i){
       while (j&&s[i]!=p[j+1])  j=ne[j];
       if (s[i]==p[j+1])  ++j;
       if (j==m)  ans.push_back(i-m+1),j=ne[j];
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    kmp();
    for(auto i:ans)cout<<i<<"\n";
    for(int i=1;i<=m;++i)cout<<ne[i]<<" ";
    cout<<"\n";


    //cout<<"hh\n"<<endl;
    //char ch=getchar();
}
```

#### 6.pam

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300000+50;
struct PAM {
    int size, tot, last;
    int cnt[N], tr[N][26], len[N], fail[N];
    char s[N];
    int node(int l) {  // 建立一个新节点，长度为 l
        size++;
        memset(tr[size], 0, sizeof(tr[size]));
        len[size] = l;
        fail[size] = cnt[size] = 0;
        return size;
    }
    void init() {  // 初始化
        size = -1; last = 0;
        s[tot = 0] = '$';
        node(0); node(-1);
        fail[0] = 1;
    }
    int getfail(int x) {  // 找后缀回文
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }
    void add(char c) {  // 建树
        s[++tot] = c;
        int now = getfail(last);
        if (!tr[now][c]) {
            int x = node(len[now] + 2);
            fail[x] = tr[getfail(fail[now])][c];
            tr[now][c] = x;
            // cnt[x]=cnt[fail[x]]+1;  如果需要一个一个加入 并且计算以 其为末尾的回文个数
        }
        last = tr[now][c];
        cnt[last]++;
    }
};
//因为PAM添加的点的下标满足拓扑序，也就是标号小的点一定是标号大的点的父亲（反正不能是儿子）
PAM pam;
/*
void dfs(int u) {
    in[u] = ++tim;
    sz[u] = 1;
    for (int v = 0; v < 26; v++) {
        if (pam.tr[u][v]) {
            dfs(pam.tr[u][v]);
            sz[u] += sz[pam.tr[u][v]];
        }
    }
    out[u] = tim;
}
for (int i = 2; i <= PAM::size; i++) {
        g[PAM::fail[i]].push_back(i);
    }
*/
void slove(){
    string s;
    cin>>s;
    int n=s.length();
    pam.init();
    for(auto c:s)pam.add(c-'a');
    for(int i=pam.size;i>=2;--i){
        pam.cnt[pam.fail[i]]+=pam.cnt[i];//这里处理完以后cnt表示这个回文子串出现的次数
    }
    int ans=0;
    for(int i=2;i<=pam.size;++i){
        ans=max(ans,pam.len[i]*pam.cnt[i]);
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);cout.tie(0);
    slove();
}
```



#### 7. pam++

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300000+50;
struct PAM {
    int size, tot, last;
    int cnt[N], tr[N][26], len[N], fail[N];
    char s[N];
    int node(int l) {  // 建立一个新节点，长度为 l
        size++;
        memset(tr[size], 0, sizeof(tr[size]));
        len[size] = l;
        fail[size] = cnt[size] = 0;
        return size;
    }
    void init() {  // 初始化
        size = -1; last = 0;
        s[tot = 0] = '$';
        node(0); node(-1);
        fail[0] = 1;
    }
    int getfail(int x) {  // 找后缀回文
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }
    void add(char c) {  // 建树
        s[++tot] = c;
        int now = getfail(last);
        if (!tr[now][c]) {
            int x = node(len[now] + 2);
            fail[x] = tr[getfail(fail[now])][c];
            tr[now][c] = x;
        }
        last = tr[now][c];
        cnt[last]++;
    }
};
//因为PAM添加的点的下标满足拓扑序，也就是标号小的点一定是标号大的点的父亲（反正不能是儿子）
PAM pam;
int tim,sz[N],in[N],out[N];
vector<int>g[N];
void dfs(int u) {
    in[u] = ++tim;
    sz[u] = 1;
    for (int v = 0; v < 26; v++) {
        if (pam.tr[u][v]) {
            dfs(pam.tr[u][v]);
            sz[u] += sz[pam.tr[u][v]];
        }
    }
    out[u] = tim;
}
int tree[N];
int lowbit(int x){return x&-x;}
void updata(int p,int x){
    while(p<N){
        tree[p]+=x;
        p+=lowbit(p);
    }
}
int query(int p){
    int res=0;
    while(p){res+=tree[p];p-=lowbit(p);}
    return res;
}
void slove(){
    string s;
    cin>>s;
    int n=s.length();
    memset(tree,0,sizeof(tree));
    tim=0;
    pam.init();
    for(auto c:s)pam.add(c-'a');
    dfs(0),dfs(1);
    int ans=0;
    for (int i = 2; i <= pam.size; i++) {
        g[pam.fail[i]].push_back(i);
    }
    for(int i=2;i<=pam.size;++i){
        g[i].push_back(i);
        sort(g[i].begin(),g[i].end(),[](int x,int y){return pam.len[x]<pam.len[y];});
        vector<int>res;
        int sum=0;
        for(auto v:g[i]){
            if(i==v){
                ans+=sz[i]-1;
                updata(in[i],1);
                updata(out[i]+1,-1);
                res.push_back(i);
            }
            else if(query(in[v])==0){
                ans+=sz[v];
                updata(in[v],1),updata(out[v]+1,-1);
                res.push_back(v);
            }
        }
        for(auto j:res)updata(in[j],-1),updata(out[j]+1,1);
        g[i].clear();
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    for(int i=1;i<=t;++i){
        cout<<"Case #"<<i<<": ";
        slove();
    }
    
}

```

-------

#### 8. tail mc one

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//给定一个只包含小写字母的字符串 S。
//请你求出 S 的所有出现次数不为 1 的子串的出现次数乘上该子串长度的最大值
const int N = 1000005;
struct node {
    int ch[26];//现在不要管
    int len;//最大长度
    int father;//父节点
};
node t[2 * N + 5];
int last = 1, ind = 1;
int siz[2 * N];
int ed[2 * N];//添加部分   记录s[1,id]对应SAM的位置
void insert(int c,int id){
    int p = last;
    int np = last = ++ind;
    t[np].len = t[p].len + 1;
    siz[np] = 1;
    ed[id] = np;//添加部分
    for (;p&&!t[p].ch[c];p = t[p].father)t[p].ch[c] = np;
    if (!p)t[np].father = 1;
    else{
        int q = t[p].ch[c];
        if (t[p].len + 1 == t[q].len)  t[np].father = q;
        else{
            int nq = ++ind;
            t[nq] = t[q];
            t[nq].len = t[p].len + 1;
            t[q].father = t[np].father = nq;
            for (; p && t[p].ch[c] == q; p = t[p].father) t[p].ch[c] = nq;
        }
    }
}
//==========板子=================================
vector<int>g[2 * N];
string s;
int ans = 0;
void dfs(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa)continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
    if (siz[u] != 1)ans = max(ans, t[u].len*siz[u]);
}
void slove() {
    cin >> s;
    int n = s.length();
    for (int i = 1; i <= n; i++)insert(s[i - 1] - 'a',i);
    for (int i = 2; i <= ind; i++)  {
        g[t[i].father].push_back(i);
    }
    dfs(1, 0);
    cout << ans << endl;
}
/*
int u = 1;
for (char c : t) {
    while (u != 1 && tr[u][c - 'a'] == 0) {
        u = fa[u];
    }
    if (u == 1 && tr[u][c - 'a'] == 0)continue;
    u = tr[u][c - 'a'];
}
*/
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    slove();
}
```

-----

#### 9. acmc

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct kkk
{
    int son[26],flag,fail;
}trie[1000000+10];
int n,cnt;
map<int,int>mp;
vector<int>g[300005];
int ans[300005];
void insert(string &s,int id){
    int cur=0 ;
    for(auto c:s){
        int v=c-'a';
        if(!trie[cur].son[v]){
            trie[cur].son[v]=++cnt;
        }
        cur=trie[cur].son[v];
    }
    trie[cur].flag++;
    mp[id]=cur;
}
void get_fail(){
    queue<int>q;
    for(int i=0;i<26;++i)if(trie[0].son[i])q.push(trie[0].son[i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<26;++i){
            int v=trie[u].son[i];
            int fail=trie[u].fail;
            if(!v){
                trie[u].son[i]=trie[fail].son[i];
                continue;
            }
            trie[v].fail=trie[fail].son[i];
            q.push(v);
        }
    }
    for(int i=1;i<=cnt;++i){
        g[trie[i].fail].push_back(i);
    }
}
void query(string &s){
    int u=0;
    for(auto c:s){
        u=trie[u].son[c-'a'];
        ans[u]++;
    }
}
void dfs(int u){
    for(auto v:g[u]){
        dfs(v);
        ans[u]+=ans[v];
    }
}
void get_ans(){
    dfs(0);
    //for(int i=0;i<26;++i)if(trie[0].son[i])dfs(trie[0].son[i]);
}
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
        string u;
        cin>>u;
        insert(u,i);
    }
    get_fail();
    string s;
    cin>>s;
    query(s);
    get_ans();
    for(int i=1;i<=n;++i){
        cout<<ans[mp[i]]<<" ";
    }
    cout<<"\n";
}
signed main(){
	std::ios::sync_with_stdio(false);
    solve();
}
```

-----

#### 10 acmc two

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 1000001
using namespace std;
struct kkk
{
    int son[26],flag,fail,ans;
    void clear(){for(int i=0;i<26;++i)son[i]=0;ans=fail=flag=0;}
}trie[2000000+1000];
int n,cnt,ans,in[2000000+1000];
map<int,int>mp;
queue<int>q;
char s[2000000+1000];
int vis[2000000+1000];
void insert(char *st,int num){
    int cur=1 ,len=strlen(st);
    for(int i=0;i<len;++i){
        int v=st[i]-'a';
        if(!trie[cur].son[v]){
            trie[cur].son[v]=++cnt;
        }
        cur=trie[cur].son[v];
    }
    if(!trie[cur].flag)trie[cur].flag=num;
    mp[num]=trie[cur].flag;
}
void get_fail(){
    for(int i=0;i<26;++i)trie[0].son[i]=1;
    q.push(1);trie[1].fail=0;
    while(!q.empty()){
        int u=q.front();q.pop(); 
        for(int i=0;i<26;++i){  
            int v=trie[u].son[i]; 
            int fail=trie[u].fail;
            if(!v){
                trie[u].son[i]=trie[fail].son[i];
                continue;
            }
            trie[v].fail=trie[fail].son[i];
            in[trie[v].fail]++;
            q.push(v);
        }
    }
}
void topu(){
    for(int i=1;i<=cnt;++i){
        if(in[i]==0)q.push(i);
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[trie[u].flag]=trie[u].ans;
        int v=trie[u].fail;
        in[v]--;
        trie[v].ans+=trie[u].ans;
        if(!in[v])q.push(v);
    }
}
void query(char *s){
    int u=1,len=strlen(s);
    for(int i=0;i<len;++i){
        u=trie[u].son[s[i]-'a'],trie[u].ans++;
    }
}
signed main(){
    std::ios::sync_with_stdio(false);  
    cin>>n;
    cnt =1;
    for(int i=1;i<=n;++i){
        cin>>s;
        insert(s,i);
    }
    cin>>s;
    get_fail();
    query(s); 
    topu();
   for(int i=1;i<=n;++i)cout<<vis[mp[i]]<<"\n";
}
```

#### 11 boruvka

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int B=29;
int a[200000+50],tree[4000000+50][2],tot=0;
int L[4000000+50],R[4000000+50],siz[4000000+50];
int pw[50];//https://codeforces.com/contest/888/problem/G
void insert(int x,int id){
    int u=0;
    for(int i=B;i>=0;--i){
        int tag=(x>>i)&1;
        if(!tree[u][tag])tree[u][tag]=++tot;
        u=tree[u][tag];
        siz[u]++;
        if(!L[u])L[u]=id;
        R[u]=id;
    }
}
int query(int u,int x,int bit){
    if(bit<0)return 0;
    int tag=(x>>bit)&1;
    if(tree[u][tag]) return query(tree[u][tag],x,bit-1);
    else return query(tree[u][tag^1],x,bit-1)+pw[bit];
}
int dfs(int u,int bit){
    if(tree[u][0]&&tree[u][1]){
        int tag=(siz[tree[u][1]]<siz[tree[u][0]]);
        int ans=1e18;
        for(int i=L[tree[u][tag]];i<=R[tree[u][tag]];++i){
            ans=min(ans,query(tree[u][tag^1],a[i],bit-1)+pw[bit]);
        }
        return dfs(tree[u][0],bit-1)+dfs(tree[u][1],bit-1)+ans;
    }
    else if(tree[u][0])return dfs(tree[u][0],bit-1);
    else if(tree[u][1])return dfs(tree[u][1],bit-1);
    return 0;
}
void slove(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;++i)insert(a[i],i);
    cout<<dfs(0,B)<<"\n";
}
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    pw[0]=1;
    for(int i=1;i<=B;++i)pw[i]=pw[i-1]*2;
    slove();
}
```

-----

#### 12 cht

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Line{
    int k, b;
    double x;
    double operator[](double x) const { return k * x + b; }
    double operator&(const Line &l) const { return double(l.b - b) / (k - l.k); } // 交点横坐标
};
deque<Line> Q;
void update(const Line &l){// 如果X(i)单调递减，把判断出队时的<=换成>=，负无穷大换成正无穷大
    double x = -INFINITY;
    while (!Q.empty() && (x = l & Q.back()) <= Q.back().x)Q.pop_back();
    Q.push_back({l.k, l.b, x});
}
int query(int x){
    while (Q.size() > 1 && Q[1].x <= x)
        Q.pop_front();
    Q.front().x = -INFINITY;
    return Q.front()[x];
}
// dp[i]=max(A[i]+B[j]+K[j]*X[i])
int K(int i) { /* ... */ }//  k,x都单增,求最大
int X(int i) { /* ... */ }
int A(int i) { /* ... */ }
int B(int i) { /* ... */ }
int run(){
    // dp[0] = 0; // 起始状态
    for (int i = 0; i <= n; ++i)
    {
        if (i) dp[i] = query(X(i)) + A(i);
        update({K(i), B(i)});
    }
    return dp[n];
}
signed main(){
    std::ios::sync_with_stdio(false);
    solve();
}

```

----



####  13 dfs on tree

```cpp
#include <bits/stdc++.h>
using namespace std;  
typedef long long ll;
/*
vector<int>sub[500005];
vector<int>e[500005];
int id[500005];
int tot=1;
void dfs(int rt,int fa){
    int mx=-1,k=0;
    id[rt]=++tot;
    for(auto j:e[rt]){
        if(rt==fa)continue;
        dfs(j,rt);
        if(sub[j].size()>mx){
            mx=sub[j].size();
            k=j;
        }
    }
    if(mx!=-1)id[rt]=id[k];
    for(auto j:e[rt]){
        if(j==k)continue;
        if(j==fa)continue;
        for(auto x:sub[id[j]]){
            sub[id[rt]].push_back(x);
        }
    }
    sub[id[rt]].push_back(rt);
}
*/
int c[100000+5],id[100005],ans[100005];
struct node
{
    int mx_cnt=0;
    int mx_sum=0;
    map<int,int>cnt;
    vector<int>list;
    void add(int u){
        cnt[c[u]]++;
        if(cnt[c[u]]>mx_cnt)mx_cnt=cnt[c[u]],mx_sum=c[u];
        else if(cnt[c[u]]==mx_cnt)mx_sum+=c[u];
        list.push_back(u);
    }
    int size(){return list.size();} 
}sub[100000+5];
const int N=1e5+5;
vector<int>e[100005];
int tot=0;
void dfs(int rt,int fa){
    int mx=0,k=-1;
    id[rt]=++tot;
    for(auto j:e[rt]){
        if(j==fa)continue;
        dfs(j,rt);
        if(sub[id[j]].size()>mx){
            mx=sub[id[j]].size();
            k=j;
        }
    }
    if(k!=-1)id[rt]=id[k];
    for(auto j:e[rt]){
        if(j==k)continue;
        if(j==fa)continue;
        for(auto x:sub[id[j]].list){
            sub[id[rt]].add(x);
        }
    }
    sub[id[rt]].add(rt);
    ans[rt]=sub[id[rt]].mx_sum;
}
void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)cin>>c[i];
    for(int i=1;i<=n-1;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i)cout<<ans[i]<<" ";
    cout<<"\n";
}
int main(){
    std::ios::sync_with_stdio(false); 
    solve();
}
```

----

#### 14 int __ feenkuai

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int block(int st,int en,int num){//return for(int i=st;i<=en;++i)ans+=num/i;
    int L=0;
    int _res=0;
    en=min(en,num);
    for(int i=st;i<=en;i=L+1){
        L=min(en,num/(num/i));
        _res+=(L-i+1)*(num/i);
    }
    return _res;
}
int up(int l,int r){
    return (l-1)/r+1;
}
int work(int st,int en){
    int ans=max(0*1LL,en/2-st+1);
    for(int start=1,right;start<st;start=right+1){
        int l=start,r=st;
        int f=up(st,start);
        for(int i=1;i<=30;++i){
            int mid=(l+r)>>1;
            if(up(st,mid)==f)l=mid+1;
            else r=mid;
        }
        right=l-1;
        ans+=max(0LL,min(right,en/(f+1))-start+1);
    }
    return ans;
}
void solve(){
    int l,r;
    cin>>l>>r;
    cout<<work(l,r)<<"\n";
}
signed main(){
	std::ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while (t--)	
    solve();
}
```

---

#### 15  jiangly_v2.cpp (HLD)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    HLD(int n) : n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), seq(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
    int cur = 0;
    void dfs2(int u) {
        in[u] = ++cur;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = parent[top[u]];
            else v = parent[top[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};
int a[200000+50],ans[200000+50];
void slove(){
    int n,m,s;
    cin>>n>>m>>s;
    HLD tr(n*2+10);
    for(int i=1;i<=n-1;++i){
        int u,v;
        cin>>u>>v;
        tr.addEdge(u,v);
    }
    tr.init(s);
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        cout<<tr.lca(u,v)<<"\n";
    }
}
signed main(){
    ios::sync_with_stdio(false); 
    cout.tie(0);
    cin.tie(0);
    slove();
}
```

----

#### 16 kru.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int u,v,w;
    bool const operator<(const node &o)const{
        return w<o.w;
    }
};int n,m;
vector<node>e;
int fa[1000005*2],cnt;
int find(int f){
    if(f==fa[f])return f;
    return fa[f]=find(fa[f]);
}
void kru(){
    sort(e.begin(),e.end());
    cnt=n;
    int sum=n;
    int ans=0;
    for(auto j:e){
        auto u=j.u,v=j.v,w=j.w;
        u=find(u),v=find(v);
        if(u!=v){
            int fath=++cnt;
            fa[u]=fa[v]=fath;
            ans+=w;
            --sum;
        }
        if(sum==1)break;
    }
    if(sum>1)cout<<"orz\n";
    else 
    cout<<ans<<"\n";
}

void solve(){
    cin>>n>>m;
    for(int i=1;i<=n*2;++i)fa[i]=i;
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e.push_back({u,v,w});
    }
    kru();

}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}

```

----

#### 17  lca.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5 + 10;
int N, M, S;
int depth[maxn];
int fa[maxn][60];
int lg[maxn];
int mx[maxn][60];
vector<int>e[maxn];
void init(){
    lg[1] = 0,lg[2] = 1;
    for (int i = 3; i <= N; i++) lg[i] = lg[i / 2] + 1;
}
void dfs(int now, int fat){
    fa[now][0] = fat;
    depth[now] = depth[fat] + 1;
    for (int i = 1; i <= lg[depth[now]]; i++){
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
        mx[now][i]=max(mx[fa[now][i-1]][i-1],mx[now][i]);
    }
    for(auto j:e[now]){
        if(j==fat)continue;
        dfs(j,now);
    }
}
int lca(int x, int y){
    if (depth[x] < depth[y])swap(x, y);
    while (depth[x] > depth[y])x = fa[x][lg[depth[x] - depth[y]]];
    if (x == y)return x;
    for (int i = lg[depth[x]]; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
void solve(){
    
}
signed main(){
    std::ios::sync_with_stdio(false);
    solve();
}
```

#### 18 lct2.cpp

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200050;
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
    void link(int x, int y) {
        if (find(x) != find(y)) makeroot(x), fa[x] = y;
    }
    void split(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
    }
    void cut(int x, int y) {
        split(x, y);
        if (ch[y][0] == x && !ch[x][1])ch[y][0] = fa[x] = 0;
    }
    int que(int x, int y) {//询问 x ->y 路径上的值
        split(x, y);
        return siz[y];
    }
    void set(int x, int y) {
        splay(x);
        val[x] = y;
        pushup(x);
    }
} tree;
int n, m;
void slove() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> tree.val[i];
    int op, x, y;
    while (m--) {
        cin >> op >> x >> y;
        if (op == 0)cout << tree.que(x, y) << endl;
        else if (op == 1)tree.link(x, y);
        else if (op == 2)tree.cut(x, y);
        else tree.set(x, y);
    }
}
signed main(){
    std::ios::sync_with_stdio(false);cin.tie(0);
    solve();
}
```



#### 19 manacher

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char str[(12000000+50)<<1];
int d[(12000000+50)<<1];
void solve(){
    cin>>str+1;
    int ans=0;
    int n=strlen(str+1);
    str[0]='!';
    for(int i=n;i>=1;--i){
        str[i<<1]=str[i];
        str[i<<1|1]='#';
    }
    str[1]='#';
    n=n*2+1;
    int mid=0,r=0;
    for(int i=1;i<=n;++i){
        if(i<=r)  d[i]=min(r-i+1,d[mid*2-i]);
        while(str[i-d[i]]==str[i+d[i]])d[i]++;
        if(d[i]+i>r)r=d[i]+i-1,mid=i;
        ans=max(ans,d[i]);
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    solve();
}
```



#### 20  odt.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;  
#define int long long
struct node{
    int l, r;
    mutable int v; // 这里mutable要写不然可能会CE
    node(int l,int r, int v) : l(l), r(r), v(v) {} // 构造函数
    bool operator<(const node &o) const { return l < o.l; } // 重载小于运算符
};
set<node> tree;
auto split(int pos)// 若不支持C++14，auto须改为set<node>::iterator
{
    auto it = tree.lower_bound(node(pos, 0, 0)); // 寻找左端点大于等于pos的第一个节点
    // 若不支持C++11，auto须改为set<node>::iterator
    if (it != tree.end() && it->l == pos) return it;// 如果已经存在以pos为左端点的节点，直接返回
    it--; // 否则往前数一个节点
    int l = it->l, r = it->r, v = it->v;
    tree.erase(it); // 删除该节点
    tree.insert(node(l, pos - 1, v)); // 插入<l,pos-1,v>和<pos,r,v>
    return tree.insert(node(pos, r, v)).first; // 返回以pos开头的那个节点的迭代器
    // insert默认返回值是一个pair，第一个成员是我们要的
}
int sum;
/*void assign(int l, int r, int v){
    auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
    tree.erase(begin, end); // 清除一系列节点
    tree.insert(node(l, r, v)); // 插入新的节点
}*/
void assign(int l,int r,int v){
    int tot=0,len=0;
    auto end=split(r+1),it=split(l),begin=it;
    for(it;it!=end;++it){
        len+=(it->r-it->l+1);
        tot+=it->v*(it->r-it->l+1);
    }
    tree.erase(begin, end); // 清除一系列节点
    tree.insert(node(l, r, v)); // 插入新的节点
    if(v==1) sum+=(len-tot);
    else sum-=tot;
}
void solve(){
    int n,q;
    cin>>n>>q;
    tree.insert(node(1,n,1));
    sum=n;
    while(q--){
        int l,r,k;
        cin>>l>>r>>k;
        assign(l,r,k!=1);
        cout<<sum<<"\n";
    }

}
signed main(){
    std::ios::sync_with_stdio(false); cin.tie(0);
    solve();
}
```

----

#### 21 prisident_tree.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls(p) tree[p].l
#define rs(p) tree[p].r
#define sum(p) tree[p].sum
int a[200000+50];
struct node
{
    int sum=0;
    int l=0,r=0;
}tree[500050*30];
int tot=1,root[500000];
void update(int p,int l,int r,int k,int last,int now){
    if(l==r){
        sum(now)=sum(last)+k;
    }
    else{
        ls(now)=ls(last),rs(now)=rs(last);
        int mid=(l+r-1)/2;// -1?
        if(p<=mid)ls(now)=++tot,update(p,l,mid,k,ls(last),ls(now));
        else rs(now)=++tot,update(p,mid+1,r,k,rs(last),rs(now));
        sum(now)=sum(ls(now))+sum(rs(now));//pushup?
    }
}
int up=1e9+5,down=-(1e9+5);
int kth(int last,int now,int k,int l=down,int r=up){
    if(l==r)return l;
    int mid=(l+r-1)/2;
    int val=sum(ls(now))-sum(ls(last));
    if(val>=k)return kth(ls(last),ls(now),k,l,mid);
    else return kth(rs(last),rs(now),k-val,mid+1,r);
}
void solve(){//查询第K小
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i){
        root[i]=++tot;
        update(a[i],down,up,1,root[i-1],root[i]);
    }
    while(m--){
        int l,r,k;
        cin>>l>>r>>k;
        cout<<kth(root[l-1],root[r],k)<<"\n";
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    solve();
}
```

----

#### 22.  SA.cpp

```cpp
#include<bits/stdc++.h>
using namespace std;
// https://ac.nowcoder.com/acm/contest/34974/B?&headNav=acm
// 给定一个字符串 ，求本质不同的子串个数。
vector<int> rk, sa, cnt, height, oldrk, px, id;
void SA(string s){
    auto cmp=[&](auto x,auto y,auto w){
        return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    };
    int  n = s.length(), m = 300;
    rk.clear(), sa.clear(), cnt.clear(), height.clear(), oldrk.clear(), px.clear(), id.clear();
    oldrk.resize(max(m + 1, 2 * n + 1));
    sa.resize(max(m + 1, n + 1));
    rk.resize(max(m + 1, n + 1));
    cnt.resize(max(m + 1, n + 1));
    height.resize(max(m + 1, n + 1));
    px.resize(max(m + 1, n + 1));
    id.resize(max(m + 1, n + 1));
    s = " " + s;
    for (int i = 1; i <= n; ++i)++cnt[rk[i] = s[i]];
    for (int i = 1; i <= m; ++i)cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i)sa[cnt[rk[i]]--] = i;
    for (int w = 1, p;; w <<= 1, m = p){
        p = 0;
        for (int i = n; i > n - w; --i)id[++p] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > w) id[++p] = sa[i] - w;
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 1; i <= n; ++i)++cnt[px[i] = rk[id[i]]];
        for (int i = 1; i <= m; ++i)cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i)sa[cnt[px[i]]--] = id[i];
        copy(rk.begin(), rk.end(), oldrk.begin());
        p = 0;
        for (int i = 1; i <= n; ++i)  rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        if (p == n){
            for (int i = 1; i <= n; ++i)sa[rk[i]] = i;
            break;
        } 
    }
    for (int i = 1, k = 0; i <= n; ++i){
        if (rk[i] == 0)continue;
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        height[rk[i]] = k;
    }
}//LCP(i,j)=min(height[i+1 to j])
void slove() {
    string s; cin >> s;
    SA(s);
    long long ans = 0;
    int n = s.length();
    for (int i = 1; i <= n; i++) {         //height[i]  后缀排序后 i与i-1的公共前缀长度
        cout<<sa[i]<<"\n";
        ans += (n - sa[i] + 1 - height[i]);//sa[i] 表示 后缀排序后 rank_i的字符串的开头在原来字符串的位置
    }
    cout << ans <<"\n";
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    slove();
}
```

----

#### 23. scc

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6 + 5, maxm = 2e6 + 5, INF = 1e9 + 1;
struct SCC{
	int h[maxn], hn[maxn], e[maxm], ne[maxm], idx;
	int dfn[maxn], low[maxn], ts;
	int stk[maxn], top;
	int scc_cnt, id[maxn];
    int din[maxn];
	vector<int> scc[maxn];
	int n; 
	bool ins[maxn];
	void add(int h[], int a, int b){
	    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
	}
	void add(int a, int b){
		add(h, a, b);
	}
	void tarjan(int u){
	    dfn[u] = low[u] = ++ts;
	    stk[++top] = u;
	    ins[u] = 1;
	    for(int i = h[u]; ~i; i = ne[i]){
	        int j = e[i];
	        if (!dfn[j]){
	            tarjan(j);
	            low[u] = min(low[u], low[j]);
	        }
	        else if (ins[j]) low[u] = min(low[u], dfn[j]);
	    }
	    if (dfn[u] == low[u]){
	        ++scc_cnt;
	        int y;
	        do{
	            y = stk[top--];
	            id[y] = scc_cnt;
	            ins[y] = 0;
	            scc[scc_cnt].push_back(y);
	        }while(y != u);
	    }
	}
	void init(int _n){
        n = _n;
	    for(int i = 1; i <= n; i++){
	    	scc[i].clear();
	        dfn[i] = 0;
	        h[i] = hn[i] = -1;
            din[i] = 0;
	    }
	    scc_cnt = top = ts = idx = 0;
	}
	void build(){
		for(int i = 1; i <= n; i++)
			if (!dfn[i]) tarjan(i); 
	    for(int x = 1; x <= n; x++)
	        for(int i = h[x]; ~i; i = ne[i]){
	            int j = e[i];
	            if (id[j] != id[x]) din[id[j]]++;
	        }
	}
}scc;
struct node
{
    int u,v,w;
};
vector<node>edge;
void solve(){
    int n,m;
    cin>>n>>m;
    edge.clear();
    scc.init(n);  
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        edge.push_back({u,v,w});
    }
    auto check=[&](int mid){
        scc.init(n);
        for(auto &[u,v,w]:edge){
            scc.add(u,v);
            if(w<=mid)scc.add(v,u);
        }
        scc.build();
        int res=0;
        for(int i=1;i<=scc.scc_cnt;++i){
            res+=(scc.din[i]==0);
        }
        return res==1;
    };
    int l=0,r=1e9+7;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    if(r>=1e9+7){cout<<"-1\n";return;}
    cout<<l<<"\n";
}
signed main(){
    std::ios::sync_with_stdio(false); 
    int t;
    cin>>t;
    while(t--)
    solve();
}
```



----

#### 24. seg_tree

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int left_son(int x){return x<<1;}
int righ_son(int x){return x<<1|1;}
int fa[500000+50],si[500000+50];
vector<pair<int &,int>>hisfa;
vector<pair<int &,int>>hissi;
void init(int n){
    for(int i=1;i<=n;++i){
        fa[i]=i;
        si[i]=1;
    }
}
int find(int x){
    while(x!=fa[x])x=fa[x];
    return x;
}
int size(int x){return si[find(x)];}
void merge(int u,int v){
    int x=find(u),y=find(v);
    if(x==y)return ;
    if(si[x]<si[y])swap(x,y);
    hisfa.push_back({fa[y],fa[y]});
    fa[y]=x;
    hissi.push_back({si[x],si[x]});
    si[x]=si[x]+si[y];
}
bool cmp(int u,int v){
    return find(u)==find(v);
}
int history(){
    return hisfa.size();
}
void roll(int h){
    while(hisfa.size()>h){
        hisfa.back().first=hisfa.back().second;
        hisfa.pop_back();
        hissi.back().first=hissi.back().second;
        hissi.pop_back();
    }
}
vector<pair<int,int>>col[500000+80];
int n;
vector<int>seg[500000*4+5];
void add_seg(int p,int l,int r,int al,int ar,int e){
    if(al>r||ar<l)return ;
    if(ar>=r&&al<=l){
        seg[p].push_back(e);
        return ;
    }
    int mid=(l+r)>>1;
    add_seg(left_son(p),l,mid,al,ar,e);
    add_seg(righ_son(p),mid+1,r,al,ar,e);
}
void add_seg(int l,int r,int e){
    add_seg(1,1,n,l,r,e);
}
int ans=0;
void query(int p,int l,int r){
    int h=history();
    if(l==r){
        for(auto c:seg[p])
            for(auto j:col[c])
                merge(j.first,j.second);
        for(auto p:col[l]) ans+=size(p.first)*size(p.second);
        
    }
    else{
        for(auto c:seg[p])
            for(auto j:col[c])
                merge(j.first,j.second);
        int mid=(l+r)>>1;
        query(left_son(p),l,mid);
        query(righ_son(p),mid+1,r);
    }
    roll(h);
}
void solve(){
    cin>>n;
    for(int i=1;i<=n-1;++i){
        int u,v,w;
        cin>>u>>v>>w;
        col[w].push_back({u,v});
    }
    init(n);
    for(int i=1;i<=n;++i){
        if(i==1)add_seg(2,n,i);
        else if(i==n)add_seg(1,n-1,i);
        else{
            add_seg(1,i-1,i);
            add_seg(i+1,n,i);
        }   
    } 
    query(1,1,n);
    cout<<ans<<"\n";
}
signed main(){
    std::ios::sync_with_stdio(false);
    solve();
}

```

---

#### 25  线性基

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//第k大异或和
struct XXJ
{
    vector<int>B;
    int n;
    void insert(int x){
        for(auto j:B)  x=min(x,x^j);
        for(auto &j:B) j=min(j,j^x);
        if(x)B.push_back(x);
    }
    void sort_B(){sort(B.begin(),B.end());}
    int max_xor(){
        int ans=0;
        for(auto j:B)ans^=j;
        return ans;
    }
    bool find_x(int x){
        for(auto j:B)x=min(x,x^j);
        return x==0;
    }
    int find_rank_min_K(int k){//先 sort_B;
        int ans=0;
        if(B.size()<n)k--;
        for(auto j:B){
            if(k&1)ans^=j;
            k>>1;
        }
        if(k==0)return ans;
        else return -1;
    }
    // 如果要看有多少种方法可以异或出X，先看能不能用 线性基表示出X，如果能，答案就是2^(n-|S|) ==  1<<(n-B.size())
};

void slove(){
}
signed main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--) 
    slove();
}
```

----

#### 26 虚树

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
//https://www.luogu.com.cn/problem/P2495
struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq,mi;
    vector<vector<pair<int,int>>> adj;
    HLD(int n) :n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), seq(n), adj(n),mi(n,1e18){}
    void addEdge(int u, int v,int w) {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    void init(int root = 0) {
        top[root] = root;
        dfs1(root,-1);
        dfs2(root,-1);
    }
    void dfs1(int u,int f) {
        siz[u] = 1;
        for (auto &v : adj[u]) {
            if(v.first==f)continue;
            parent[v.first] = u;
            dep[v.first] = dep[u] + 1;
            mi[v.first]=min(mi[u],v.second);
            dfs1(v.first,u);
            siz[u] += siz[v.first];
            if (siz[v.first] > siz[adj[u][0].first]) {
                swap(v, adj[u][0]);
            }
        }
    }
    int cur = 0;
    void dfs2(int u,int f) {
        in[u] = ++cur;
        seq[in[u]] = u;
        for (auto j : adj[u]) {
            if(j.first==f)continue;
            int v=j.first;
            top[v] = v == adj[u][0].first ? top[u] : v;
            dfs2(v,u);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
};
vector<pair<int,int>>vg[600000];
void bulid(vector<int>&node,HLD& g){
    auto cmp=[&](int u,int v){
        return g.in[u]<g.in[v];
    };
    auto isp=[&](int u,int v){//判断子树
        return g.in[u] <= g.in[v] && g.out[v] <= g.out[u];
    };
    sort(node.begin(),node.end(),cmp);unordered_set<int>s;
    for(auto j:node)s.insert(j);
    for(int i=1;i<node.size();++i)s.insert(g.lca(node[i-1],node[i]));
    node.clear();for(auto j:s)node.push_back(j);
    sort(node.begin(),node.end(),cmp);
    vector<int>st;
    for(auto v:node){
        while(!st.empty()&&!isp(st.back(),v))st.pop_back();
        if(!st.empty())vg[st.back()].push_back({v,g.mi[v]});
        st.push_back(v);
    }
}
int dp[600000],vis[600000];
void dfs(int u,int f){
    dp[u]=0;
    for(auto j:vg[u]){
        if(j.first==f)continue;
        int v=j.first,w=j.second;
        dfs(v,u);
        if(vis[v])dp[u]+=w;
        else dp[u]+=min(w,dp[v]);
    }
}
void solve(){
    int n;
    cin>>n;
    HLD g(n+5);
    for(int i=1;i<=n-1;++i){
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    g.init(1);
    int m;
    cin>>m;
    while(m--){
        int k;
        cin>>k;
        vector<int>node;
        for(int i=1;i<=k;++i){
            int x;
            cin>>x;
            node.push_back(x);
            vis[x]=1;
        }
        node.push_back(1);
        bulid(node,g);
        dfs(1,-1);
        cout<<dp[1]<<"\n";
        for(int x:node)vis[x]=0,vg[x].clear();
    }
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
```

#### 27 FHQ

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define num(x) tree[x].num
#define val(x) tree[x].val
#define sz(x) tree[x].sz
#define exist(x) !(num(x) == 0 && ls(x) == 0 && rs(x) == 0)
struct ubst{    
    const double ALPHA = 0.7;
    struct Node{
        int ls, rs, num, val, sz;
    }; // 改用结构体进行存储
    vector<int> FP, FN, FV;
    vector<Node> tree; // 存储拉平后的节点编号、数目、值
    int cnt = 1;
    ubst(int n):tree(1500005){}
    int flatten(int pos) {// 一趟中序遍历，把当前子树拉平并存到vector里，返回当前节点的索引
        if (exist(ls(pos))) flatten(ls(pos));// 递归地拉平左子树
        int id = FP.size(); // 记下当前节点的索引
        if (num(pos) != 0) {// 如果该节点是已被删除的节点，就略过，否则把相应信息存入vector
            FP.push_back(pos);
            FV.push_back(val(pos));
            FN.push_back(num(pos));
        }
        if (exist(rs(pos))) flatten(rs(pos));// 递归地拉平右子树
        return id;
    }
    void rebuild(int pos, int l, int r ){// 以pos为根节点，以[l,r]内的信息重建一棵平衡的树
        int mid = (l + r)>>1, sz1 = 0, sz2 = 0;
        if (l < mid){
            ls(pos) = FP[(l + mid - 1) / 2]; // 重用节点编号
            rebuild(ls(pos), l, mid - 1); // 递归地重建
            sz1 = sz(ls(pos));
        }
        else ls(pos) = 0;
        if (mid < r){
            rs(pos) = FP[(mid + 1 + r) / 2];
            rebuild(rs(pos), mid + 1, r);
            sz2 = sz(rs(pos));
        }
        else rs(pos) = 0;
        num(pos) = FN[mid]; // 把存于vector中的信息复制过来
        val(pos) = FV[mid];
        sz(pos) = sz1 + sz2 + num(pos); // 递归确定重建后树的大小
    }
    void try_restructure(int pos) {// 尝试重构当前子树
        double k = max(sz(ls(pos)), sz(rs(pos))) / double(sz(pos));
        if (k > ALPHA){
            FP.clear(), FV.clear(), FN.clear(); // 清空vector
            int id = flatten(pos);
            swap(FP[id], FP[(FP.size() - 1) / 2]); // 这里是确保当前节点的编号在重构后不会改变，因为它可能
            rebuild(pos,0,FP.size()-1);
        }
    }
    // 接下来是普通的二叉查找树
    void insert(int v, int pos = 1){
        if (!exist(pos)){
            val(pos) = v;
            num(pos) = 1;
        }
        else if (v < val(pos)){
            if (!exist(ls(pos)))ls(pos) = ++cnt;
            insert(v, ls(pos));
        }
        else if (v > val(pos)){
            if (!exist(rs(pos)))rs(pos) = ++cnt;
            insert(v, rs(pos));
        }
        else  num(pos)++;
        sz(pos)++;
        try_restructure(pos);
    }
    void remove(int v, int pos = 1){
        sz(pos)--;
        if (v < val(pos)) remove(v, ls(pos));
        else if (v > val(pos))  remove(v, rs(pos));
        else num(pos)--;
        try_restructure(pos);
    }
    int countl(int v, int pos = 1){
        if (v < val(pos))  return exist(ls(pos)) ? countl(v, ls(pos)) : 0;
        else if (v > val(pos)) return sz(ls(pos)) + num(pos) + (exist(rs(pos)) ? countl(v, rs(pos)) : 0);
        else  return sz(ls(pos));
    }
    int countg(int v, int pos = 1){
        if (v > val(pos))  return exist(rs(pos)) ? countg(v, rs(pos)) : 0;
        else if (v < val(pos))  return sz(rs(pos)) + num(pos) + (exist(ls(pos)) ? countg(v, ls(pos)) : 0);
        else  return sz(rs(pos));
    }
    int rank(int v){return countl(v) + 1;}
    int kth(int k, int pos = 1){
        if (sz(ls(pos)) + 1 > k)   return kth(k, ls(pos));
        else if (sz(ls(pos)) + num(pos) < k)  return kth(k - sz(ls(pos)) - num(pos), rs(pos));
        else return val(pos);
    }
    int pre(int v){
        int r = countl(v);
        return kth(r);
    }
    int suc(int v){
        int r = sz(1) - countg(v) + 1;
        return kth(r);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    ubst ut(n);
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        ut.insert(x,1);
    }
    int ans=0,last=0;
    while(m--){
        int op,x;
        cin>>op>>x;
        x^=last;
        //cout<<op<<"    "<<x<<"\n";
        if(op==1)ut.insert(x);
        else if(op==2)ut.remove(x);
        else if(op==3)last=ut.rank(x);
        else if(op==4)last=ut.kth(x);
        else if(op==5)last=ut.pre(x);
        else last=ut.suc(x);
        if(op>=3)ans^=last;
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    solve();
}
```

#### 28 mex

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
const int M = 1e6 + 5;
struct node {
    int mi = 0;
    int l = 0, r = 0;
}tr[M * 30];
#define ls(x) (tr[x].l)
#define rs(x) (tr[x].r)
#define mi(x) tr[x].mi
int tot = 1;
int root[N], a[N], n, m;
void pushup(int x) { mi(x) = min(mi(ls(x)), mi(rs(x)));}
void upd(int last, int now, int pos, int k, int l, int r) {
    //过去的节点 现在的节点 修改的位置，k ，当前节点表示的区间[l,r]
    if (l == r) {
        mi(now) = k;
    }
    else {
        ls(now) = ls(last), rs(now) = rs(last);
        int mid = (l + r - 1) / 2;
        if (pos <= mid)
            ls(now) = ++tot, upd(ls(last), ls(now), pos, k, l, mid);
        else
            rs(now) = ++tot, upd(rs(last), rs(now), pos, k, mid + 1, r);
        pushup(now);
    }
}
void upd(int last, int now, int pos, int k) {
    upd(last, now, pos, k, 0, n);
}
int que(int x, int L, int l, int r) {
    if (l == r)return l;
    int mid = (l + r - 1) / 2;
    if (mi(ls(x)) < L)return que(ls(x), L, l, mid);
    else return que(rs(x), L, mid + 1, r);
}
void slove() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        root[i] = ++tot;
        upd(root[i - 1], root[i], a[i], i);;
    }
    while (m--) {
        int L, R; cin >> L >> R;
        cout << que(root[R], L, 0, n) << endl;
    }
}signed main(){
    std::ios::sync_with_stdio(false);
    slove();
}
```



####  29 moban_O(nm)

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

#### 30 scan

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define ls(p) p<<1
#define rs(p) p<<1|1
int cover[200000*4+50];
double length[200000+50],yy[200000*4+50];
struct scan{
    double x,upy,downy;
    int in_out;
    scan(){};
    scan(double x,double y1,double y2,int in):x(x),upy(y1),downy(y2),in_out(in){};
    const bool operator<(const scan& o)const{return x<o.x;}
}line[200000+50];
void pushup(int p,int l,int r){
    if(cover[p])length[p]=yy[r]-yy[l];
    else if(l+1==r)length[p]=0;
    else length[p]=length[ls(p)]+length[rs(p)];
}
void updata(int p,int l,int r,int yl,int yr,int io){
    if(yl>r||yr<l)return;
    if(yl<=l&&r<=yr){
        cover[p]+=io;
        pushup(p,l,r);
        return;
    }
    if(l+1==r)return;
    int mid=(l+r)>>1;
    updata(ls(p),l,mid,yl,yr,io),updata(rs(p),mid,r,yl,yr,io);
    pushup(p,l,r);
}
void slove() {
    int n;
    cin>>n;
    int cnt=0;
    double x1,x2,y1,y2;
    int yl,yr,io;
    for(int i=1;i<=n;++i){
        cin>>x1>>y1>>x2>>y2;
        line[++cnt]=scan(x1,y2,y1,1);
        yy[cnt]=y1;
        line[++cnt]=scan(x2,y2,y1,-1);
        yy[cnt]=y2;
    }
    sort(yy+1,yy+1+cnt);
    sort(line+1,line+1+cnt);
    int len=unique(yy+1,yy+1+cnt)-yy-1;
    memset(cover,0,sizeof cover);memset(length,0,sizeof length);
    double ans=0;
    for(int i=1;i<=cnt;++i){
        ans+=length[1]*(line[i].x-line[i-1].x);
        yl=lower_bound(yy+1,yy+1+len,line[i].downy)-yy;
        yr=lower_bound(yy+1,yy+1+len,line[i].upy)-yy;
        io=line[i].in_out;
        updata(1,1,len,yl,yr,io);
    }
    cout<<ans<<"\n";    
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    slove();
}
```
####  31 手写unodered_map
```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
#define hash_t gp_hash_table<int,int, chash>
```



