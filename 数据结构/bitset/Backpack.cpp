/*
Alice 有一个容量为 m 的背包，她现在想装一些物品！
Alice 有 n 个项目，每个项目都有一个体积 vi 和一个值 wi。
是否可以从 n 个项目中选择多个项目以使背包完全装满（即体积之和等于背包容量）？
如果是这样，当背包装满时，背包中物品的值的最大异或和是多少？
*/

int t;
bitset<1024> dp[2][N];
int v[N],w[N];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>v[i]>>w[i];
    for(int j=0;j<(1<<10);++j){
        dp[0][j].reset();
        dp[1][j].reset();
    }
    dp[0][0]=1;
    //for(int i=1;i<=n;++i){
	// 	for(int j=0;j<(1<<10);++j){
	// 		dp[i&1][j].reset();
	// 	}
	// 	for(int j=0;j<(1<<10);++j){
	// 		dp[i&1][j]|=dp[i&1^1][j];
	// 		dp[i&1][j^w[i]]|=dp[i&1^1][j]<<v[i];
	// 	}
	// }
    for(int i=1;i<=n;++i){
        for(int j=0;j<(1<<10);++j){
            dp[i&1][j].reset();
            dp[i&1][j]|=dp[i&1^1][j];
            dp[i&1][j]|=dp[i&1^1][j^w[i]]<<v[i];
        }
    }
    for(int i=(1<<10)-1;i>=0;--i){
        if(dp[n&1][i][m]){
            cout<<i<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
} 