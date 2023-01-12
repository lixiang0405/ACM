/*
有n种物品要放到一个袋子里，袋子的总容量为m。
第i个物品属于第ai组，每组物品我们只能从中选择一个。
第i种物品的体积为vi，把它放进袋子里会获得wi的收益。问如何选择物品，
使得在物品的总体积不超过m的情况下，获得最大的收益？请求出最大收益。
*/

int n,m,ans=0,cnt=0;
int v[N],w[N],dp[N],g[N];
vector<int> a[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		int id;
		scanf("%d%d%d",&id,&v[i],&w[i]);
		cnt=max(cnt,id);
		a[id].push_back(i);
	}
	for(int i=1;i<=cnt;++i){
		if(a[i].empty()) continue;
		for(int j=1;j<=m;++j) g[j]=dp[j],dp[j]=0;
		for(auto cur:a[i]){
			for(int j=v[cur];j<=m;++j){
				dp[j]=max({dp[j],g[j],g[j-v[cur]]+w[cur]});
				ans=max(ans,dp[j]);
			}
		}
		for(int j=1;j<=m;++j) dp[j]=max(dp[j],g[j]);
	}
	printf("%d",ans);
    return 0;
}