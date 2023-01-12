int n,par[N][M+1],dep[N];
vector<int> e[N];

void dfs(int u,int f){
	dep[u]=dep[f]+1;
	for(auto v:e[u]){
		if(v==f) continue;
		par[v][0]=u;
		dfs(v,u);
	}
}

int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	int d=dep[v]-dep[u];
	for(int i=M;i>=0;--i){
		if(d&(1<<i)){
			v=par[v][i];
		}
	}
	if(u==v)
		return u;
	for(int i=M;i>=0;--i){
		if(par[u][i]!=par[v][i]){
			u=par[u][i],v=par[v][i];
		}
	}
	return par[u][0];
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

	dfs(1,0);
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=par[par[u][i-1]][i-1];
		}
	}
	
	return 0;
} 