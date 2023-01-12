/*
ICPCNanjing 2020 M , Monster Hunter 

给你一个 n (1≤ n ≤2000）个点的有根树。一开始在第1个点上有个血量为 hpi的怪物。

如果你想要消灭所有的怪物。一个怪物只有当它的父亲被消灭了オ能被消灭。消灭第 i 个怪物需要用到的力量为这个怪物和它所有未被消灭的儿子（直接儿子）的 hp 总和。
你可以使用 m 次魔法，使用一次魔法你就可以没有额外限制的用 O 的力量消灭一个点的怪物。你希
望使用魔法，使得消灭剩下点的力量之和最小。

切输出 m =0,1,2,…, n 的答案。*/

int a[N],sz[N],t;
vector<int> e[N];
ll dp[N][N][2];

void dfs(int u,int fa){
	sz[u]=1;
	static ll tmp[N][2];
	dp[u][0][1]=inf;
	dp[u][1][1]=0;
	dp[u][1][0]=inf;
	dp[u][0][0]=a[u];
	for(auto v:e[u]){
		if(v==fa) continue;
		dfs(v,u);
		for(int i=0;i<=sz[u]+sz[v];++i){
			tmp[i][0]=tmp[i][1]=inf;
		}
		for(int i=0;i<=sz[u];++i){
			for(int j=0;j<=sz[v];++j){
				tmp[i+j][0]=min(dp[u][i][0]+min(dp[v][j][0]+a[v],dp[v][j][1]),tmp[i+j][0]);
				tmp[i+j][1]=min(dp[u][i][1]+min(dp[v][j][0],dp[v][j][1]),tmp[i+j][1]);
			}
		}
		sz[u]+=sz[v];
		for(int i=0;i<=sz[u];++i) dp[u][i][0]=tmp[i][0],dp[u][i][1]=tmp[i][1];
	}
}

void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) e[i].clear();
	for(int i=2;i<=n;++i){
		int u;
		scanf("%d",&u);
		e[u].push_back(i);
	} 
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	dfs(1,0);
	for(int i=0;i<=n;++i){
		printf("%lld",min(dp[1][i][0],dp[1][i][1]));
		printf("%c"," \n"[i==n]);
	}
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