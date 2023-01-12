/*给你一个 n(1≤n≤1000) 个点的有根树，其中1号点为根。每个点有一个权值 ai(1≤ai≤105) 和重量 wi(1≤wi≤104)。

你需要选择一个重量恰好 k 的包含根的连通块，最大的权值和。

对所有的k=0,1,2,…,m输出答案，其中 1≤m≤104 。如果不存在，输出0。*/

int n,m,a[N],dp[N][M+5],w[N];
int l[N],r[N],tot,id[N];
vector<int> e[N];

void dfs(int u){
    l[u]=++tot;
    id[tot]=u;
    for(auto v:e[u]){
        dfs(v);
    }
    r[u]=tot;
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
    for(int i=1;i<=n;++i)
    scanf("%d",&w[i]);
    dfs(1);
    for(int i=1;i<=m;++i) dp[n+1][i]=-inf;
    for(int i=n;i>=1;--i){
        int u=id[i];
        for(int j=0;j<=m;++j){
            dp[i][j]=dp[r[u]+1][j];
            if(j-w[u]>=0)
            dp[i][j]=max(dp[i+1][j-w[u]]+a[u],dp[i][j]);
        }
    }
    for(int i=0;i<=m;++i){
        if(dp[1][i]<0)
        printf("0\n");
        else
        printf("%d\n",dp[1][i]);
    }
	return 0;
}