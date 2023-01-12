https://blog.csdn.net/weixin_43533544/article/details/90750342
也许是你从未见过的黑科技

很多小伙伴或许想到了离线查询，先对矩阵排序，再对点排序，然后从最后一个点开始往前遍历，
并将遇到的高度加入到set中,到当前高度时,在set里面二分查询,查询到的位置作为答案，
但是,c++里面的set不能添加重复元素,所以我们要用multiset,set和multiset二分搜索返回的迭代器都无法进行加减操作,
因此我们并不能知道这个位置前面的元素有多少个。

有一个黑科技可以弥补这个问题，希望大家能学到这个知识，
说不定不久的将来会派上用场,pb_ds库,也就是平板电视,首先我们需要引入头文件:
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

接着定义红黑树(也就是set),tree<int, null_type, less<int>, rb_tree_tag, 
tree_order_statistics_node_update> t;

对红黑树进行二分查找,也是lower_bound和upper_bound,
但是,我们有order_of_key函数,他可以直接知道我们要查询的数，是红黑树中第几大的元素

有了以上这些依然不够,因为我们的题目一定有重复元素的存在,解决问题的办法就是使用pair,
定义红黑树的方法改写为tree<pair<int,int>, null_type, less<pair<int,int>>, 
rb_tree_tag, tree_order_statistics_node_update> t;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
/*
定义一颗红黑树
int 关键字类型
null_type无映射(低版本g++为null_mapped_type)
less<int>从小到大排序
rb_tree_tag 红黑树（splay_tree_tag）
tree_order_statistics_node_update结点更新
插入t.insert();
删除t.erase();
求k在树中是第几大:t.order_of_key();0开始
求树中的第k大:t.find_by_order();0开始
前驱:t.lower_bound();
后继t.upper_bound();
a.join(b)b并入a 前提是两棵树的key的取值范围不相交
a.split(v,b)key小于等于v的元素属于a，其余的属于b
T.lower_bound(x)   >=x的min的迭代器
T.upper_bound((x)  >x的min的迭代器
T.find_by_order(k) 有k个数比它小的数
*/

gp_hash_table<int,int> 哈希表

#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& r, vector<vector<int>>& points) {
        sort(r.begin(),r.end());//先排序
        vector<int>ans(points.size(),0);
        for(int i=0;i<points.size();i++)
        {
            points[i].push_back(i);//离线查询
        }
        tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> t;
        
        sort(points.begin(),points.end());//排序
        int now=r.size()-1;//now意味指向矩阵当前遍历位置的指针
        int s=1;
        for(int i=points.size()-1;i>=0;i--)
        {
            int k=0;
            int nowh=points[i][1];
            if(now>=0)
            {
                while(r[now][0]>=points[i][0])
                {
                    
                    t.insert(make_pair(r[now][1],s));//s是至关重要的，他只需要保证我们在插入相同元素的时候不同就可以了
                    s++;
                    now--;//移动指针直到r[now][0]<points[i][0]
                    if(now<0)
                    {
                        break;
                    }
                }
            }
            int p=t.order_of_key(make_pair(nowh,-1));//这样的查询可以得到当前高度的排名
            ans[points[i][2]]=t.size()-p;   //用红黑树大小减去这个排名，就是当前查询的答案
        }
        return ans;
    }
};




