/*有一棵 n 个点的树，每条边有一流量限制。令某一个点为根节点，向根节点灌水，最终从叶子节点流出的水量和为这一个点的最大流量，请求出每个点的最大流量。

输入格式
第一行一个整数 n 表示点的数目。

接下来 n−1 行，每行三个整数 x,y,z 描述一条连接 x,y 的流量限制为 z 的树边。*/

int n,fa[N];
vector<pair<int,ll>> e[N];
ll dp[N],dp2[N],ans[N];

ll dfs(int u){
	ll cnt=0;
	for(auto [v,w]:e[u]){
		if(v==fa[u]) continue;
		fa[v]=u;
		cnt+=min(dfs(v),w);
	}
	return 	dp[u]=(cnt?cnt:1e9);
}

void dfs2(int u,ll w2){
	int m=e[u].size();
    for(int i=1;i<=m;++i){
		auto [v,w]=e[u][i-1];
		if(v==fa[u]) continue;
        dp2[v]=dp[u]-min(dp[v],w); 
        if(u!=1) dp2[v]+=min(dp2[u],w2);
		else if(e[u].size()==1) dp2[v]=w;//注意：根节点是1的时候到v流为w而不是0！！！
		dp2[v]=min(dp2[v],w);
    }//dp2[v]表示以v点为根把树倒过来
    for(auto [v,w]:e[u]){
		if(v==fa[u]) continue;
		if(e[v].size()==1)
		ans[v]=dp2[v];
		else
        ans[v]=dp[v]+dp2[v];//为什么要加一:因为dp2[v]表示的是所有u子树的连通块
        dfs2(v,w);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs(1);
	dfs2(1,0);
	ans[1]=dp[1];
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
    return 0;
}