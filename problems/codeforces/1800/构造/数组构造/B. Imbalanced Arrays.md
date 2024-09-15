# B. Imbalanced Arrays

[Problem - B - Codeforces](https://codeforces.com/contest/1852/problem/B)

![image-20230727154753744](C:/Users/86153/AppData/Roaming/Typora/typora-user-images/image-20230727154753744.png)

### solve

首先先排序一遍： 从两端开始看：

发现由$a_{i}$ 可以挖掘排序后首尾的一些匹配关系： 构造入口是两端，逐步前移动，发现总有唯一构造方案，同时为了防止标记不够用，标记总是从大中选择。

r从大到小遍历，更新了一个r之后，从后往前遍历更新l , 发现矛盾就判无解：
对标记注意错开使用：

1. tagr : n 或者 n - 1 （具体选择要看首尾a[r]的情况，要追求尽量使用满标记。） 
2. tagl : -n 或-n + 1

看上去jls的思路更清晰： 下分析jls的代码思路：

### code jls

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i] < a[j];
    });
    
    int l = 0, r = n - 1;
    int pos = 0;
    std::vector<int> ans(n);
    for (int i = n; i > 0; i--) {
        if (a[p[l]] - pos == 0) {
            ans[p[l]] = -i;
            l++;
        } else if (a[p[r]] - pos == i) {
            ans[p[r]] = i;
            pos++;
            r--;
        } else {
            std::cout << "NO\n";
            return;
        }
    }
    std::cout << "YES\n";
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
```

### myself code

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x) cerr << "[" << __LINE__ << "]" << ": " << x << "\n"

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second

const int inf = 1E9 + 7;
const ll INF = 1E18 + 7;
const int N = 1E6 + 10;

/*
1
3
1 3 1
*/

void work(int testNo)
{
	int n;
	cin >> n;
	vector<pair<int, int>> rec(n + 1);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		rec[i] = { x , i };
	}
	sort(rec.begin() + 1, rec.end());
	vector<int> ans(n + 1);
	int cur ;
	if (rec[1].fi == 0) cur = n - 1;
	else cur = n;
	rec[0].fi = -1000;
	// 错开的构造思路：
	for (int r = n, l = 1; r >= 1 && r >= l; r--, cur -= 2) {
		ans[rec[r].se] = cur;
		int suf = n - r;
		while (r >= 1 && rec[r].fi == rec[r - 1].fi) {
			r--;
			ans[rec[r].se] = cur;
		}

		// 怎么对相遇的情况做出处理？
		while (l <= n - rec[r].fi) {
			ans[rec[l].se] = -cur - 1;
			if (rec[l].fi != suf) {
				// cout << rec[l].fi << " " << n - r << "\n";
				cout << "NO\n"; return;
			}
			l++;
		}
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(i);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

