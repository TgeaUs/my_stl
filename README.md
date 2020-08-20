### 介绍
源代码:GCC-2.95 <br>
文档:cppreference.com和open-std.org<br>
这是基于上述两个东西写出来的一个玩具STL 主要是为了学习<br>
并不是每个函数都有完善 只挑核心写了 <br>
比如: <span style="color: green"> map.insert </span>据文档有8个重载 但是我只会挑核心写这个 std::pair<iterator,bool> insert( const value_type& value );  其他都是大同小异

### 功能
- [x] 迭代器 <br>
- [x] 算法 <br>
- [x] 容器 <br>
- [x] 仿函数 <br>
- [x] 分配器 <br>
- [x] 适配器 <br>
> 容器
