/*
有n种物品要放到一个袋子里，袋子的总容量为m，第i种物品的体积为vi，
把它放进袋子里会获得wi的收益，每种物品至多能用一次，问如何选择物品，
使得在物品的总体积不超过m的情况下，获得最大的收益？请求出最大收益。
*/

int n,m,val[N],w[N],dp[N][N],ans=0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&w[i],&val[i]);
	dp[0][0]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=m;++j){
			if(j>=w[i])
			dp[i][j]=max(dp[i-1][j-w[i]]+val[i],dp[i-1][j]);
			else dp[i][j]=dp[i-1][j];
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
			ans=max(ans,dp[i][j]);
		}
	}
	printf("%d",ans);
    return 0;
}