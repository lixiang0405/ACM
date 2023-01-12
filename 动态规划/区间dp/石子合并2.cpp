/*有 n 堆石子围成一个圈，第 i 堆石子有 ai 颗，每次我们可以选择相邻的两堆石子合并，

代价是两堆石子数目的和，现在我们要一直合并这些石子，使得最后只剩下一堆石子，问总代价最少是多少？*/

//dp
int dp[N][N],a[N],tot[N],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=n+1;i<=n*2;++i) a[i]=a[i-n];
	for(int i=1;i<=n*2;++i)
	tot[i]+=tot[i-1]+a[i];
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<=n*2;++i) dp[i][i]=0;
	for(int l=1;l<n;++l){
		for(int i=1;i<=2*n-l;++i){
			for(int j=i;j<=i+l-1;++j){
				dp[i][i+l]=min(dp[i][i+l],dp[i][j]+dp[j+1][i+l]+tot[i+l]-tot[i-1]);
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;++i) ans=min(ans,dp[i][i+n-1]);
	printf("%d",ans);
    return 0;
}