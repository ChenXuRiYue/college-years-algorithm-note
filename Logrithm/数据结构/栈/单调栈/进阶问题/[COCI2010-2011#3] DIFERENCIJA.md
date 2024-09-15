https://www.luogu.com.cn/problem/P6503

#### introduce

一道dp思想，单调栈优化的问题。

单调栈在这里的优化是，快速的计算出dp转移中要使用的关键的量。可能所有的dp优化都是从这一个角度做起的。

#### 思路设计，思路历程

其一：首先设计状态。

我们总是尝试把区间扫一遍，在此之间，我们总是可以关注什么子问题呢？

我们关注以 i为左边界的区间。然后考虑这一些区间的总贡献。

对答案的贡献为$\sum f(i)-g(i)$。设计$f_i$为所有区间的最大值之和。$g_i$为所有的最小值之和。

于是我们发现 $f_i=f_{p_i}+(i-p_i)*a_i$其中$p_i$为大于$a_i$的第一个位置。

这个我们可以利用单调栈来快速找出。

同理我们可以设计$g_i$的计算方法。



面对解是一堆区间的。所有区间的计算。我们考虑区间与区间的关系。

总是由于它们的交集，包含关系导致了状态的迁移。

其中区间结构的关注角度为最值。可以分类出一些区间共享最大值。

总而言之，这是一道去感受区间结构以及单调栈优化的非常好的问题。



#### 生长思考：

- 数组，区间资源上dp的一种非常经典，天然的设计角度。

- 单调栈总结

  - 从哪个方向构造意味着维护的第一个最值在哪个方向

  - 递减栈维护最大值。递增栈维护最小值。

    - 某一个状态下的相邻的两个栈元素。如果是递减栈，那么就在原数组中夹在这两个元素之间的是，小于或等于个元素同时满足的项。
    - 如果是递增栈，省略的就是大于等于两个元素的项。

  - 很多时候，当我们维护一个单调栈时候，不妨去问，我为什么要关注第一个大于或者小它的元素？

     [[COCI2010-2011#3] DIFERENCIJA.md]([COCI2010-2011#3] DIFERENCIJA.md) 这里我们不断维护的过程中，我们关注前面是否有等于当前$b_i$长度的剪刀，其实就是一种维护第一个大于等于它的结果。看是否为当前$b_i$的大小如果是就可以节省一把剪刀。

    寻找连续矩阵中的最大值问题中：我们建立一个一个以当前$a_i$为高度的矩形。然后从左从右找第一个比它矮的。显然这样成立了。正方形为什么不更低一点？更低就可以转化成其它点上高度的问题。我们枚举的最优正方形都应该贴着一个矩形块上走。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;
typedef pair<int, int> iip;

int Max[N], top1, Min[N], top2;
ll a[N];

ll f[N], g[N];


ll ans = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for ( int  i = 1; i <= n; i++ ) {
		cin >> a[i];
		//怎么维护？
		while (top1 && a[i] >= a[Max[top1]])top1--;
		while (top2 && a[i] <= a[Min[top2]])top2--;
		f[i] = f[Max[top1]] + (i - Max[top1]) * a[i];
		g[i] = g[Min[top2]] + (i - Min[top2]) * a[i];
		ans += (f[i] - g[i]);
		Max[++top1] = i;
		Min[++top2] = i;
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

