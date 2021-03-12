### 介绍
源代码:GCC-2.95 <br>
文档:cppreference.com和open-std.org<br>
运行环境: vs2019 <br>
这是基于上述写出来的一个玩具STL 主要是为了学习<br>
并不是每个函数都有完善 只挑核心写了 <br>

比如: + `map.insert`据文档有8个重载 但是我只会挑核心写这个+`std::pair<iterator,bool> insert( const value_type& value );`  其他都是大同小异

### 功能
- [x] 迭代器 <br>
- [ ] 算法 <br>
- [x] 容器 <br>
- [x] 仿函数 <br>
- [x] 分配器 <br>
- [x] 适配器 <br>

算法不写是因为很多重复的无用功 写一个东西是为了了解市面上好工具的内部原理 而目前已经通过这个简易的STL了解了标准的STL的内部运作 所以并没有完善到标准库的那种情况

