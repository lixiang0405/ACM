/*
有 N 张卡，编号为 1,...,N。卡 i 有 Pi写在前面和Qi写在背面。
这里，P=(P1,...,PN),Q=(Q1,...,QN)是(1,2,…,N) 的排列。
有多少种方法可以选择满足以下条件的一些N卡？
找到计数模 998244353。
条件：每个数字 1,2,...,N 至少写在一张所选卡片上。
*/

struct DSU {
    vector<int> fa, sz;
	int n;
    DSU(int n) : fa(n+1), sz(n+1, 1),n(n){ 
		for(int i=0 ; i<=n ; ++i) fa[i] = i;    
    }
    int find(int x) {
        /*while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;*/
        return fa[x]==x?x:fa[x]=find(fa[x]);
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) { return sz[find(x)]; }
	int size(){
		set<int> st; 
		for(int i=1;i<=n;++i){
			st.insert(find(i));
		}
		return st.size();
	}
};

//一个n个点的环上在保证切出来的点集大小都大于1切任意刀，问有多少种切法
int n,a[N],b[N];
ll dp[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	dp[1]=1;
	dp[2]=3;
	for(int i=3;i<=2e5;++i){
		dp[i]=(dp[i-1]+dp[i-2])%mod;
		//cout<<i<<" "<<dp[i]<<endl;
	}
	cin>>n;
	DSU d(n);
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
	}
	for(int i=1;i<=n;++i){
		if(d.find(a[i])!=d.find(b[i])){
			d.merge(a[i],b[i]);
		}
	}
	vector<int> vt;
	for(int i=1;i<=n;++i){
		if(d.find(i)==i){
			vt.push_back(d.size(i));
		}
	}
	ll ans=1;
	for(auto cur:vt){
		ans=ans*dp[cur]%mod;
	}
	cout<<ans<<endl;
	return 0;
} 