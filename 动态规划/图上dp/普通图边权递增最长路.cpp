/*
Pashmak 的作业是关于图表的问题。
虽然他总是努力把功课做的很彻底，但是他解决不了这个问题。
如您所知，他在图论方面确实很弱。
所以试着帮助他解决问题。
给定一个带 n 个顶点和 m 个边的加权有向图。
您需要找到具有最大边数的路径（也许是非简单路径），以便边的权重沿路径增加。
换句话说，路径的每条边的权重必须严格大于路径中的前一条边。
帮助 Pashmak，打印所需路径中的边数。
*/

int n,m;
vector<pii> e[N];
int dp[N],tmp[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[w].push_back({u,v});
	}
	int ans=0;
	for(int i=1;i<=3e5;++i){
		for(auto [u,v]:e[i]){
			tmp[v]=max({tmp[v],dp[v],dp[u]+1});
		}
		for(auto [u,v]:e[i]){
			dp[v]=tmp[v];
			ans=max(ans,dp[v]);
		}
	}
	printf("%d",ans);
	return 0;
}