https://codeforces.com/contest/1555/problem/D



通过简单的构造。

我们发现如果不想成回文串。

必然要abc acb bac bca cab cba中的六种之一，不断的连续拼接。



第一种方法时dp

$f[i][j][k]$表示1....i的区间之内。j字符在余k位置上出现地次数。

具体到一个子串时，枚举6中种处理方案。

注意长度特判小于3的情况。

总的来说这个处理起来相对麻烦了一点。



#### 更优的处理方案：

直接记录六种方案之下的每一段的贡献。

具体到子串上的一个问题的时候，直接利用前缀和，就可以得到当前方案下的代价。

#### tourist's code

```cpp
/**
 *    author:  tourist
 *    created: 30.07.2021 17:40:35       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<vector<int>> pref;
  for (char a : {'a', 'b', 'c'}) {
    for (char b : {'a', 'b', 'c'}) {
      for (char c : {'a', 'b', 'c'}) {
        if (a != b && a != c && b != c) {
          pref.emplace_back(n + 1);
          for (int i = 0; i < n; i++) {
            char d = (i % 3 == 0 ? a : (i % 3 == 1 ? b : c));
            pref.back()[i + 1] = pref.back()[i] + (s[i] != d);
          }
        }
      }
    }
  }
  while (m--) {
    int L, R;
    cin >> L >> R;
    --L; --R;
    int ans = (int) 1e9;
    for (auto& v : pref) {
      ans = min(ans, v[R + 1] - v[L]);
    }
    cout << ans << '\n';
  }
  return 0;
}
```



#### mycode

```CPP
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int oo = 0x0fffffff;

const int N = 1E6 + 10;

int cnt[3][3];
int sum[N][3][3];
string v[6] { "abc", "acb", "bac", "bca", "cab", "cba" };


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				sum[i + 1][j][k] = sum[i][j][k];
			}
		sum[i + 1][s[i] - 'a'][i % 3]++;
	}
	while (m--)
	{

		int ans = oo, l, r;
		cin >> l >> r;
		int size = r - l + 1;
		if (size <= 3)
		{
			set<char>rec;
			for (int i = l - 1; i < r; i++)
				rec.insert(s[i]);
			cout << size - rec.size() << '\n';
			continue;
		}
		for (int i = 0; i < 6; i++) {
			int temp = 0;
			//d当前枚举的情况时s[i]类型的符号分布情况。分别将是s[i][0]放在余0位置，
			//同理推导到其它字符的情况。
			//研究每一种分类是否妥当并被计算。
			for (int j = 0; j < min(size, 3); j++) //具体到某一个位置上的情况。
			{
				int need = (size) / 3 + (size % 3 >= j + 1); //现在剩余几个位置。1则说明第一位还是要添。第二位说明a,b都要添加。
				int have = sum[r][v[i][j] - 'a'][j] - sum[l - 1][v[i][j] - 'a'][j];
				temp += need - have;
			}

			ans = min(ans, temp);
		}
		cout << ans << '\n';

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





