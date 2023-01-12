/*蜗蜗的世界里有 n 个城市，城市两两之间通过高速公路连接，从第 i 个城市走到第 j 个城市需要花费 ai,j 的时间。

现在蜗蜗想从 1 号城市出发旅游，他想把每个城市都玩个遍，但又不想在一个城市玩两遍，

玩完以后蜗蜗需要回到 1 号城市应付期末考试。请问蜗蜗最少需要花费多少时间？

蜗蜗到了一个城市以后，一定会在这个城市游玩。蜗蜗在出发之前会先在 1 号城市游玩。

连接两个城市的高速公路不会经过其他城市。由于路况的原因，

从第 i 个城市走到第 j 个城市花费的时间不一定等于从第 j 个城市走到第 i 个城市花费的时间。*/

int dp[N][M],a[M][M],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			scanf("%d",&a[i][j]);
		}
	}
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<(1<<n);++i){
		int c=__builtin_popcount(i);
		if((i&1)&&c==2){
			for(int j=1;j<n;++j)
			if(i&(1<<j)) dp[i][j]=a[0][j];
		}
	}
	for(int i=1;i<(1<<n);++i){
		int c=__builtin_popcount(i);
		if(c<=2) continue;
		for(int j=1;j<n;++j){
			if(i&(1<<j)){
				int tmp=i-(1<<j);
				for(int k=1;k<n;++k){
					if(k==j) continue;
					if(i&(1<<k))
					dp[i][j]=min(dp[i][j],dp[tmp][k]+a[k][j]);
				}
			}
		}
	}
	int ans=1e9;
	for(int i=1;i<n;++i){
		ans=min(ans,dp[(1<<n)-1][i]+a[i][0]);
	}
	printf("%d",ans);
    return 0;
}