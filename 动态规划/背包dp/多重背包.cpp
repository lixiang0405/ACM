/*
有n种物品要放到一个袋子里，袋子的总容量为m，
第i种物品的体积为vi，把它放进袋子里会获得wi的收益，
可以用li次。问如何选择物品，使得在物品的总体积不超过m的情况下，
获得最大的收益？请求出最大收益。
*/

//O(nm)

int n,m,val[N],w[N],dp[N],ans=0,l[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&w[i],&val[i],&l[i]);
	for(int i=1;i<=n;++i){//2^k-1
		int len=31-__builtin_clz(l[i]+1),c=1;
		for(int k=1;c<=len&&k*w[i]<=m;k*=2,c++){
			for(int j=m;j>=k*w[i];--j){
				dp[j]=max(dp[j],dp[j-k*w[i]]+val[i]*k);
			}
		}
		int last=l[i]-pow(2,len)+1;
		for(int j=m;j>=last*w[i];--j){
			dp[j]=max(dp[j],dp[j-last*w[i]]+val[i]*last);
		}
	}
	printf("%d",dp[m]);
    return 0;
}


//O(nmlog(l))

int n,m,val[N],w[N],dp[N],ans=0,l[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&w[i],&val[i],&l[i]);
	for(int i=1;i<=n;++i){//2^k-1
		int len=31-__builtin_clz(l[i]+1),c=1;
		for(int k=1;c<=len&&k*w[i]<=m;k*=2,c++){
			for(int j=m;j>=k*w[i];--j){
				dp[j]=max(dp[j],dp[j-k*w[i]]+val[i]*k);
				ans=max(ans,dp[j]);
			}
		}
		int last=l[i]-pow(2,len)+1;
		for(int j=m;j>=last*w[i];--j){
			dp[j]=max(dp[j],dp[j-last*w[i]]+val[i]*last);
			ans=max(ans,dp[j]);	
		}
	}
	printf("%d",ans);
    return 0;
}

//在完全背包3.0的基础上
//每件物品有l 个，相当于多了若干件物品的01背包
//其实可以把l 件物品当作若干件新的物品这样就成为了新的01背包，但时间比较慢
//
//考虑将多出来的物品分为l[i] = 1件 + 2件 + 4件 + 8件 + 16件 + 32件 + ... + 剩余部分
//（所有数都可以被分为x = 1 + 2 + 4 + 8 + 16 + ... 的形式）
//
//把分开的每件物品，作为一件新的物品，对这件物品就像之前背包一样状态转移方程
//这样就相当于把l[i] 变成log l[i] 件物品
//
//（n * log l[i] 件物品，推导n * log l[i] 次，
//  f[j] 代表当前j 容量的背包下，放入i 个物品所能得到的最大价值）


//O(nml)

int n,m,val[N],w[N],dp[N],ans=0,l[N],g[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d%d",&w[i],&val[i],&l[i]);
	for(int i=1;i<=n;++i){
		for(int k=1;k<=l[i];++k){
			for(int j=1;j<=m;++j){
				g[j]=dp[j];
				dp[j]=0;
			}
			for(int j=1;j<=m;++j){
				if(j>=w[i]) dp[j]=max(g[j-w[i]]+val[i],g[j]);
				else dp[j]=g[j];
				ans=max(ans,dp[j]);
			}
		}
	}
	printf("%d",ans);
    return 0;
}