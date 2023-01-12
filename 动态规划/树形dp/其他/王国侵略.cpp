/*
	根节点1有无数个军队，
	军队每移动一格到相邻的点需要付出1的代价，
	问军队经过所有点的最小代价
*/
int dp[N][2],dep[N],t;
vector<int> e[N];

void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=dep[u];
	for(auto v:e[u]){
		dep[v]=dep[u]+1;
		dfs(v);
		dp[u][1]=min({dp[u][1]+dp[v][1],dp[u][1]+dp[v][0]+2,dp[u][0]+dp[v][1]});
		dp[u][0]+=dp[v][0]+2;
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
	dfs(1);
	printf("%d\n",min(dp[1][0],dp[1][1]));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
	int cnt=1;
	while(t--){
		printf("Case #%d: ",cnt);
		cnt++;
		solve();
	}
	return 0;
}