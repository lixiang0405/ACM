//给一个n个点m条边的图，输出所有的强连通分量。
 
int n,m,cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N];
stack<int> sk;
vector<int> e[N];
vector<vector<int>> scc;
 
void dfs(int u){
	dfn[u]=low[u]=++tot;
	sk.push(u);
	ins[u]=1;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else 
			if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		vector<int> c;
		while(1){
			int x=sk.top();
			c.push_back(x);
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			sz[cnt]++;
			if(x==u) break;
		}
		stable_sort(c.begin(),c.end());
		scc.push_back(c);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
		dfs(i);
	stable_sort(scc.begin(),scc.end());
	for(auto cur:scc){
		for(auto v:cur) printf("%d ",v);
		printf("\n");
	}
    return 0;
}