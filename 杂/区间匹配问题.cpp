//转化为 a[i]<=c[i],b[i]<=d[i]的形式

/*高桥有N块巧克力。第i块为宽度为a厘米和长度B厘米的矩形。
他还有M个盒子。第i个框的宽度为C厘米和长度D厘米的矩形。
确定在以下条件下是否可以将N块巧克力放入盒子中。
1.一个盒子最多只能装一块巧克力。
2.Ai≤Cj和Bi≤Dj*/

VI e[N],q[N];
int a[N],b[N],c[N],d[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	VI x;
	rep(i,1,1+n) cin>>a[i],x.pb(a[i]);
	rep(i,1,1+n) cin>>b[i];
	rep(i,1,1+m) cin>>c[i],x.pb(c[i]);
	rep(i,1,1+m) cin>>d[i];
	sort(all(x));
	x.erase(unique(all(x)),x.end());
	rep(i,1,1+m){
		e[lower_bound(all(x),c[i])-x.begin()+1].pb(d[i]);
	}
	rep(i,1,1+n){
		q[lower_bound(all(x),a[i])-x.begin()+1].pb(b[i]);
	}
	map<int,int> mp;
	per(i,1,4e5+1){
		for(auto cur:e[i]){
			mp[cur]++;
		}
		for(auto cur:q[i]){
			auto it=mp.lower_bound(cur);
			if(it==mp.end()){
				cout<<"No\n";
				return 0;
			}
			it->se--;
			if(it->se==0) mp.erase(it);
		}
	}
	cout<<"Yes\n";
	return 0;
}

/*
https://codeforces.com/problemset/problem/555/B

输入 n(2≤n≤2e5) 和 m(1≤m≤2e5)，然后输入 n 行，每行有两个数，表示一个闭区间（1≤L≤R≤1e18），然后输入一个长为 m 的数组 a (1≤a[i]≤1e18)。输入保证区间之间没有交集，且上一个区间的右端点小于下一个区间的左端点。

你有 m 座桥，每座桥的长为 a[i]，你需要选择 n-1 座桥连接所有相邻的区间。
要求桥的两个端点分别落在这两个闭区间内（这两个端点的差等于桥长）。

如果无法做到，输出 No；否则输出 Yes，然后按顺序输出这 n-1 座桥的编号（编号从 1 开始），输出的第一座桥连接第一个区间和第二个区间，输出的第二座桥连接第二个区间和第三个区间，依此类推。

思考：如果不要求连接的两个区间相邻，你能否连通所有区间？

本题算作区间与点的最大匹配/覆盖问题
类似的还有 https://www.luogu.com.cn/problem/P2887
*/

//转化为-r<=-a[i] l<=a[i]即可

vector<pll> e[N],q[N];
ll a[N],b[N],c[N],d[N],ans[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	vector<ll> x;
	ll prel=-1,prer=-1;
	set<array<ll,3>> st; 
	rep(i,0,n){
		ll l,r;
		cin>>l>>r;
		if(prel!=-1){
			a[i]=-r+prel;
			b[i]=l-prer;
			x.pb(a[i]);
		}
		prel=l;
		prer=r;
	}
	rep(i,1,1+m){
		ll tmp;
		cin>>tmp;
		c[i]=-tmp;
		d[i]=tmp;
		x.pb(c[i]);
	}
	sort(all(x));
	x.erase(unique(all(x)),x.end());
	rep(i,1,1+m){
		e[lower_bound(all(x),c[i])-x.begin()+1].pb({d[i],i});
	}
	rep(i,1,n){
		q[lower_bound(all(x),a[i])-x.begin()+1].pb({b[i],i});
	}
	map<ll,VI> mp;
	per(i,1,4e5+1){
		for(auto [cur,id]:e[i]){
			mp[cur].pb(id);
		}
		for(auto [cur,id]:q[i]){
			auto it=mp.lower_bound(cur);
			if(it==mp.end()){
				cout<<"No\n";
				return 0;
			}
			ans[id]=it->se.back();
			it->se.pop_back();
			if(it->se.empty()) mp.erase(it);
		}
	}
	cout<<"Yes\n";
	rep(i,1,n) cout<<ans[i]<<" ";
	cout<<'\n';
	return 0;
}