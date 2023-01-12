/*喜欢吃麦当劳的蜗蜗要在学校呆 n 天，如果第 i 天蜗蜗吃到了麦当劳，他可以获得 ai 点快乐值。

然而蜗蜗不能吃太多麦当劳，在连续的 m 天中，他最多只能有一半的天数吃麦当劳。

请问蜗蜗在这 n 天中最多可以得到多少快乐值？*/

int n,m;
ll dp[1<<M],g[1<<M],ans=0,a[N];
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	scanf("%lld",&a[i]);
	for(int i=1;i<(1<<m);++i){
		int c=__builtin_popcount(i);
		if(c>m/2) continue;
		int b=__builtin_ctz(i);
		dp[i]=dp[i-(1<<b)]+a[b];
		ans=max(ans,dp[i]);
	}
	for(int i=m;i<n;++i){
		for(int j=0;j<(1<<m);++j){
			g[j]=dp[j],dp[j]=0;
		}
		for(int j=0;j<(1<<m);++j){
			int c=__builtin_popcount(j);
			if(c>m/2) continue;
			if(j&(1<<(m-1))){
				dp[j]=a[i]+max(g[((j-(1<<(m-1)))<<1)+1],g[((j-(1<<(m-1)))<<1)]);
			}else{
				dp[j]=max(g[(j<<1)+1],g[(j<<1)]);
			}
			ans=max(dp[j],ans);
		}
	}
	printf("%lld",ans);
	return 0;
}