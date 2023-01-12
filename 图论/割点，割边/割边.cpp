//给一个n个点m条边的无向连通图，从小到大输出所有割边的编号。注意：边从1开始标号。

int n,m,idx=0;
int dfn[N],low[N];
vector<pii> e[N];
vector<int> bridge;

void dfs(int u,int fa){
	dfn[u]=low[u]=++idx;
	for(auto [v,f]:e[u]){
		if(!dfn[v]) dfs(v,f);
		if(f!=fa) low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]&&fa!=-1){
		bridge.push_back(fa);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back({v,i});
		e[v].push_back({u,i});
	}
	dfs(1,-1);
	stable_sort(bridge.begin(),bridge.end());
	printf("%d\n",bridge.size());
	for(auto cur:bridge) printf("%d ",cur);
    return 0;
}