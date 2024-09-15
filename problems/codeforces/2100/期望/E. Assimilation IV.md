# E. Assimilation IV

Monocarp 正在玩游戏 "同化 IV"。在这款游戏中，他管理着一个伟大的帝国：建造城市，征服新的土地。

Monocarp 的帝国拥有 $n$座城市。为了征服新的土地，他计划在每个城市建造1座纪念碑。游戏采用回合制，由于莫诺卡普还是业余选手，所以他每回合正好建造一座纪念碑。

莫诺卡普在地图上有$m$个点，他想用建造的纪念碑来控制这些点。他知道每个点与每个城市之间的距离。纪念碑的作用如下：当纪念碑建在某个城市时，它可以控制与该城市距离最多为 $1$的所有点。下一回合，纪念碑控制距离为 $2$的所有点，再下一回合--控制距离为 $3$的所有点，以此类推。Monocarp 将建造 $n$的帝国将征服至少有一座纪念碑控制的所有点。

Monocarp 无法想出任何策略，因此在每个回合中，他会在所有剩余的城市（没有纪念碑的城市）中随机选择一个城市作为纪念碑。莫诺卡普想知道在第 $n$回合结束时，他将征服多少个点（在其中的 $m$个点中）。请帮他计算预计征服的点数！

[Problem - E - Codeforces](https://codeforces.com/contest/1525/problem/E)

参考：[CF1525E Assimilation IV - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/solution/CF1525E)

### solve

1. 求期望的计算体系之正向的求：

   从方案再到具体的点；（从方案到具体的细节，显然不好做）如果先从方案入手，分类方案到点的体统计，总要考虑诸多的容斥。

2. 关注一个点，看这个点，贡献了多少次方案： 这个角度下，就不需要考虑容斥问题：

   1. 如果考虑使得这个点被攻陷的方案数，比较麻烦，可以再逆向的思维，考虑其补集：
      1. 补集中任何一个排列的第i个数字离当前点的距离大于 n + 1 - i

### code

```CPP
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 22;
const int M = 50100;

const int mod = 998244353;

/*统计第i个点中距离该点距离为i点：*/
int c[M][N];

int qpow(int x, int n)
{
	int res = 1; //用来返回结果。
	while (n > 0)
	{
		if (n & 1)res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		n >>= 1;
	}
	return res;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n , m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int d; cin >> d;
			c[j][d]++;
		}
	}
	int fac = 1;
	for (int i = 1; i <= n; i++)
		fac = 1LL * fac * i % mod;
	int res = 0;
	for (int i = 1; i <= m; i++) {
		// 当前符合条件的点的个数有多少个：
		// 当前阶乘的前缀的答案是多少；
		// 然后由乘法原理计算出补集的大小：
		int ans = 1 ,  sum = 0;
		// 反过来才可以用乘法原理完成计算：
		for (int j = n; j >= 1; j--) {
			sum += c[i][j + 1];
			ans = 1LL * ans * sum % mod;
			// 已经用了一个：
			sum--;
		}
		res = (res + 1 - 1LL * ans * qpow(fac , mod - 2) % mod + mod) % mod;
	}
	cout << res << "\n";
}
```













