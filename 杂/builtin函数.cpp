/*
__builtin_ffs(x)：返回x中最后⼀个为1的位是从后向前的第⼏位，如__builtin_ffs(0x789)=1, __builtin_ffs(0x78c)=3。于
是，__builtin_ffs(x) - 1就是x中最后⼀个为1的位的位置。

__builtin_popcount(x)：x中1的个数。

__builtin_ctz(x)：x末尾0的个数。x=0时结果未定义。

__builtin_clz(x)：x前导0的个数。x=0时结果未定义。

__builtin_parity(x)：x中1的奇偶性。

__builtin_return_address(n)：当前函数的第n级调⽤者的地址，⽤的最多的就是__builtin_return_address(0)，即获得当前函数的
调⽤者的地址。注意，该函数实现是体系结构相关的，有些体系结构只实现了n=0的返回结果。
uint16_t __builtin_bswap16 (uint16_t x)、 uint32_t __builtin_bswap32 (uint32_t x)：按字节翻转x，返回翻转后的结果。

__builtin_prefetch (const void *addr, …)：它通过对数据⼿⼯预取的⽅法，在使⽤地址addr的值之前就将其放到cache中，减少了
读取延迟，从⽽提⾼了性能，但该函数也需要 CPU 的⽀持。该函数可接受三个参数，第⼀个参数addr是要预取的数据的地址，第⼆个
参数可设置为0或1（1表⽰我对地址addr要进⾏写操作，0表⽰要进⾏读操作），第三个参数可取0-3（0表⽰不⽤关⼼时间局部性，
取完addr的值之后便不⽤留在cache中，⽽1、2、3表⽰时间局部性逐渐增强）。

__builtin_constant_p (exp)：判断exp是否在编译时就可以确定其为常量，如果exp为常量，该函数返回1，否则返回0。如果exp为
常量，可以在代码中做⼀些优化来减少处理exp的复杂度。

__builtin_types_compatible_p(type1, type2)：判断type1和type2是否是相同的数据类型，相同返回1，否则返回0。该函数不区分
const/volatile这样的修饰符，即int和const int被认为是相同的类型。

__builtin_expect (long exp, long c)：⽤来引导gcc进⾏条件分⽀预测。在⼀条指令执⾏时，由于流⽔线的作⽤，CPU可以完成下⼀
条指令的取指，这样可以提⾼CPU的利⽤率。在执⾏⼀条条件分⽀指令时，CPU也会预取下⼀条执⾏，但是如果条件分⽀跳转到了其
他指令，那CPU预取的下⼀条指令就没⽤了，这样就降低了流⽔线的效率。内核中的likely()和unlikely()就是通过__builtin_expect来
实现的。

__builtin_expect (long exp, long c)函数可以优化程序编译后的指令序列，使指令尽可能的顺序执⾏，从⽽提⾼CPU预取指令的正确
率。该函数的第⼆个参数c可取0和1，



*/