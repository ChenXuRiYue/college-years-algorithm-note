# D. Matrix Cascade

[Problem - D - Codeforces](https://codeforces.com/contest/1864/problem/D)

There is a matrix of size $n \times n$ which consists of 0s and 1s. The rows are numbered from $1$ to $n$ from top to bottom, the columns are numbered from $1$ to $n$ from left to right. The cell at the intersection of the $x$\-th row and the $y$\-th column is denoted as $(x, y)$.

AquaMoon wants to turn all elements of the matrix to 0s. In one step she can perform the following operation:

-   Select an arbitrary cell, let it be $(i, j)$, then invert the element in $(i, j)$ and also invert all elements in cells $(x, y)$ for $x \gt i$ and $x - i \ge \left|y - j\right|$. To invert a value means to change it to the opposite: 0 changes to 1, 1 changes to 0.

Help AquaMoon determine the minimum number of steps she need to perform to turn all elements of the matrix to 0s. We can show that an answer always exists.

有一个大小为$n \times n$的矩阵，由 0 和 1 组成。行的编号从上到下依次为$1$到$n$，列的编号从左到右依次为$1$到$n$。第$x$行与第$y$列交叉处的单元格记为$(x, y)$。

水月想把矩阵的所有元素都变成 0。她可以一步完成以下操作：

- 选择任意一个单元格，假设它是$(i, j)$，然后反转$(i, j)$中的元素，并反转$(x, y)$单元格中的$x \gt  i$和$x - i \ge \left|y - j\right|$的所有元素。将一个值反转意味着将它变为相反的值：0 变为 1，1 变为 0。

帮助 AquaMoon 确定将矩阵中的所有元素变为 0 所需的最少步骤数。我们可以证明答案总是存在的。



### solve

难以找出一个优雅的规律： 那么就转换成一个模拟的问题：
显然如果每个格子只操作1次。那么方案是唯一的。
变化中关注以下的几个现象：

$cunt_{i , j}$ 处理完i以上的行之后， 第i行第j各个格子的操作次数。

1. $cunt_{i ,j}$首先继承于$cunt_{i - 1, j}$
2. 研究其变化：
   1. 关注第一个翻转的格子： 那么可以这个格子的操作次数是被下一行继承的。此外还造成其它一些映像。相当于有两个哨兵接下来起点分别$j - 1$ , $j + 1$ ， 不断地往前走直到走到终点。
   2. 每一个格子翻转后其行为是独立的。

**生长思考：**

1. 针对一个和数学相关的问，没有一下子找到公式。但是换个角度，好比有一种数列是没有通项公式的，但是它们有递推公式， 使用这些递推公式，逐渐的，也可以得到全局的情况。
2. 要让影响更加密集， 统一。上述就是一个好例子。化繁为简。

### code

```cpp
void work(int testNo)
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1 , vector<int>(n + 1 , 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char x; cin >> x;
            s[i][j] = x - '0';
        }
    }
    vector<int> pre(n + 2 , 0) , suf(n + 2 , 0) , sum (n + 2 , 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int i = 1; i <= n; i++) {
            sum[i] += pre[i];
            sum[i] += suf[i];
        }
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i + 1];
        }
        for (int i = n; i >= 1; i--) {
            suf[i] = suf[i - 1];
        }
        for (int j = 1; j <= n; j++) {
            if ((s[i][j] + sum[j]) % 2) {
                pre[j - 1] ++;
                suf[j + 1] ++;
                sum[j]++;
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++)work(i);
}
```

