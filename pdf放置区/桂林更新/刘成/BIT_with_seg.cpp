#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct segtr{
    static const int maxp=maxn*200;
    int ls[maxp],rs[maxp],sum[maxp],pcnt;
    vector<int>ok;
    void addnode(int &p){
        if(ok.empty()){p=++pcnt;return ;}
        p=ok.back();ok.pop_back();
    }
    void del(int &p){ok.push_back(p);p=0;}
    void init(){
        ok.clear();
        memset(ls,0,sizeof(ls));
        memset(rs,0,sizeof(rs));
        memset(sum,0,sizeof(sum));
        pcnt=0;
    }
    void pushup(int p){sum[p]=sum[ls[p]]+sum[rs[p]];}
    void updata(int &u,int l,int r,int q,int k){
        if(!u)addnode(u);
        sum[u]+=k;
        if(l<r){
            int mid=(l+r)>>1;
            if(q<=mid)updata(ls[u],l,mid,q,k);
            else updata(rs[u],mid+1,r,q,k);
        }
        if(!sum[u])del(u);
    }
    int query(int p,int l,int r,int ql,int qr){
        if(!p)return 0;
        if(ql<=l&&r<=qr)return sum[p];
        int mid=(l+r)>>1;
        int res=0;
        if(ql<=mid)res+=query(ls[p],l,mid,ql,qr);
        if(mid<qr)res+=query(rs[p],mid+1,r,ql,qr);
        return res;
    }
};
struct BIT{
    int n;
    segtr seg;
    int rt[maxn];
    int lowbit (int p){return p&-p;}
    void init(int n=0){this->n=n;seg.init();}
    void updata(int p,int q,int k){
        for(;p<=n;p+=lowbit(p))seg.updata(rt[p],1,n,q,k);
    }
    int query(int p,int ql,int qr){
        int res=0;
        for(;p;p-=lowbit(p))res+=seg.query(rt[p],1,n,ql,qr);
        return res;
    }
    int query(int l,int r,int ql,int qr){return query(r,ql,qr)-query(l-1,ql,qr);}
}bit;
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int>a(n+1),b(n+1),pos(n+1),c(n+1);
    for(int i=1;i<=n;++i)cin>>a[i],pos[a[i]]=i;
    for(int i=1;i<=n;++i)cin>>b[i],b[i]=pos[b[i]];
    bit.init(n);
    for(int i=1;i<=n;++i)bit.updata(i,b[i],1);
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            int l,r;
            cin>>l>>r;
            cout<<bit.query(l,r,x,y)<<"\n";
        }else{
            bit.updata(x,b[x],-1);
            bit.updata(y,b[y],-1);
            swap(b[x],b[y]);
            bit.updata(x,b[x],1);
            bit.updata(y,b[y],1);
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie (0);
    solve();
}
