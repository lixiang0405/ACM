/*
给一个n个点m条边的无向连通图，从小到大输出所有割点的编号。
*/

int n,m,sz=0,idx=0;
int dfn[N],low[N],cut[N];
vector<int> e[N];

void dfs(int u,int fa){
	dfn[u]=low[u]=++idx;
	int x=0;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v,u);
			x++;
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]) cut[u]=1;
		}else if(v!=fa) low[u]=min(low[u],dfn[v]);
	}
	if(u==1&&x<=1) cut[u]=0;
	sz+=cut[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	printf("%d\n",sz);
	for(int i=1;i<=n;++i)
		if(cut[i]) printf("%d ",i);
	return 0;
}