# F-Kevin的矩阵_牛客小白月赛76

[F-Kevin的矩阵_牛客小白月赛76 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/60393/F)

链接：https://ac.nowcoder.com/acm/contest/60393/F
来源：牛客网

*氧气少年*现在有一个长度为 n 的序列 a 和一个空的矩阵，矩阵的行数不限，但列数为 m。

 每次操作他可以从下面的操作中任选其一：



- ​		 任选序列的某个位置，将此位置的数字修改为任意的数字； 
- ​		 将矩阵的列数增加 1； 
- ​		 将矩阵的列数减小 1（如果当前矩阵的列数大于 1）。 


 操作完成后，*氧气少年*将序列中的每个元素依次按照从上到下、从左到右的顺序填到矩阵中。（即：先填第 1 行第 1 列，再填第 1 行第 2 列，…… 填第 1行第 m 列，填第 2行第 1 列，填第 2 行第 2 列，…… 填第 2行第 m 列，以此类推。）



​	*氧气少年*想要让矩阵至少一列的所有数字均为目标数字 k，请求出他需要做的最少的操作次数



### solve

1. m 小于 $\sqrt n$ ,其变化列数的操作花费 最多为$\sqrt n$ , 

2. m 大于等于 $\sqrt n$ 其直接处理其中某一列，其花费做多为$\sqrt n$

综上至多使用$2\sqrt n$ 的花费就可以得到目标解。因此一一枚举即可：

### code

```cpp
const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = 1E6 + 10;
int f(int x) {
	int sq = sqrt(x);
	while (sq * sq < x) sq++;
	return sq;
}
int a[N];
void work(int testNo)
{
	int n ,  m , k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int sq = f(n);
	int ans = inf;
	for (int i = -2 * sq; i <= 2 * sq; i++) {
		int temp = m + i;
		if (temp <= 0) continue;
		// 检查当前的情况 ： 是否。
		for (int j = 0; j < min(n , temp); j++) {
			int res = 0;
			for (int s = j; s < n; s += temp) {
				res += a[s] != k;
			}
			ans = min(ans , res + abs(i));
		}
	}
	cout << ans << "\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}
```

