/*给你 N 颗宝石，每颗宝石都有重量和价值。要你从这些宝石中选取一些宝石

保证总重量不超过 W，且总价值最大为，并输出最大的总价值。

输入文件中包含多组数据。每组数据的格式如下：

第一行是两个正整数 n(1≤n≤100) 和W(1≤W<2^30)，分别表示宝石的数目和最多能带走的宝石重量。

接下来的 n 行，每行有两个正整数 weighti 和 valuei,(1≤weighti≤2^30,0≤valuei≤2^30)，

分别表示第 i 颗宝石的重量和价值，且保证 weighti 能写成 a×2^b(1≤a≤20,0≤b≤30) 的形式。同一行的两个正整数之间用空格隔开。

最后一组数据的后面有两个 −1，表示文件的结束。这两个 −1 并不代表一组数据，

你不需对这组数据输出结果。并且输入文件中数据的组数不超过 20 。*/

int n,W;
vector<pair<int,int>> it[40];
ll g[N],dp[N];

void solve(){
    int s=0;
    for(int i=0;i<=31;++i) it[i].clear();
    for(int i=1;i<=n;++i){
        int w,v;
        scanf("%d%d",&w,&v);
        int ctz=__builtin_ctz(w);
        w>>=ctz;
        it[ctz].push_back({w,v});
        s+=w;
    }
    for(int i=0;i<=s;++i) dp[i]=-inf;
    dp[0]=0;
    for(int i=30;i>=0;--i){
        for(int j=0;j<=s;++j) g[j]=dp[j],dp[j]=-inf;
        int w=(W>>i)&1;
        for(int j=0;j<=s;++j)
        dp[min(j*2+w,s)]=max(dp[min(j*2+w,s)],g[j]);
        for(int j=s-1;j>=0;--j) dp[j]=max(dp[j+1],dp[j]);
        for(auto &j:it[i]){
            for(int k=j.first;k<=s;++k)
            dp[k-j.first]=max(dp[k-j.first],dp[k]+j.second);
        }
    }
    printf("%lld\n",*max_element(dp,dp+s+1));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(scanf("%d%d",&n,&W),n!=-1&&W!=-1){
        solve();
    }
    return 0;
}