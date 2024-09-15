**Making the Grade**

A straight dirt road connects two fields on FJ's farm, but it changes elevation more than FJ would like. His cows do not mind climbing up or down a single slope, but they are not fond of an alternating succession of hills and valleys. FJ would like to add and remove dirt from the road so that it becomes one monotonic slope (either sloping up or down).

You are given *N* integers *A*1, ... , *AN* (1 ≤ *N* ≤ 2,000) describing the elevation (0 ≤ *Ai* ≤ 1,000,000,000) at each of *N* equally-spaced positions along the road, starting at the first field and ending at the other. FJ would like to adjust these elevations to a new sequence *B*1, . ... , *BN* that is either nonincreasing or nondecreasing. Since it costs the same amount of money to add or remove dirt at any position along the road, the total cost of modifying the road is

> |*A*1 - *B*1| + |*A*2 - *B*2| + ... + |*AN* - *BN* |

Please compute the minimum cost of grading his road so it becomes a continuous slope. FJ happily informs you that signed 32-bit integers can certainly be used to compute the answer.

https://vjudge.csgrandeur.cn/problem/POJ-3666

#### solve

两种方法：
1. 尝试突破的角度： 是否可以对方案进行压缩？归纳出规模更小的问题 ， 以及更简洁的转移？
2. 