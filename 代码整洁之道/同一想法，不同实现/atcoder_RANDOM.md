https://atcoder.jp/contests/abc279/tasks/abc279_c

#### compare code

#### jly大佬代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H, W;
    std::cin >> H >> W;
    
    std::vector S(W, std::vector<char>(H)), T(S);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            std::cin >> S[j][i];
        }
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            std::cin >> T[j][i];
        }
    }
    
    std::sort(S.begin(), S.end());
    std::sort(T.begin(), T.end());
    
    if (S == T) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    return 0;
}
```



#### 模仿代码

```cpp
#include <bits/stdc++.h>
using namespace std;

void MAIN();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    MAIN();
}
typedef long long ll;
const int maxn = 2e5 + 10;
//------code-----٩(ˊωˋ*)و ------靓仔代码-----٩(ˊωˋ*)و ----talk is cheap , show me the code--------
vector<string> a, b;
unordered_map<string, int> rec;
void MAIN()
{
    int n, m;
    cin >> n >> m;
    vector s1(m, vector<char>(n)); // y有一些黑科技函数依然是没有用好。
    vector s2(s1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> s1[j][i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> s2[j][i];
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    if (s1 != s2)
        cout << "No\n";
    else
        cout << "Yes\n";
}
```

#### 完全自己写的代码（大思路相同,但是超时了。）

```cpp
#include <bits/stdc++.h>
using namespace std;

void MAIN();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    MAIN();
}
typedef long long ll;
const int maxn = 2e5 + 10;
//------code-----٩(ˊωˋ*)و ------靓仔代码-----٩(ˊωˋ*)و ----talk is cheap , show me the code--------
vector<string> a, b;
unordered_map<string, int> rec;
vector<string> s1, s2;
void MAIN()
{
    int n, m;
    cin >> n >> m;
    a.resize(n + 1), b.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] = ' ' + a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        b[i] = ' ' + b[i];
    }
    for (int i = 1; i <= m; i++)
    {
        string s;
        for (int j = 1; j <= n; j++)
        {
            s = s + a[j][i];//这里不超时才怪。
        }
        s1.push_back(s);
    }
    for (int i = 1; i <= m; i++)
    {
        string s;
        for (int j = 1; j <= n; j++)
        {
            s = s + b[j][i];
        }
        s2.push_back(s);
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    for (int i = 0; i < m; i++)
        if (s1[i] != s2[i])
        {
            cout << "No\n";
            return;
        }
    cout << "Yes\n";
}
```

#### 生长思考

- 第一点：
  - 为什么自己的第二份代码会超时？
    - 构造$s1,s2$的过程中，使用string的重载等于函数。这个函数的常数很大。
  - 换一种更加优的方式进行处理。
    - 像jly上的，倒过来优化资源的输入。
- 第二点： 关于使用vector函数。
  - 构造一个数组的vector对象的其它方法。 
  - 对vector排序的方法。
  - 用等于号快速判断是否相等。