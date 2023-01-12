/*
有n种物品要放到一个袋子里，袋子的总容量为m，我们一共有k点体力值。
第i种物品的体积为vi，把它放进袋子里会获得wi的收益，
并且消耗我们ti点体力值，每种物品只能取一次。问如何选择物品，
使得在物品的总体积不超过m并且花费总体力不超过k的情况下，
获得最大的收益？请求出最大收益。
*/

int n,m,ans=0,cnt=0,k;
int v[N],w[N],t[N],dp[N][N][N],g[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		scanf("%d%d%d",&v[i],&w[i],&t[i]);
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<=m;++j)
			for(int f=0;f<=k;++f){
				if(j>=v[i]&&f>=t[i])
				dp[i][j][f]=max(dp[i-1][j][f],dp[i-1][j-v[i]][f-t[i]]+w[i]);
				else dp[i][j][f]=dp[i-1][j][f];
				
			}
	}
	printf("%d",dp[n][m][k]);
    return 0;
}