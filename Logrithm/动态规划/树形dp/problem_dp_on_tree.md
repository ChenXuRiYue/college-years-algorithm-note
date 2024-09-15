### 树形$dp\quad problems$

####  $first$

###### [P1352上司的舞会](https://www.luogu.com.cn/problem/P1352)

- 问题简介

  ```txt
  若干个节点构成了一棵树。整体快乐指数计算规则如下：选择若干个节点，它们的快乐指数之和。
  若干个节点的选择规则： 直接父节点和子节点不共存。
  问最大快乐指数。
  ```

- 分析
  $$
  定义 f_{i,0/1}分别表示，该节点选择(1)，不选择(0)时，子树方案中的最大快乐指数。\\
  f_{i,1}=\sum(f_{i,0})+w_i;\\
  f_{i,0}=\sum(max(f_{j,1},f_{j,0}));\\
  $$

- #### $code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 6e3 + 10;
int inf = -1e9;
int w[maxn], f[maxn][2];
vector<int> g[maxn];

void dfs(int now){
    if (f[now][1] != inf)
        return;
    f[now][1] = f[now][0] = 0;
    for (auto to : g[now]){
        dfs(to);
        f[now][0] += max(f[to][0], f[to][1]);
        f[now][1] += f[to][0];
    }
    f[now][1] += w[now];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> w[i];
        f[i][1] = f[i][0] = inf;
    }
    for (int i = 1; i <= n-1; i++){
        int a, b;
        cin >> a >> b;
        g[b].push_back(a);
    }
    int ans = inf;
    for (int i = 1; i <= n; i++){
        dfs(i);
        ans = max(ans, max(f[i][1], f[i][0]));
    }
    cout << ans << '\n';
}
```

$15:21.57$

---

#### $second$

###### [加分二叉树](https://www.luogu.com.cn/problem/P1040) 

- 简介

  ```txt
  计算的一颗二叉树的加分：具体规则如下
  左子树的加分*右子树的加分。
  如果子树为空，加分为1.
  叶子的加分为本身的分数。
  给出中序遍历：
  求满足所有该中序遍历的最大加分二叉树的最大加分和。
  并且输出前序遍历。
  ```

- 分析

  - 关于二叉树的几个概念，中序遍历，前序遍历。

  ```txt
  来源《数据结构辅导书》的遍历二叉树。
  遍历二叉树的实质是将二叉树进行线性化，即便里的结果是将非线性结构树中的节点排成一个线性序列。
  
  前序遍历：
  若二叉树为空，操作为空，否则：
  1.访问根节点：
  2.先序遍历左子树。
  3.先序遍历右子树。
  DLR
  
  中序遍历:
  若二叉树为空，操作为空，否则：
  1.中序遍历左子树：
  2.访问根节点：
  3.中序遍历右子树：
  
  后序遍历：
  若二叉树为空操作为空，否则：
  1.后续遍历左子树：
  2.后续遍历右子树：
  3.访问根节点：
  ```

- 惨痛教训—又读假题。

```txt
当一个中序确定时，并不代表着一棵树确定。每一个节点都可以作为二叉树的根。然后进一步分割，进一步确定其它的根。最终就完全确定，这一颗树的形状。

question，
当两个序都确定了是否就可以确定了一个树的形状？


可以认为区间dp问题。
解决的问题时 【1，n】的一个二叉树，并且使他的加分最大。

小规模问题  【l,r】->[l,k-1].[k+1,r].两种子树，两种个子树的最大加分。
规模前进   1 2 3---即可。最终可以得到f(1,n)的解。

求前序，记录每一个小区间的最优子树下的根。这样就可以确定一个具体的二叉树。
递归的完成。
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 40;
ll f[maxn][maxn]; //加分二叉树。
ll w[maxn];
int root[maxn][maxn];

void print(int x, int y)
{
    if (x > y)
        return;
    cout << root[x][y] << ' ';
    print(x, root[x][y] - 1);
    print(root[x][y] + 1, y);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] = 1, root[i][j] = i; //针对一边界就是根部的情况。
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        f[i][i] = w[i];
    }
    for (int i = 2; i <= n; i++)             //枚举长度，
        for (int j = 1; j <= n - i + 1; j++) //枚举终点
            for (int k = j, tt = j + i - 1; k <= tt; k++)
            {
                ll temp = f[j][k - 1] * f[k + 1][tt] + w[k];
                if (temp >= f[j][tt])
                    f[j][tt] = temp, root[j][tt] = k;
            }
    cout << f[1][n] << '\n';
    print(1, n);
    cout << '\n';
}

```

###### 总结

- 这样一道不能算典型树形$dp$，按照这一种特殊情形之下，应该算区间$dp$。
