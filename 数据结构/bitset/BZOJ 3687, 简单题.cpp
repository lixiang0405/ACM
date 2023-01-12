/*
给你 n 个数 a1,a2,…,an，问所有子集的和的异或和是多少。
第一行一个整数 n(n≤1000)。
接下来一行，一共 n 个正整数 a1,a2,…,an(∑ai≤2×106)。
*/

bitset<2000001> dp;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    dp[0]=1;
    int n;
    scanf("%d",&n);
    //dp[i][j+a[i]]=(dp[i-1][j+a[i]]+dp[i-1][j])%2;
    rep(i,0,n){
        int x;
        scanf("%d",&x);
        dp=dp^(dp<<x);
    }
    int ans=0;
    rep(i,0,2000001){
        if(dp[i])
            ans^=i;
    }
    printf("%d",ans);
    return 0;
}