## Fire!

 [Fire! - UVA 11624 - Virtual Judge (csgrandeur.cn)](https://vjudge.csgrandeur.cn/problem/UVA-11624#author=0)

#### 20mins

bfs解决几个问题：

1. 基于合法的最初状态进行转移。
   1. 有多少个方向？
   2. 其中怎么判断是否合法？
2. 终点是什么？

本问题中 ：

1. 先将火焰的蔓延情况全部求取出来。
2. 然后通过火焰的分布情况来指导J的转移：
   1. 