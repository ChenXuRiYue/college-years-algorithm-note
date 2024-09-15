**Pushing Boxes**蓝书

[C-Pushing Boxes_0x25 搜索-广度优先搜索 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/1017/C)

#### solve

研究过程中的解。

1. 第一个关注箱子的最短移动步数。ans以箱子的步数最短为前提。

**1.**

箱子第一步到达某一个位置。关注的过程为人先到达箱子的某一侧人后向前推动。

**2.**

在1的队列上进行拓展。

状态：f_box\[x]\[y]\[dir]box在（x , y）上。人在箱子的某一侧：dir->(0...3)表示上下左右侧。箱子已经移动的步数。

​             f_man\[x]\[y]\[dir] 同理 ，表示人已经移动的步数。

搜索框架。

1. 箱子在（x , y）不动 ， 人用尽量少的步数从起点（x - dx[dir], y + dy[dir]）移动到(x - dx[k] , y - dy[k])。
2. 人沿着k方向推一次箱子，箱子移动到x + dx[k] , y + dy[k]处。人移动到（x, y）。

