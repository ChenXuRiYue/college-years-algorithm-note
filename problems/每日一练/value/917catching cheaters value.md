##### 问题简介

```txt
给定串 A ，B：（1.小写字母组成。）
定义S(C,D)=4*LCS(C,D)-|C|-|D|.其中
question max(S(C,D)).其中 C，D分别是A和B的子串。 
1<=|B|,|A|<=5000.
```

##### 基本的方向

1. 处理该式子。
2. 联想关于公共子序列的经典问题，经典优化思路。

##### 借鉴题解

```txt
尝试dp动态规划：
记录 f[i][j]；这个状态的意义是不好表示的，从s1---i,t1----j,有意义的最大前缀拼接贡献。
解决小规模的问题过程中中。
if(s[i]==t[j])一种最优方案 f[i][j]=f[i-1][j-1]+4-2=f[i-1][j-1]+2;
if(s[i]!=t[j])           f[i-1][j-1]=max(f[i-1][j]-1,f[i+1][j]-1).选择或者不选。
如果小于o这一段中，无论不如不选。，直接设置为0，该点真正表示的从该点开始的后一段是后一段即可。
说明该状态的定义有待待定。
```

##### code 

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e3 + 10;
int f[maxn][maxn];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    s = '#' + s;
    t = '#' + t;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s[i] == t[j])
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 2);
            else
                f[i][j] = max(f[i - 1][j] - 1, f[i][j - 1] - 1);
            f[i][j] = max(f[i][j], 0);
            ans = max(ans, f[i][j]);
        }
    cout << ans << '\n';
}
```

