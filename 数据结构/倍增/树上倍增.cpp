/*给一棵n个点的树，每条边上有边权。

给q个询问u,v，每次询问路径u,v上的最小值。*/

int n,q,par[N][M+1],val[N][M+1],depth[N];
vector<pair<int,int>> e[N];

void dfs(int u,int f){
	depth[u]=depth[f]+1;
	for(auto p:e[u]){
		int v=p.first;
		if(v==f) continue;
		par[v][0]=u;
		val[v][0]=p.second;
		dfs(v,u);
	}
}

int query(int u,int v){
	int ans=1<<30;
	if(depth[u]>depth[v]) swap(u,v);
	int d=depth[v]-depth[u];
	for(int i=M;i>=0;--i){
		if(d&(1<<i)){
			ans=min(ans,val[v][i]);
			v=par[v][i];
		}
	}
	if(u==v)
	return ans;
	for(int i=M;i>=0;--i){
		if(par[u][i]!=par[v][i]){
			ans=min({ans,val[u][i],val[v][i]});
			u=par[u][i],v=par[v][i];
		}
	}
	ans=min({ans,val[u][0],val[v][0]});
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&q);
	for(int i=0;i<n-1;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs(1,0);
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=par[par[u][i-1]][i-1];
			val[u][i]=min(val[par[u][i-1]][i-1],val[u][i-1]);
		}
	}
	for(int i=0;i<q;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",query(u,v));
	}
    return 0;
}
