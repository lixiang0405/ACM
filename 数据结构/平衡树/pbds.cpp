/*
您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
1.插入 x 数
2.删除 x 数(若有多个相同的数，因只删除一个)
3.查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
4.查询排名为 x 的数
5.求 x 的前驱(前驱定义为小于 x，且最大的数)
6.求 x 的后继(后继定义为大于 x，且最小的数)
*/

tree<pii, null_type , less<pii>, rb_tree_tag, 
tree_order_statistics_node_update> st;

int cnt=0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	rep(i,1,n+1){
		int ty;
		cin>>ty;
		if(ty==1){
			int x;
			cin>>x;
			st.insert({x,++cnt});
		}else if(ty==2){
			int x;
			cin>>x;
			auto it=st.lower_bound({x,0});
			if(it!=st.end()&&it->fi==x){
				st.erase(it);
			}
		}else if(ty==3){
			int x;
			cin>>x;
			auto it=st.lower_bound({x,0});
			cout<<st.order_of_key(*it)+1<<'\n';
		}else if(ty==4){
			int x;
			cin>>x;
			x--;
			cout<<st.find_by_order(x)->fi<<'\n';
		}else if(ty==5){
			int x;
			cin>>x;
			auto it=st.lower_bound({x,0});
			it--;
			cout<<(it->fi)<<'\n';
		}else{
			int x;
			cin>>x;
			auto it=st.upper_bound({x,(1<<30)});//fi相同时将比较se，所以se要设置为inf
			cout<<(it->fi)<<'\n';
		}
	}
	return 0;
} 