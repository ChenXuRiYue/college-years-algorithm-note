**E Tree Master**

[Problem - E - Codeforces](https://codeforces.com/contest/1806/problem/E)

#### solve

参考博客：[Codeforces Round 858 (Div. 2) A - E - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/615119672)

经典树上奇奇怪怪的根号N的做法挖掘。

考虑两种问题不同的处理方法：

1. 一类为暴力做。
2. 一类为记忆化搜索。

两部分总的贡献都是根号复杂度。因为对两种问题，点进行分开讨论，于是称为根号分治？

人类智慧。

关注它们与lca的距离。

1. 如果点到lca的距离大于$\sqrt n$，那么直接暴力即可。
2. 如果点到lca的距离小于$\sqrt n$，采取记忆化搜索的方式。可以知道这种点的对数，不会超过
