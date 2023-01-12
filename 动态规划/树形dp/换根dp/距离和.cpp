/*有一棵 n 个点的树，请求出每个点到其他所有点的距离的和。

定义两个点的距离为它们的简单路径上经过了多少条边。*/

int n,fa[N],sz[N];
vector<int> e[N];
ll dp[N],dp2[N],ans[N];

ll dfs(int u){
	ll cnt=0;
	sz[u]=0;
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		fa[v]=u;
		cnt+=dfs(v);
		sz[u]+=sz[v];
	}
	sz[u]++;
	dp[u]=cnt;
	return cnt+sz[u];
}

void dfs2(int u){
	int m=e[u].size();
    if(m==0) return;
    for(int i=1;i<=m;++i){
		int v=e[u][i-1];
		if(v==fa[u]) continue;
        dp2[v]=dp[u]-dp[v]-sz[v]+sz[u]-sz[v]; 
        if(u!=1) dp2[v]+=dp2[u]+sz[1]-sz[u];//此时dp2[u]将树倒过来的v的一棵子树
    }//dp2[v]表示以v点为根把树倒过来
    for(auto v:e[u]){
		if(v==fa[u]) continue;
        ans[v]=dp[v]+dp2[v];//为什么要加一:因为dp2[v]表示的是所有u子树的连通块
        dfs2(v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	dfs2(1);
	ans[1]=dp[1];
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
    return 0;
}