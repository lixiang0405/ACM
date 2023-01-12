/*
给你一个n个点的树。一开始第i个点上有ai只蝴蝶
每次到达一个顶点可以抓到这个点的所有蝴蝶，但一旦到达一个点，所有它
相邻的顶点的蝴蝶都会被惊动，如何一个蝴蝶在t'时刻被惊动，那么它会在t'+ti时刻飞走
(1=<ti<=3)
在0时刻你到达了一号节点，在接下来每个时刻，你可以移动到一个相邻点，并停留到下一时刻开始。
问最后最多能抓几只蝴蝶。
*/

int t,p[N],fa[N];
ll a[N],dp[N][2];
vector<int> e[N];

void dfs(int u){
	ll maxx=0;
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
		dp[u][0]+=dp[v][0];
		maxx=max(maxx,a[v]);
	}
	dp[u][1]=dp[u][0]+a[u];
	pair<int,ll> b(-1e18,0),c(-1e18,0);
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		if(c.first<dp[v][1]){
			swap(c,b);
			c.first=dp[v][1];
			c.second=v;
		}else if(b.first<dp[v][1]){
			b.first=dp[v][1];
			b.second=v;
		}
	}
	ll res=0;
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		if(p[v]==3){
			if(v!=c.second)
				res=max(res,dp[u][0]+a[v]+c.first);
			else res=max(res,dp[u][0]+a[v]+b.first);
		}
	}
	dp[u][0]+=maxx;
	dp[u][0]=max(res,dp[u][0]);
	dp[u][1]-=dp[u][0];
}

void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) dp[i][0]=0,dp[i][1]=0,e[i].clear(),fa[i]=0;
	for(int i=1;i<=n;++i) scanf("%lld",a+i);
	for(int i=1;i<=n;++i) scanf("%d",p+i);
	for(int i=1;i<=n-1;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	printf("%lld\n",dp[1][0]+a[1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
	while(t--){
		solve();
	}
	return 0;
}