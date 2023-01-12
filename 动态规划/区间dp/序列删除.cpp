//有 n 个数字 a1,a2,…,an，我们要把除了 a1,an 之外的其他数字删除，
//删除一个数字的代价是它乘上它相邻两个还没有被删除的数字的值，
//请求出最小代价是多少。

//dp
int dp[N][N],a[N],tot[N],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=2;i<=n-1;++i) dp[i][i]=a[i-1]*a[i+1]*a[i];
	for(int l=1;l<n-1;++l){
		for(int i=2;i<=n-l-1;++i){
			for(int j=i;j<=i+l;++j){
				if(i>j-1) dp[i][j-1]=0;
				if(j+1>i+l) dp[j+1][i+l]=0;//i=2,j=4,l=2
				dp[i][i+l]=min(dp[i][i+l],dp[i][j-1]+dp[j+1][i+l]+a[j]*a[i-1]*a[i+l+1]);
				//cout<<i<<" "<<i+l<<" "<<dp[i][i+l]<<" "<<i<<" "<<j<<endl;
			}
			//cout<<i<<" "<<i+l<<" "<<dp[i][i+l]<<endl;
		}
	}
	printf("%d",dp[2][n-1]);
    return 0;
}