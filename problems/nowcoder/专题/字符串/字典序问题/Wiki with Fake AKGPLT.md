**Wiki with Fake AKGPLT**

[F-Wiki with Fake AKGPLT_“2021年中国高校计算机大赛-团队程序设计天梯赛（GPLT）上海理工大学校内选拔赛” (nowcoder.com)](https://ac.nowcoder.com/acm/contest/13276/F)

#### solve

看代码即可：

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 10;

string t = "AKGPLT";

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	while (n --) {
		string s;
		cin >> s;
		if (s > t) {
			cout << 0 << '\n';
			continue;
		}
		bool flag = true;
		for (int i = 0 ; i < (int)s.length(); i++) {
			if (i >= 2 && s[i] > 'K') {
				cout << i - 1 << '\n';
				flag = false;
				break;
			}
			if (s[i] != 'A') {
				cout << i << '\n';
				flag = false;
				break;
			}
		}
		if (flag) { cout << -1 << '\n';}


	}
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/
```

##### 生长总结

1. 前缀的字符串（不相等）的字典序比其本身小。