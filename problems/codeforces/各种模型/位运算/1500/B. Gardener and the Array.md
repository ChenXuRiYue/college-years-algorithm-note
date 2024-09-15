https://codeforces.com/contest/1775/problem/B

就是给定若干个数。判断这若干个数之间是否可以分成几个序列。使得这个序列之间的或相等。



位运算相关的问题，一个常见的角度就是思考位与位之间的关系。

1. 假设存在上述条件。

那么现在进行一些演绎。

a序列中拿出一个。数组中的其余元素单独并一块。记为$S_1$

那么$S_1$和一整块数组$S$满足上述关系。

反过来看，如果存在一个c。拿出来之后，剩下的元素中做或运算。覆盖了c。那么必然可以构造出上述的形式。

综上构成了充要条件。

##### CODE

```CPP
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int oo = 0x0fffffff;
const int N = 1E6 + 10;

void work(int testNo)
{
	int n;
	cin >> n;
	map<int , int>rec;
	bool flag = false;
	vector<vector<int>> a(n);
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		a[i].resize(k);
		for (int j = 0 ; j < k; j++ ) {
			cin >> a[i][j];
			rec[a[i][j]]++;
		}
	}

	for (int i = 0; i < n; i++) {
		flag = true;
		for (auto &j : a[i]) {
			if (rec[j] == 1) {
				flag = false;
				break;
			}
		}
		if (flag) {
			cout << "YES\n";
			return;
		}
	}

	cout << "NO\n";
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++)work(t);
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

#### 生长思考。

- 位运算背景下的问题。研究性质。
- 结论假设的角度就是各个位之间的关系。正着来看不出，就逆着；来。

