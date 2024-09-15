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