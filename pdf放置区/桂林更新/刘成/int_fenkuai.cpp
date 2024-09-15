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