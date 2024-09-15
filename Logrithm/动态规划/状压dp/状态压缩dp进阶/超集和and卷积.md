**AND卷积**
http://oj.daimayuan.top/course/8/problem/371



----


![image-20230503151810316](image-20230503151810316.png)

#### 超集合

$$
g_i = \sum _{i \& j = i } f_j
$$

对于二进制的每一个位 ，都要求j大于等于i 。 所以转变成一个后缀和问题： 
##### code

```cpp
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((j & (1 << i)) == 0) {
				f[j] += f[j + (1 << i)];
			}
		}
	}
```

**转换过程：**

$F_i$:  $f_i$的后缀和。
$$
F_i = \sum _{k >= i} f_k\\
$$
$G_i$  $g_i$的后缀和。
$$
G_i = \sum _{k >= i} g_k
$$


$H_i$  定义为$h_i$的后缀和。
$$
H_i = \sum _{k >= i}h_k
$$
**关键性质1：**
$$
H_i = F_i \times G_i。\\
$$
感受上述性质， 对于上述乘法式子的每一个组合， 都唯一投射到 唯一的一个$h_j$上 。 同时对于不在$H_i $ , $F_i$中的元素是必然没有投射到某种解的。

**最后的问题 ： 由后缀和还原空间中的元素$h_i$**

按照规律就是逆着做差。

```
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((j & (1 << i)) == 0) {
				f[j] -= f[j + (1 << i)];
			}
		}
	}
```





#### code

```cpp
const int inf = 1 << 29;
const ll INF = 1LL << 60;
const int N = 1E6 + 10;

unsigned int A, B, C;
inline unsigned int rng61() {
	A ^= A << 16;
	A ^= A >> 5;
	A ^= A << 1;
	unsigned int t = A;
	A = B;
	B = C;
	C ^= t ^ A;
	return C;
}
const int M = 1 << 22;
const int mod = 1000000007;
ll f[M + 10];
ll g[M + 10];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n >> A >> B >> C;
	for (int i = 0; i < (1 << n); i++)
		f[i] = rng61();
	for (int i = 0; i < (1 << n); i++)
		g[i] = rng61();
    //一种特殊的数据shu
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((j & (1 << i)) == 0) {
				f[j] += f[j + (1 << i)];
				g[j] += g[j + (1 << i)];
			}
		}
	}
	for (int i = 0; i < (1 << n); i++) {
		f[i] %= mod;
		g[i] %= mod;
		f[i] = f[i] * g[i] % mod;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((j & (1 << i)) == 0) {
				f[j] -= f[j + (1 << i)];
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		f[i] %= mod;
		if (f[i] < 0)
			f[i] += mod;
		ans ^= f[i];
	}
	cout << ans << "\n";
}
```
