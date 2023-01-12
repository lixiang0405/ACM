给定一个长度为 n 的数组 a1,a2,…,an 以及一个长度为 m 的数组 b1,b2,…,bm，问 a 和 b 的最长公共子序列的长度。

也就是说，我们要找到最大的 k 以及数组 p1,p2,…,pk，数组 l1,l2,…,lk 满足 1≤p1<p2<⋯<pk≤n 并且 1≤l1<l2<⋯<lk≤m 并且对于所有的 i(1≤i≤k) ，api=bli。

int a[N],b[N],n,m;
int dp[N][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=m;++i) scanf("%d",&b[i]);
    dp[0][0]=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            dp[i][j]=max({dp[i][j-1],dp[i-1][j-1]+(a[i]==b[j]),dp[i-1][j]});
        }
    }
    printf("%d",dp[n][m]);
    return 0;
}