/*
有n个点m条边无向连通图的图，保证没有重边和自环。对于每个点，
输出将这个点的所有边删除之后，有多少点对不能互相连通。
这里的点对是有顺序的，也就是(u,v)和(v,u)需要被统计两次。
*/

int n,m,idx=0;
int dfn[N],low[N];
vector<int> e[N];
ll ans[N],sz[N];

void dfs(int u,int fa){
	dfn[u]=low[u]=++idx;
	sz[u]=1;
	ans[u]=n-1;
	//第一个数取u，任取
	ll cut=n-1;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v,u);
			sz[u]+=sz[v];
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){ 
				//是割点，第一个数在子树sz[v]任取，另一个数在其他地方任取
				ans[u]+=sz[v]*(n-sz[v]);
				cut-=sz[v];
			}
		}else if(v!=fa) low[u]=min(low[u],dfn[v]);
	}
	//最后剩下来的连通块也要加上
	ans[u]+=cut*(n-cut);
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
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
	return 0;
}