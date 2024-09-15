[manacher - chenxuming 的博客 - 洛谷博客 (luogu.com.cn)](https://www.luogu.com.cn/blog/chenjiuri/manacher)

#### 填充式的manacher的实现：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
using namespace std; //问题背景，求出子串中的最大回文串。
string s1, s;
int ans;
vector<int> d; //处理偶数串
int main()
{
    cin >> s1;
    int n = s1.size();
    s.resize(n * 2 + 1);
    for (int i = 0; i < n; i++)
    {
        s[i * 2] = '#';
        s[i * 2 + 1] = s1[i];
    } //于是已经构建好了。
    s[n * 2] = '#';
    d.resize(n * 2 + 1); //
    n = n * 2 + 1;
    for (int i = 1, l = -1, r = -1, k; i < n; i++)
    {

        k = i > r ? 1 : min(d[l + r - i], r - i);
        while (i - k >= 0 && i + k < n && s[i + k] == s[i - k])
            k++;
        d[i] = --k;
        if(i+k>r)
            r = i + k, l = i - k;
        ans = max(d[i], ans);
    }
    cout << ans;
}
```