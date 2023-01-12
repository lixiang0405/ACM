/*给你一个 n(1≤n≤2000) 个点的有根树，其中1号点为根。每个点有一个权值ai(−105≤ai≤105)，权值可能是负数。

你需要回答 q(1≤q≤105) 个询问，在 u 的子树中，

选择一个大小恰好为 m(1≤m≤n) 的包含 u 点的连通块，最大的权值和。保证 m 不会超过 u 的子树大小。*/

int n,m,a[N],dp[N][N],sz[N];
vector<int> e[N];

void dfs(int u){
    sz[u]=0;
    static int tmp[N];
    for(auto v:e[u]){
        dfs(v);
        for(int i=1;i<=sz[v]+sz[u];++i)
        tmp[i]=-inf;
        for(int i=0;i<=sz[u];++i)
        for(int j=0;j<=sz[v];++j)
        tmp[i+j]=max(tmp[i+j],dp[u][i]+dp[v][j]);
        sz[u]+=sz[v];
        for(int i=1;i<=sz[u];++i)
        dp[u][i]=tmp[i];
    }
    sz[u]++;
    for(int i=sz[u];i>=1;--i)
    dp[u][i]=dp[u][i-1]+a[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //memset(dp,-inf,sizeof(dp));
	scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i){
        int x;
        scanf("%d",&x);
        e[x].push_back(i);
    }
    for(int i=1;i<=n;++i)
    scanf("%d",&a[i]);
    dfs(1);
    for(int i=1;i<=m;++i){
        int u,x;
        scanf("%d%d",&u,&x);
        printf("%d\n",dp[u][x]);
    }
	return 0;
}