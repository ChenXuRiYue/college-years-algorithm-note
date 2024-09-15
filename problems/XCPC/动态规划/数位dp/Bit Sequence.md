# 2020 ICPC 济南站 L：Bit Sequence

参考https://blog.csdn.net/qq1838641320/article/details/112061559

https://ac.nowcoder.com/acm/contest/10662/L

1. 数组$a_{0 ...m -1}$
2. 运算函数$f_{x}$ , x的二进制串上1的个数。
question: 统计中 , 对于任意的 0 <= i < m , 都满足 $f(x + i) = a_i$的数字的个数.

## solve

1. 发现m的范围非常的小。分析m的影响：
   1. 比较$f(x+i)和f(x)$，不考虑进位 ， i最多影响7位。(100 = 1100100)。
   2. 考虑进位，最多进一位。7位之后的连续1反转。并且在第一个0出加一个1.
2. 综上在枚举前缀时，只需要关注结构的几个特征如下：
   1. 第6位之后连续1的奇偶性。
   2. 最后7的状态：
   3. 整体上1比特的个数的奇偶性质



**状态设计：**

$f_{i, 0/2 ,0/2}$ 表示 当前高60到第i位比特下，前面1位总数位奇/偶数。当前是否贴着上界，合法的数字总数。

**状态转移：**

1. 60 --- 8位置： 枚举之后往下记忆化搜索。
2. 7....0的位置，继续枚举往下搜索。
3. 枚举到最后就check答案。
   1. 如果当前线程的数位为60 -- 8注意使用记忆数组。
   2. 否则，只做每种方案下返回合法总数的贡献。



### my code (奇慢200ms)

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 110;

ll l;
int a[N] , m;
ll f[61][2][2][2];

vector<int> Bit;
//检查后5位置的奇偶性
int check(int x /*当前后7位的情况。*/, int pre /*前高位连续0*/, int sum/*高位0的总数奇偶性*/) {
	int flag = 1;
	for (int i = 0; i < m; i++) {
		int j = x + i;
		if (j < (1 << 7)) {
			flag &= (sum ^ (__builtin_parity(j))) == a[i];
		} else {
			flag &= ((sum ^ pre) ^ (__builtin_parity(j))) == a[i];
		}
	}
	// if (flag == 1)
	// 	cout << x << " "  << pre  << " " << sum  << "\n";
	return flag;
}

/*
3
3 10
0 1 0
1 1000
0
9 1000000
1 0 1 1 0 1 0 0 1
*/

/*
1
3 10
0 1 0
*/

ll dfs(int cur /*第几位*/, int sum ,  int odd /*前面位置的奇偶性*/, int limit /*是否贴着上界*/, int chose/*后7位的选择情况。*/) {
	if (cur > 6 && f[cur][sum][odd][limit] != -1) {
		return f[cur][sum][odd][limit];
	}
	if (cur == -1) return check(chose , odd , sum);
	int mx = limit ? Bit[cur] : 1;
	ll& res = f[cur][sum][odd][limit];
	res = 0;
	for (int i = 0; i <= mx; i++) {
		int sum_ = sum, odd_ = odd, chose_ = chose * 2;
		if (i == 1) {
			if (cur < 7) {
				chose_++;
			} else {
				odd_ ^= 1;
				sum_ ^= 1;
			}
		} else {
			if (cur  > 6) {
				odd_ = 0;
			}
		}
		res += dfs(cur - 1 , sum_ , odd_ , limit && (i == mx) , chose_);
	}
	return res;
}

void solve() {
	memset(f , 0xff , sizeof f);
	Bit.clear();
	cin >> m >> l;
	for (int i = 0; i < m; i++)
		cin >> a[i];
	for (int i = 0; i <= 60; i++) {
		Bit.push_back(l % 2);
		l /= 2;
	}
	cout << dfs(60 , 0 , 0 , 1 , 0) << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--)solve();
}
```



### 借鉴code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define mem(a,b) memset(a,b,sizeof(a))
using ll=long long;
using namespace std;
ll dp[64][2][2][2]={},x;
int bi[64]={},am[109]={},m;
ll calc(int lim,int s,int t){
	int res=0,hi=lim?x%128:127;
	for(int i=0;i<=hi;i++){//枚举低6位
		int f=1;
		for(int j=0;j<m&&f;j++)//O(m)逐一检查,注意到模2意义下加减都相当于异或
			if(i+j<128) f&=(__builtin_parity(i+j)^s)==am[j];
			else f&=(__builtin_parity(i+j)^s^t)==am[j];
		res+=f;
	}
	return res;
}
ll dfs(int pos,int lim,int s,int t){
	ll&res=dp[pos][lim][s][t];
	if(res!=-1) return res;
	if(pos<=6) return res=calc(lim,s,t);
	res=0;
	int up=lim?bi[pos]:1;
	for(int i=0;i<=up;i++) //注意到模2意义下加减都相当于异或
		res+=dfs(pos-1,lim&&i==up,s^i,i&(!t));
	return res;
}
ll solve(){
	mem(dp,-1);
	int len=0;
	for(ll xi=x;xi;xi>>=1) bi[len++]=xi&1;
	return dfs(len-1,1,0,0);
}
int main() {
	int ___;
	for(scanf("%d",&___);___--;){
		scanf("%d%lld",&m,&x);
		rep(i,0,m) scanf("%d",&am[i]);
		printf("%lld\n",solve());
	}
}
```



