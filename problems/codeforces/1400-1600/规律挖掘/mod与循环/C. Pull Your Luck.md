**Pull Your Luck**

[Problem - C - Codeforces](https://codeforces.com/contest/1804/problem/C)

**简介**

定义正整数 h ,定义域为 $h\in[1,h_{max}]$。找到一个h满足$(1+2+...+h)\%n=k$

#### solve

1. 当h = 2n时。 $sum_{h}\%n=n*(2n + 1)\%n=0$

2. 当h > n 时 ， 求和的前缀mod去为0 .新赠的尾部 , 的表示为 n + d。n完蛋了，然后重新变回 $sum(1...(d-n))\%n$
3. 综上只需要，考察$min(2n , h+{max})$即可。

代码比较简单略。