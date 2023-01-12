/*一家公司里有 n 个员工，除了公司 CEO 外，每个人都有一个直接上司。

今天公司要办一个舞会，为了大家玩得尽兴，如果某个员工的直接上司来了，他/她就不想来了。

第 i 个员工来参加舞会会为大家带来 ai 点快乐值。

由于场地有大小限制，场地最多只能容纳 m 个人。请求出快乐值最大是多少。*/

int n,m,a[N],dp[N][N][2];
vector<int> e[N];

void dfs(int u){
	dp[u][1][1]=a[u],dp[u][0][0]=0;
	for(auto v:e[u]){
		dfs(v);
		for(int i=m;i>=1;--i){
			for(int j=0;j<=i;++j){
				dp[u][i][0]=max(dp[u][i][0],dp[u][j][0]+max(dp[v][i-j][0],dp[v][i-j][1]));
				dp[u][i][1]=max(dp[u][i][1],dp[u][j][1]+dp[v][i-j][0]);
			}
		}
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;++i){
		int u;
		scanf("%d",&u);
		e[u].push_back(i);
	}
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	dfs(1);
	printf("%d",max(dp[1][m][0],dp[1][m][1]));
    return 0;
}