/*
给一个n个点m条边的无向连通图，问最少添加多少条边使得成为一个边双连通图。
*/

int n,m,idx=0,cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N];
vector<pii> e[N];
stack<int> sk;
vector<int> cc[N];

void dfs(int u,int fa){
	dfn[u]=low[u]=++idx;
	sk.push(u);
	ins[u]=1;
	for(auto [v,f]:e[u]){
		if(!dfn[v]) dfs(v,f);
		if(f!=fa) low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(1){
			int x=sk.top();
			sk.pop();
			cc[cnt].push_back(x);
			bel[x]=cnt;
			ins[x]=0;
			if(x==u) break;
		}
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
	int nleaf=0;
	for(int i=1;i<=cnt;++i){
		int c=0;
		for(auto u:cc[i]){
			for(auto [v,w]:e[u]){
				if(bel[u]!=bel[v]) c++;
			}
		}
		if(c==1) nleaf++;
	}
	//最少添加叶子节点/2上取整条路径可以将整棵树覆盖
	printf("%d",(nleaf+1)/2);
    return 0;
}