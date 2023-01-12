/*给一棵n个点的树，每条边有权。求一条简单路径，
权值和等于k，且边的数量最小。*/

int l[N],r[N],id[N],sz[N],hs[N],tot,n,c[N],cnt[N],dep1[N],k,ans;
vector<pair<int,int>> e[N];
ll dep2[N];
gp_hash_table<ll,int> mp;

void dfs(int u,int f){
    l[u]=++tot;
    id[tot]=u;
    sz[u]=1;
    hs[u]=-1;
    for(auto [v,w]:e[u]){
        if(v==f) continue;
		dep1[v]=dep1[u]+1;
		dep2[v]=dep2[u]+w;
        dfs(v,u);
        sz[u]+=sz[v];
        if(hs[u]==-1||sz[v]>sz[hs[u]])
        hs[u]=v;
    }
    r[u]=tot;
}

void dsu(int u,int f,bool keep){
    for(auto [v,w]:e[u]){
        if(v!=f&&v!=hs[u])
        dsu(v,u,false);
    }

    if(hs[u]!=-1){
        dsu(hs[u],u,true);
    }

	auto add=[&](int x){
		ll tmp=dep2[x];
		if(mp.find(tmp)!=mp.end()){
			mp[tmp]=min(mp[tmp],dep1[x]);
		}else mp[tmp]=dep1[x];
	};
	auto update=[&](int x){
		ll tmp=dep2[u]*2+k-dep2[x];
		if(mp.find(tmp)!=mp.end()){
			ans=min(ans,-2*dep1[u]+mp[tmp]+dep1[x]);
		}
	};

	for(auto [v,w]:e[u]){
		//printf("u %d v %d\n",u,v);
        if(v!=f&&v!=hs[u]){
            for(int i=l[v];i<=r[v];++i)
            update(id[i]);
			for(int i=l[v];i<=r[v];++i)
            add(id[i]);
        }
    }
    update(u),add(u);
	if(!keep){
		mp.clear();
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;++i){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		e[x+1].push_back({y+1,w});
		e[y+1].push_back({x+1,w});
	}
	ans=n+1;
	dfs(1,0);
	dsu(1,0,false);
	if(ans==n+1) ans=-1;
	printf("%d",ans);
	return 0;
}