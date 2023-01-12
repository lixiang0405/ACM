/*有 n 堆石子排成一排，第 i 堆石子有 ai 颗，每次我们可以选择相邻的两堆石子合并，代价是两堆石子数目的和，

现在我们要一直合并这些石子，使得最后只剩下一堆石子，问总代价最少是多少？*/

//记忆化

int dp[N][N],a[N],tot[N],n;

int solve(int l,int r){
	if(dp[l][r]!=-1) return dp[l][r];
	int ans=inf;
	if(l==r) return dp[l][r]=0;
	for(int i=l;i<=r-1;++i){
		ans=min(ans,solve(l,i)+solve(i+1,r)+tot[r]-tot[l-1]);
	}
	return dp[l][r]=ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;++i)
	tot[i]+=tot[i-1]+a[i];
	printf("%d",solve(1,n));
    return 0;
}

//dp
int dp[N][N],a[N],tot[N],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	tot[i]+=tot[i-1]+a[i];
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<=n;++i) dp[i][i]=0;
	for(int l=1;l<n;++l){
		for(int i=1;i<=n-l;++i){
			for(int j=i;j<=i+l-1;++j){
				dp[i][i+l]=min(dp[i][i+l],dp[i][j]+dp[j+1][i+l]+tot[i+l]-tot[i-1]);
			}
		}
	}
	printf("%d",dp[1][n]);
    return 0;
}