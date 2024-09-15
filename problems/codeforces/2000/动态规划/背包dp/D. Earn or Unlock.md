# D. Earn or Unlock

[Problem - D - Codeforces](https://codeforces.com/contest/1855/problem/D)

Andrea is playing the game Tanto Cuore.

![](9530fd0a2ed9a8c0f1f686637cff167fb8ac008b.png)

He has a deck of $n$ cards with values $a_1, \ldots, a_n$ from top to bottom. Each card can be either locked or unlocked. Initially, only the topmost card is unlocked.

The game proceeds in turns. In each turn, Andrea chooses an unlocked card in the deck — the value written on the card is $v$ — and performs exactly one of the following two operations:

1.  Unlock the first $v$ **locked** cards in the deck from the top. If there are less than $v$ locked cards in the deck, then unlock all the locked cards.
2.  Earn $v$ victory points.

In both cases, after performing the operation, he removes the card from the deck.

The game ends when all the cards remaining in the deck are locked, or there are no more cards in the deck.

What is the maximum number of victory points Andrea can earn?

翻译
Andrea 正在玩 "Tanto Cuore "游戏。
![](https://espresso.codeforces.com/9530fd0a2ed9a8c0f1f686637cff167fb8ac008b.png)
他有一副从上到下数值为 $a_1, \ldots, a_n$的$n$张牌。每张牌都可以上锁或解锁。最初，只有最上面的一张牌是解锁的。
游戏轮流进行。在每一轮中，安德烈娅从牌组中选择一张未上锁的牌--牌上写的数值是 $v$--并执行以下两个操作中的一个：

1.  解锁第一张$v$锁牌组中自上而下的第 $v$张**锁**牌。如果牌组中锁定的牌少于$v$张，则解锁所有锁定的牌。
2.  获得 $v$ 胜利点数。
在这两种情况下，执行完操作后，他都会将卡牌从牌面移除。
当牌组中所有剩余的牌都被锁定或牌组中不再有牌时，游戏结束。
Andrea 最多能获得多少胜利点数？

### solve
**基本的观察：**
1. 如果使用了某些可行的牌组，在保证可行性的前提下（即，i牌不是开启j牌的前提。）牌使用顺序是无关的。
2. 在不开启的牌组中能选就选。如果已知道开启牌最远到x牌。则可以直接确定其花费是：$sum_i - (i - 1)$ 因为开启的牌数等于使用牌子的胜利点数。因此总的用来开启牌数的胜利点数和为i - 1（除去第一张， 其它都是通过胜利点数开启的.）

**启发**
只要确定了所有可能开启的范围：就可以统计出所有可能的答案。这种可行性问题，可以考虑天然bitset优化实现。

**1 .状态定义：**
$f_{i , s}$ 表示当前前可以开启的最大长度。

**1 .状态转移方程：**
小于位置i的最大范围，都不能作为是i可用的前提。都不可以参与转移。因此将比i更低位的可行范围全部标记为0.然后根据i的点数做一个移动位运算。最后将所有的i的情况都或起来。

**2 . 状态定义：**
使用滚动数组优化： $f_s$ 表示考虑完1...i（假设当前滚动到了第i个物品。）

**2. 状态转移方程：**

$f |= (f >> i) << (i + a_i)$ : 清空低位，更新高位。

### code ， 下面的代码主要是借鉴tourist

```cpp
const int inf = 1E9 + 7;;
const ll INF = 1E18 + 7;
const int N = 2E5 + 10;
int a[N];
ll sum[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	bitset<N> f;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		// sum[i] = sum[i - 1] + a[i];
	}
	f[1] = 1;
	for (int i = 1; i <= n; i++) {
		f |= (f >> i) << (i + a[i]);
	}
	ll ans = 0;
	for (int i = 1; i < N; i++) {
		sum[i] = sum[i - 1] + a[i];
		if (f[i]) ans = max(ans , sum[i] - i + 1);
	}
	cout << ans << "\n";
}
```





