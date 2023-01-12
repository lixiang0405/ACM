/*
一个有向图G=(V,E)称为半连通的，如果满足：∀u,v∈V，满足u→v或v→u，

即对于图中任意两点u，v，存在一条u到v的有向路径或者从v到u的有向路径。

若G′=(V′,E′)满足V′⊂V，E′是E中所有跟V′有关的边，则称G′是G的一个导出子图。

若G′是G的导出子图，且G′半连通，则称G′为G的半连通子图。

若G′是G所有半连通子图中包含节点数最多的，则称G′是G的最大半连通子图。给定一个有向图G，

请求出G的最大半连通子图拥有的节点数K，以及不同的最大半连通子图的数目C。由于C可能比较大，

仅要求输出C对X的余数。
*/

int n,m,cnt=0,tot=0,mod,T=0;
int dfn[N],low[N],bel[N],sz[N],ins[N],dp[N],way[N],vis[N];
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
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
		dfs(i);
	int ans=0,w=0;
	for(int i=1;i<=cnt;++i){
		//从当前点出发
		way[i]=1;
		dp[i]=0;
		T++;
		vis[i]=T;
		for(auto u:rec[i]){
			for(auto v:e[u]){
				//从其他连通块转移过来
				if(vis[bel[v]]!=T){
					vis[bel[v]]=T;
					//注意，if完之后一定执行下一个if
					if(dp[bel[v]]>dp[i]) dp[i]=dp[bel[v]],way[i]=0;
					if(dp[bel[v]]==dp[i]) way[i]=(way[i]+way[bel[v]])%mod;
				}
			}
		}
		dp[i]+=sz[i];
		if(dp[i]>ans)
			ans=dp[i],w=0;
		if(dp[i]==ans) w=(w+way[i])%mod;
	}
	printf("%d\n%d",ans,w);
    return 0;
}

//边dfs边dp写法

int n,m,cnt=0,tot=0,mod,T=0,ans=0,w=0;
int dfn[N],low[N],bel[N],ins[N],dp[N],way[N],vis[N];
stack<int> sk;
vector<int> e[N];

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
		way[cnt]=1;
		dp[cnt]=0;
		T++;
		vis[cnt]=T;
		int sz=0;
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			for(auto y:e[x]){
				//从其他连通块转移过来
				if(vis[bel[y]]!=T){
					vis[bel[y]]=T;
					//注意，if完之后一定执行下一个if
					if(dp[bel[y]]>dp[cnt]) dp[cnt]=dp[bel[y]],way[cnt]=0;
					if(dp[bel[y]]==dp[cnt]) way[cnt]=(way[cnt]+way[bel[y]])%mod;
				}
			}
			sz++;
			if(x==u) break;
		}
		dp[cnt]+=sz;
		if(dp[cnt]>ans)
			ans=dp[cnt],w=0;
		if(dp[cnt]==ans) w=(w+way[cnt])%mod;
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
		dfs(i);
	printf("%d\n%d",ans,w);
    return 0;
}