#include<bits/stdc++.h>
using namespace std;
#define int long long
int sq,n;
struct node{
    int l,r,id;
    bool operator<(const node &o)const
    {
        if(l/sq!=o.l/sq)return l<o.l;
        if(l/sq&1)return r<o.r;
        return r>o.r;
    }
}qt[205000];
int a[205000];
//int mu[200000+50];
map<int,int>mu;
int res=0;
int c3(int x){
    return (x*(x-1)*(x-2))/6;
}
void add(int p){
    res-=c3(mu[p]);
    mu[p]++;
    res+=c3(mu[p]);
}
void del(int p){
    res-=c3(mu[p]);
    mu[p]--;
    res+=c3(mu[p]);
    
}
int q;
int ans[205000];
void solve(){
    int l=1,r=0;
    for(int i=1;i<=q;++i){
        while (l > qt[i].l)add(a[--l]);
        while (l < qt[i].l)del(a[l++]);
        while (r < qt[i].r)add(a[++r]);
        while (r > qt[i].r)del(a[r--]);
        ans[qt[i].id]=res;
    }
}
signed main(){
     std::ios::sync_with_stdio(false);
     cin.tie(0);cout.tie(0);
     cin>>n;cin>>q;
     sq=sqrt(n);
     for(int i=1;i<=n;++i)cin>>a[i];
     for(int i=1;i<=q;++i){
        cin>>qt[i].l>>qt[i].r;
        qt[i].id=i;
     }
     sort(qt+1,qt+q+1);
     solve();
     for(int i=1;i<=q;++i){
        cout<<ans[i]<<"\n";
     }
}