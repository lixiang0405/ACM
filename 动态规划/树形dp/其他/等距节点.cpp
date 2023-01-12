/*
树是一个没有圈的无向连通图。
给你一棵由n个顶点组成的树。找到在该树中精确选择k个顶点的方法的数量（i。 e、 顶点的k元素子集），
使选定顶点之间的所有成对距离相等
（换句话说，存在一个整数c，使得对于所有u，v（u≠v、 u，v在选定顶点中）du，v=c，其中du，v是从u到v的距离）。
由于答案可能非常大，您需要将其输出为模1e9+7。
*/


int t,g[N][N],cnt[N];
ll dp[N];

void solve(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) g[i][j]=(i==j)?0:mod;
	}
	for(int i=1;i<=n-1;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u][v]=g[v][u]=1;
	}
	if(k==2){
		printf("%lld\n",(ll)n*(n-1)/2);
		return;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int p=1;p<=n;++p){
				g[i][j]=min(g[i][j],g[i][p]+g[p][j]);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		for(int d=1;d<=n;++d){
			for(int j=1;j<=n;++j) cnt[j]=0;
			for(int u=1;u<=n;++u){
				if(g[i][u]==d){
					for(int v=1;v<=n;++v){
						if(g[i][v]==1&&g[i][v]+g[v][u]==d){
							cnt[v]++;
						}
					}
				}
			}
			for(int j=1;j<=k;++j) dp[j]=0;
			dp[0]=1;
			for(int u=1;u<=n;++u){
				if(cnt[u]){
					for(int j=k;j>=1;--j) dp[j]=(dp[j-1]*cnt[u]%mod+dp[j])%mod;
				}
			}
			ans=(ans+dp[k])%mod;
		}
	}
	printf("%d\n",ans);
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