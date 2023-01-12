/*
给出一个 n 点 m 边的有向无环图，你需要从中移除一些边，

使得对于每一个点，其入度减少（如果原来有入边），出度也减少（如果原来有出边）。

当删完边以后，如果有一个点集，满足对于任两点（i, j）

可以从 i 走到 j 或可以从 j 走到 i，那就称其为可爱的。

现在要构造一种删边方案，使得删边后其中一个可爱的点集最大，

输出这个点集大小。

输入数据第一行由两个正整数 n, m 组成，代表 n 个点和 m 条边。第 2 至 m + 1 行包含两个数 u, v，分别表示一条有向边的两个顶点。
*/

int n,m,idx=0;
int dep[N],tp[N],dp[N],in[N],out[N];
vector<int> e[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		dep[v]++;
		in[v]++;
		out[u]++;
	}
	queue<int> q;
	for(int i=1;i<=n;++i)
		if(dep[i]==0) q.push(i),tp[++idx]=i;
	while(!q.empty()){
		auto u=q.front();
		q.pop();
		for(auto v:e[u]){
			dep[v]--;
			if(dep[v]==0){
				tp[++idx]=v;
				q.push(v);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		if(out[tp[i]]>=2)
			for(auto v:e[tp[i]]){
				if(in[v]>=2){
					dp[v]=max(dp[tp[i]]+1,dp[v]);
					ans=max(ans,dp[v]);
				}
			}
	}
	cout<<ans+1<<endl;
	return 0;
}