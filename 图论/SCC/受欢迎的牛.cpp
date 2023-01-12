/*
每一头牛的愿望就是变成一头最受欢迎的牛。
现在有N头牛，给你M对整数(A,B)，表示牛A认为牛B受欢迎。
这种关系是具有传递性的，如果A认为B受欢迎，B认为C受欢迎，
那么牛A也认为牛C受欢迎。你的任务是求出有多少头牛被所有的牛认为是受欢迎的。
*/

int n,m,cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N],out[N];
stack<int> sk;
vector<int> e[N],rec[N];

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
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			rec[cnt].push_back(x);
			sz[cnt]++;
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
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
		dfs(i);
	int ans=0,cntv=0;
	for(int i=1;i<=cnt;++i){
		for(auto u:rec[i]){
			for(auto v:e[u]){
				if(bel[v]!=i){
					out[i]++;
				}
			}
		}
		if(out[i]==0){
			ans=sz[i];
			cntv++;
		}
	}
	if(cntv>=2){
		printf("0");
	}else{
		printf("%d",ans);
	}
    return 0;
}