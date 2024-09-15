# $stl$->一些使用不当的例子，容易忘记的细节。
- ## $one:\quad map$
  - ### 出错细节：
    - 当map模板的赋值情况如下：
        map<string,s>mmap;
    要注意，数据结构会根据它们的字典序排序区分，查找，不会产生二义性。但是在比较字典序的时候，会花费很多的时间。当串不多，且比较小的时候，考虑用该数据结构管理一些列的字符串集合。此时一般使用字符串哈希，配合管理。
   - ### 使用技巧
      - 当我们确认一个元素确实是存在的时候，我们去查询该关键字指向的卫星数据。有如下方案
        ```CPP
        map<int,int>mmap;
        mmap.insert({1,1});
        int t;
        if(mmap.count(1))
        //first
        t=mmap.find(1)->second;
        //second
        t=mmap[1];
        ```
------
- ## $two:\quad priority\_queue$
    - ### 出错细节：
      - 默认情况下，优先队列是大顶堆。
        ```
        //小顶堆的定义方式。
        priority_queue<int, vector<int>, greater<int>> que;
        //大顶堆的定义方式
        //默认的方法。
        priority_queue<int>  que；
        //详细按照模板定义的方法
        priority_queue<int,vector<int>,less<int>>que;
        ```
-----
- ## $three\quad stl$ 封装的一些高效的函数.