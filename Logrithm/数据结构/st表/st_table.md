### st表 dls

```cpp
const int N = (int)1E6 + 10;
//把较小的维度放在前面有利于优化维度。
ll f[22][N] , a[N];
//int log[N];
void init() {
    //预处理log。
    //for(int i = 2; i <= n; i++) log[i] = log[i / 2] + 1;
	for (int i = 1; i <= n; i++) f[0][i] = a[i];
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			f[j][i] = max(f[j - 1][i] , f[j - 1][i + (1 << (j - 1))]);
		}
	}
}
int query(int l , int r) {
    assert(l <= r);
    //len = log[r- l + 1];
	int len = 31 - __builtin_clz(r - l + 1);
	return max(f[len][l] , f[len][r - (1 << len) + 1]);
}
//这个下标默认从1开始。
```

### tourist的st表

```cpp
/**
 *    author:  tourist
 *    created: 31.05.2022 18:35:43
**/
template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
	int n;
	vector<vector<T>> mat;
	F func;

	SparseTable(const vector<T>& a, const F& f) : func(f) {
		n = static_cast<int>(a.size());
		int max_log = 32 - __builtin_clz(n);
		mat.resize(max_log);
		mat[0] = a;
		for (int j = 1; j < max_log; j++) {
			mat[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= n - (1 << j); i++) {
				mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	T get(int from, int to) const {
		assert(0 <= from && from <= to && to <= n - 1);
		int lg = 32 - __builtin_clz(to - from + 1) - 1;
		return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
	}
};
//应用示例。挺好用的
/*int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<ll> a(n + 1);
	SparseTable<long long> smin(a, [&](long long i, long long j) { return min(i, j);});
	SparseTable<long long> smax(a, [&](long long i, long long j) { return max(i, j);});
}*/

```

