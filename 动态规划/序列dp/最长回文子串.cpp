给定一个长度为 n 的数组 a1,a2,…,an，问其中的最长回文子串长度。

定义子串 al,al+1,…,ar 为回文子串，当且仅当这个子串正着看和反着看是一样的，即有 al=ar,al+1=ar−1,…。

int a[N],n,ans=0;
int dp[N][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=i;++j){
            if(a[i]==a[j]){
                if(i-j<=2) dp[i][j]=max(i-j+1,dp[i-1][j]);
                else if(dp[i-1][j+1]==i-j-1) dp[i][j]=max(dp[i-1][j+1]+2,dp[i-1][j]);
                ans=max(ans,dp[i][j]);
            }else dp[i][j]=dp[i-1][j];
        }
    }
    printf("%d",ans);
    return 0;
}