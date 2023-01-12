/*
构造函数
bitset(): 每一位都是 false。
bitset(unsigned long val): 设为 val 的二进制形式。
bitset(const string& str): 设为 01 串 str。

运算符
operator []: 访问其特定的一位。
operator ==/!=: 比较两个 bitset 内容是否完全一样。
operator &/&=/|/| =/^/^=/~: 进行按位与/或/异或/取反操作。bitset 只能与 bitset 进行位运算，若要和整型进行位运算，要先将整型转换为 bitset。
operator <>/<<=/>>=: 进行二进制左移/右移。
operator <>: 流运算符，这意味着你可以通过 cin/cout 进行输入输出。

成员函数¶
count(): 返回 true 的数量。
size(): 返回 bitset 的大小。
test(pos): 它和 vector 中的 at() 的作用是一样的，和 [] 运算符的区别就是越界检查。
any(): 若存在某一位是 true 则返回 true，否则返回 false。
none(): 若所有位都是 false 则返回 true，否则返回 false。
all():C++11，若所有位都是 true 则返回 true，否则返回 false。
set(): 将整个 bitset 设置成 true。
set(pos, val = true): 将某一位设置成 true/false。
reset(): 将整个 bitset 设置成 false。
reset(pos): 将某一位设置成 false。相当于 set(pos, false)。
flip(): 翻转每一位。（，相当于异或一个全是  的 bitset）
flip(pos): 翻转某一位。
to_string(): 返回转换成的字符串表达。
to_ulong(): 返回转换成的 unsigned long 表达 (long 在 NT 及 32 位 POSIX 系统下与 int 一样，在 64 位 POSIX 下与 long long 一样）。
to_ullong():C++11，返回转换成的 unsigned long long 表达。

一些文档中没有的成员函数：
_Find_first(): 返回 bitset 第一个 true 的下标，若没有 true 则返回 bitset 的大小。
_Find_next(pos): 返回 pos 后面（下标严格大于 pos 的位置）第一个 true 的下标，若 pos 后面没有 true 则返回 bitset 的大小。

*/