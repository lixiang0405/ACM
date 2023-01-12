/*
煤矿工地可以看成是由隧道连接挖煤点组成的无向图。

为安全起见，希望在工地发生事故时所有挖煤点的工人都能有一条出路逃到救援出口处。

于是矿主决定在某些挖煤点设立救援出口，使得无论哪一个挖煤点坍塌之后，

其他挖煤点的工人都有一条道路通向救援出口。

请写一个程序，用来计算至少需要设置几个救援出口，

以及不同最少救援出口的设置方案总数。
*/
 
int m,t=0,cnt=0,idx=0;
int dfn[N],low[N],cut[N];
vector<int> e[N],cc[N];
stack<int> sk;

void dfs(int u,int fa){
	dfn[u]=low[u]=++idx;
	sk.push(u);
	int sz=0;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v,u);
			sz++;
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++cnt;
				cc[cnt].push_back(u);
				while(1){
					int x=sk.top();
					sk.pop();
					cc[cnt].push_back(x);
					if(x==v) break;
				}
				cut[u]=1;
			}
		}else if(v!=fa) low[u]=min(low[u],dfn[v]);
	}
	if(u==1&&sz<=1) cut[u]=0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	while(scanf("%d",&m),m){
		int n=0;
		for(int i=1;i<=1000;++i){
			e[i].clear();
			cc[i].clear();
			cut[i]=0;
			low[i]=dfn[i]=0;
		}
		for(int i=1;i<=m;++i){
			int u,v;
			scanf("%d%d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
			n=max({n,u,v});
		}
		printf("Case %d: ",++t);
		sk=stack<int>();
		idx=0;
		cnt=0;
		//dfs(1,0)也行
		for(int i=1;i<=n;++i){
			if(!dfn[i]) dfs(i,0);
		}
		//如果没有割点，则任取两点都行
		if(cnt==1){
			int sz=cc[1].size();
			printf("%d %d\n",2,sz*(sz-1)/2);
			continue;
		}
		ll ans1=0,ans2=1;
		for(int i=1;i<=cnt;++i){
			int sz=0;
			for(auto u:cc[i]){
				if(cut[u]) sz++; 
			}
			//只有一个割点->是叶子节点，从中任取一点
			if(sz==1){
				ans1++;
				ans2*=(int)cc[i].size()-1;
			}
		}
		printf("%d %lld\n",ans1,ans2);
	}
    return 0;
}