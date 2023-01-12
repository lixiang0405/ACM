/*给你一棵有 N 个顶点的树。
顶点编号为 1.....N，第 i 个(1 <= i <= N - 1)边连接顶点 Ai和Bi
我们通过从顶点u到顶点v的最短路径中的边数来定义这棵树上顶点u和v之间的距离。
给你Q查询。
在第 i 个 (1 ≤ i ≤ Q) 查询中，给定整数 Ui 和 Ki
，打印与顶点 Ui 距离正好是 Ki的任何顶点的索引.
如果没有这样的顶点，则打印 -1。*/

int t,dep[N],dp[N],rec[N];
int par[N][M+1];
VI e[N];
int d=0,a,b;

void dfs(int u,int fa){
	dp[u]=dep[u]=dep[fa]+1;
	rec[u]=u;
	int maxx=0,r;
	for(auto v:e[u]){
		if(v==fa) continue;
		dfs(v,u);
		par[v][0]=u;
		if(dp[u]<dp[v]){
			dp[u]=dp[v];
			rec[u]=rec[v];
		}
	}
	if(d<dp[u]-dep[u]){
		d=dp[u]-dep[u];
		a=u;
		b=rec[u];
	}
	for(auto v:e[u]){
		if(v==fa) continue;
		if(dp[v]+maxx-2*dep[u]>d){
			d=dp[v]+maxx-2*dep[u];
			a=r,b=rec[v];
		}
		if(dp[v]>maxx){
			maxx=dp[v];
			r=rec[v];
		}
	}
}

int Dis(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	int d=dep[v]-dep[u],dis=0;
	for(int i=M;i>=0;--i){
		if(d&(1<<i)){
			v=par[v][i];
			dis+=1<<i;
		}
	}
	if(u==v)
		return dis;
	for(int i=M;i>=0;--i){
		if(par[u][i]!=par[v][i]){
			dis+=1<<(i+1);
			u=par[u][i],v=par[v][i];
		}
	}
	return dis+2;
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

void solve(){
	int n;
	cin>>n;
	rep(i,1,n){
		int u,v;
		cin>>u>>v;
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs(1,0); 
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=par[par[u][i-1]][i-1];
		}
	}
	//cout<<a<<" "<<b<<'\n';
	int q;
	cin>>q;
	while(q--){
		int u,k;
		cin>>u>>k;
		if(Dis(u,a)>=k){
			int c=lca(u,a);
			if(Dis(c,u)>=k){
				int ans=u,x=k;
				for(int i=M;i>=0;--i){
					if(x>=(1<<i)){
						x-=1<<i;
						ans=par[ans][i];
					}
				}
				cout<<ans<<'\n';
			}else{
				int d=Dis(u,a)-k;
				int ans=a,x=d;
				for(int i=M;i>=0;--i){
					if(x>=(1<<i)){
						x-=1<<i;
						ans=par[ans][i];
					}
				}
				cout<<ans<<'\n';
			}
		}else if(Dis(u,b)>=k){
			int c=lca(u,b);
			if(Dis(c,u)>=k){
				int ans=u,x=k;
				for(int i=M;i>=0;--i){
					if(x>=(1<<i)){
						x-=1<<i;
						ans=par[ans][i];
					}
				}
				cout<<ans<<'\n';
			}else{
				int d=Dis(u,b)-k;
				int ans=b,x=d;
				for(int i=M;i>=0;--i){
					if(x>=(1<<i)){
						x-=1<<i;
						ans=par[ans][i];
					}
				}
				cout<<ans<<'\n';
			}
		}else{
			cout<<-1<<'\n';
		}
	}
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	t=1;
	while(t--){
		solve();
	}
	return 0;
}