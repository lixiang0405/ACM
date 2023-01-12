/*
小C同学认为跑步非常有趣，于是决定制作一款叫做《天天爱跑步》的游戏。

《天天爱跑步》是一个养成类游戏，需要玩家每天按时上线，完成打卡任务。

这个游戏的地图可以看作一棵包含 n 个结点和 n−1 条边的树，每条边连接两个结点，

且任意两个结点存在一条路径互相可达。树上结点编号为从 1 到 n 的连续正整数。

现在有 m 个玩家，第 i 个玩家的起点为 Si，终点为 Ti。每天打卡任务开始时，

所有玩家在第 0 秒同时从自己的起点出发，以每秒跑一条边的速度，

不间断地沿着最短路径向着自己的终点跑去，跑到终点后该玩家就算完成了打卡任务。

（由于地图是一棵树，所以每个人的路径是唯一的）

小C想知道游戏的活跃度，所以在每个结点上都放置了一个观察员。

在结点 j 的观察员会选择在第 Wj 秒观察玩家，
一个玩家能被这个观察员观察到当且仅当该玩家在第 Wj 秒也正好到达了结点 j。

小C想知道每个观察员会观察到多少人？

注意：我们认为一个玩家到达自己的终点后该玩家就会结束游戏，
他不能等待一段时间后再被观察员观察到。
即对于把结点 j 作为终点的玩家：
若他在第 Wj 秒前到达终点，则在结点 j 的观察员不能观察到该玩家；
若他正好在第 Wj 秒到达终点，则在结点 j 的观察员可以观察到这个玩家。
*/

int par[N][M+1];
vector<int> e[N];
int w[N],l[N],r[N],tot,ans[N],dep[N],pre[2*N];
vector<array<int,3>> up,down;

void dfs(int u,int f){
	dep[u]=dep[f]+1;
	l[u]=++tot;
	for(auto v:e[u]){
		if(v==f) continue;
		par[v][0]=u;
		dfs(v,u);
	}
	r[u]=tot;
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
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=M;++i){
		for(int u=1;u<=n;++u){
			par[u][i]=par[par[u][i-1]][i-1];
		}
	}
	for(int i=1;i<=n;++i) scanf("%d",&w[i]);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		int x=lca(u,v);
		up.push_back({dep[u],l[u],1});//w[j]=dep[u]-dep[j]
		up.push_back({dep[u],l[x],-1});
		int T=dep[u]+dep[v]-2*dep[x];
		down.push_back({T-dep[v],l[v],1});//T-w[j]=dep[v]-dep[x]
		down.push_back({T-dep[v],l[x],-1});
		if(dep[u]-dep[x]==w[x]) ans[x]++;
	}
	m=up.size();
	stable_sort(up.begin(),up.end());
	stable_sort(down.begin(),down.end());
	for(int i=1;i<=m;++i){
		pre[i]=pre[i-1]+up[i-1][2];
	}
	for(int i=1;i<=n;++i){
		int pl=lower_bound(up.begin(),up.end(),array<int,3>{dep[i]+w[i],l[i],-2})-up.begin();
		int pr=lower_bound(up.begin(),up.end(),array<int,3>{dep[i]+w[i],r[i],2})-up.begin();
		ans[i]+=pre[pr]-pre[pl];
	}
	for(int i=1;i<=m;++i){
		pre[i]=pre[i-1]+down[i-1][2];
	}
	for(int i=1;i<=n;++i){
		int pl=lower_bound(down.begin(),down.end(),array<int,3>{w[i]-dep[i],l[i],-2})-down.begin();
		int pr=lower_bound(down.begin(),down.end(),array<int,3>{w[i]-dep[i],r[i],2})-down.begin();
		ans[i]+=pre[pr]-pre[pl];
	}
	for(int i=1;i<=n;++i) printf("%d ",ans[i]);
	return 0;
} 