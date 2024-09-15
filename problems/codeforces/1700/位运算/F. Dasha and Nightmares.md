**F. Dasha and Nightmares**

https://codeforces.com/contest/1800/problem/F
#### 简介

1. 给定若干个字符串
2. 找出若干对字符串满足：

#### solve

管理字符串的方法： 

1. 压位，表示当前字符串中的各种字符出现了多少次。
   1. 如果简单的压位记录。会丢弃掉某个字母是否存在的信息。、

计算答案：

##### solve1

1. 枚举一个字母 ， 表示在拼接串中该字母不存在。
2. 然后扫一遍。
   1. 但是初始化f的花费将会非常的大。
   2. 算法复杂度会达到$\sum |s| + 2^26*26$



##### solve2

1. 在扫描的过程中。开一个巨大的map 或者 unorder_map
2. 直接记录 ， 统计即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n ;
	cin >> n;
	ll ans = 0;
	int mask = (1 << 26) - 1;
	unordered_map <int, int > rec[26];
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		int ch = 0 , bit = 0;
		for (auto c : s) {
			ch |= 1 << (c - 'a');
			bit ^= 1 << (c - 'a');
		}
		for (int i = 0; i < 26; i++) {
			if (!(ch & (1 << i) )) {
				ans += rec[i][bit ^ mask ^ (1 << i)];
				rec[i][bit]++;
			}
		}
	}
	cout << ans << '\n';
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```





##### solve3

认识到抽象出来的26位是比字符串数量更大的。考虑在1的基础上做出改进。

1. 初始化数组的时候，只要枚举所有字符串的种类即可。贡献是$O(n)*26$
2. 统计上的复杂度是$O(n)$
3. 预处理字符串的花费是$O(\sum |s|)$

```cpp
//这回只花了114514min就打完了。
//真好。记得多手造几组。ACM拍什么拍。 
#include "bits/stdc++.h"
using namespace std;
template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD>> &a) { for (auto &x:a) cout<<x<<'\n'; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }
template<typename typC,typename typD> bool cmin(typC &x,const typD &y) { if (x>y) { x=y; return 1; } return 0; }
template<typename typC,typename typD> bool cmax(typC &x,const typD &y) { if (x<y) { x=y; return 1; } return 0; }
template<typename typC> vector<typC> range(typC l,typC r,typC step=1) { assert(step>0); int n=(r-l+step-1)/step,i; vector<typC> res(n); for (i=0; i<n; i++) res[i]=l+step*i; return res; }
#if !defined(ONLINE_JUDGE)&&defined(LOCAL)
#include "my_header\debug.h"
#else
#define dbg(...) ;
#define dbgn(...) ;
#endif
typedef unsigned int ui;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
// template<typename T1,typename T2> void inc(T1 &x,const T2 &y) { if ((x+=y)>=p) x-=p; }
// template<typename T1,typename T2> void dec(T1 &x,const T2 &y) { if ((x+=p-y)>=p) x-=p; }
const int N=1<<26;
int cnt[N];
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cout<<fixed<<setprecision(15);
	int n,i,j,k;
	cin>>n;
	vector<int> a(n),b(n);
	for (i=0; i<n; i++)
	{
		string s;
		cin>>s;
		for (auto c:s) a[i]|=1<<c-'a',b[i]^=1<<c-'a';
	}
	ll r=0;
	for (k=0; k<26; k++)
	{
		int B=(1<<26)-1^(1<<k);
		for (i=0; i<n; i++) if (1^a[i]>>k&1)
		{
			++cnt[b[i]];
			r+=cnt[b[i]^B];
		}
		for (i=0; i<n; i++) if (1^a[i]>>k&1) --cnt[b[i]];
	}
	// for (i=0; i<n; i++) for (j=i; j<n; j++) if (__builtin_popcount(a[i]|a[j])==25&&__builtin_popcount(b[i]^b[j])==25) ++r;
	cout<<r<<endl;
}

```



