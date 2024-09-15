C. Double Lexicographically Minimum

(https://codeforces.com/contest/1799/problem/C)

简介： 与字典序大小相关的构造：

给定一个字符串：对它进行reordering.对每一种情况 ， 选出该组的max(s , reverse(x));从若干组max中，选出min。

#### solve

采取某一种策略：从小到大遍历s中的字符：

1. l , r不断交替放置min字符.直到字符地个数小于2.
   1. 如果当前剩余字符数为0,进行下一轮.
   2. 如果当前剩余字符数为1
      1. 如果下一个字符的字符数等于剩余位置 - 1.依次两端交替的放置.直到放完,那么最后一个位置放置min
      2. 将min放在r.然后其余所有的字符从小到大, 从l位置开始放置所有剩余字符串.

#### code jly

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    std::string t(n, '?');
    
    int cnt[26] {};
    for (auto c : s) {
        cnt[c - 'a']++;
    }
    
    int l = 0, r = n - 1;
    for (int c = 0; c < 26; c++) {
        while (cnt[c] >= 2) {
            cnt[c] -= 2;
            t[l++] = t[r--] = 'a' + c;
        }
        if (cnt[c] == 1) {
            cnt[c] -= 1;
            if (l == r) {
                t[l] = 'a' + c;
            } else {
                int x = c + 1;
                while (cnt[x] == 0) {
                    x++;
                }
                if (cnt[x] == r - l) {
                    while (cnt[x] >= 2) {
                        cnt[x] -= 2;
                        t[l++] = t[r--] = 'a' + x;
                    }
                    if (cnt[x] == 1) {
                        cnt[x] -= 1;
                        t[l++] = 'a' + x;
                    }
                    t[r] = 'a' + c;
                } else {
                    for (; x < 26; x++) {
                        while (cnt[x] > 0) {
                            cnt[x] -= 1;
                            t[l++] = 'a' + x;
                        }
                    }
                    t[r] = 'a' + c;
                }
            }
            break;
        }
    }
    
    std::cout << t << "\n";
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

