/*
松鼠的新家是一棵树，前几天刚刚装修了新家，新家有n个房间，

并且有n−1根树枝连接，每个房间都可以相互到达，

且俩个房间之间的路线都是唯一的。天哪，他居然真的住在“树”上。

松鼠想邀请小猫前来参观，并且还指定一份参观指南，

他希望小猫能够按照他的指南顺序，先去a1 ，再去a2，……，

最后到an，去参观新家。可是这样会导致重复走很多房间，

懒惰的小猫不停地推辞。可是松鼠告诉他，每走到一个房间，

他就可以从房间拿一块糖果吃。

小猫是个馋家伙，立马就答应了。

现在松鼠希望知道为了保证小猫有糖果吃，

他需要在每一个房间各放至少多少个糖果。

因为松鼠参观指南上的最后一个房间an是餐厅，

餐厅里他准备了丰盛的大餐，

所以当小猫在参观的最后到达餐厅时就不需要再拿糖果吃了。
*/

int n,par[N][M+1],depth[N];
vector<int> e[N];
int a[N],w[N],tag[N];

void dfs(int u,int f){
	depth[u]=depth[f]+1;
	for(auto v:e[u]){
		if(v==f) continue;
		par[v][0]=u;
		dfs(v,u);
	}
}

void dfs2(int u,int f){
	for(auto v:e[u]){
		if(v==f) continue;
		dfs2(v,u);
		tag[u]+=tag[v];
	}
}

int lca(int u,int v){
	if(depth[u]>depth[v]) swap(u,v);
	int d=depth[v]-depth[u];
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
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
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
	for(int i=2;i<=n;++i){
		int u=a[i-1],v=a[i],x=lca(u,v);
		tag[u]++;
		tag[v]++;
		tag[x]-=2;
		w[x]++;
		w[v]--;
	}
	dfs2(1,0);
	for(int i=1;i<=n;++i) printf("%d\n",w[i]+tag[i]);
	return 0;
} 