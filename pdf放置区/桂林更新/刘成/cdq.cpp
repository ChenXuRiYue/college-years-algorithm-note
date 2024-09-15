#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct BIT{
    vector<int>tr;
    int n;
    BIT(int n):n(n),tr(n+12){};
    int lowbit (int p){return p&-p;}
    void updata(int p,int x){
        for(;p<=n;p+=lowbit(p))tr[p]+=x;
    }
    int query(int p){
        int res=0;
        for(;p;p-=lowbit(p))res+=tr[p];
        return res;
    }
    int query(int l,int r){return query(r)-query(l-1);}
    void clear(){for(auto &x:tr)x=0;}
};
struct CDQ{
    struct event{
        int l,r,y,val,id;
        event(int l=0,int r=0,int y=0,int val=0,int id=0):l(l),r(r),y(y),val(val),id(id){}
        const bool isupdata(){return id<0;}
        const bool isquery(){return id>=0;}
        bool const operator<(const event& o)const{return y<o.y;}
    };
    vector<event>events,buffer;
    vector<int>res;
    int n;BIT bit;
    CDQ(int n):n(n),bit(n){init();}
    int mx,mxid;
    void init(){mx=mxid=0;}// BIT clear()???
    void addupdata(int x,int y,int val){
        events.push_back({x,x,y,val,-1});
        mx=max(mx,x);
    }
    void addquery(int l,int r,int y,int val,int id){
        events.push_back({l,r,y,val,id});
        mx=max(mx,r);
        mxid=max(mxid,id);
    }
    void solve(int l,int r){
        if(r-l+1<=100){
            for(int i=l;i<=r;++i)if(events[i].isquery()){
                auto now=events[i];
                for(int j=l;j<i;++j)if(events[j].isupdata()){
                    if(events[j].y<=now.y&&now.l<=events[j].l&&events[j].l<=now.r)
                        res[now.id]+=now.val*events[j].val;
                }
            }
            sort(events.begin()+l,events.begin()+r+1);
            return ;
        }
        int mid=(l+r)>>1;
        solve(l,mid),solve(mid+1,r);
        int cur=l;
        for(int i=l,j=mid+1;i<=mid||j<=r;){
            if(j>r||(i<=mid&&events[i].y<=events[j].y)){
                if(events[i].isupdata())bit.updata(events[i].l,events[i].val);
                buffer[cur++]=events[i++];
            }else{
                if(events[j].isquery())res[events[j].id]+=events[j].val*bit.query(events[j].l,events[j].r);
                buffer[cur++]=events[j++];
            }
        }
        if(mid-l+1>(bit.n>>9))bit.clear();
        else for(int i=l;i<=mid;++i)if(events[i].isupdata())bit.updata(events[i].l,-events[i].val);
        for(int i=l;i<=r;++i)events[i]=buffer[i];
    }
    void solve(){
        res.assign(mxid+50,0);
        bit.n=mx;bit.tr.assign(mx+50,0);
        buffer.resize(events.size()+50);
        solve(0,events.size()-1);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    CDQ cdq(n);
    vector<int>a(n+1),b(n+1),pos(n+1);
    for(int i=1;i<=n;++i)cin>>a[i],pos[a[i]]=i;
    for(int i=1;i<=n;++i)cin>>b[i],b[i]=pos[b[i]],cdq.addupdata(i,b[i],1);
    int cnt=0;
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            int l,r;
            cin>>l>>r;
            cdq.addquery(l,r,y,1,cnt);
            cdq.addquery(l,r,x-1,-1,cnt);
            ++cnt;
        }else{
            cdq.addupdata(x,b[x],-1);
            cdq.addupdata(y,b[y],-1);
            swap(b[x],b[y]);
            cdq.addupdata(x,b[x],1);
            cdq.addupdata(y,b[y],1);
        }
    }
    cdq.solve();
    for(int i=0;i<cnt;++i)cout<<cdq.res[i]<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);cin.tie (0);
    solve();
}
