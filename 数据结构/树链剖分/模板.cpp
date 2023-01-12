int fa[N],l[N],r[N],sz[N],dep[N],hs[N],top[N],id[N];
int tot,n,m;
vector<int> e[N];

void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	sz[u]=1;
	hs[u]=-1;
	for(auto v:e[u]){
		if(v==f) continue;
		fa[v]=u;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(hs[u]==-1||sz[v]>sz[hs[u]]) 
			hs[u]=v;
	}
}

void dfs2(int u,int f){//f:链头
	l[u]=++tot;
	top[u]=f;
	id[tot]=u;
	if(hs[u]!=-1){
		dfs2(hs[u],f);
	}
	for(auto v:e[u]){
		if(v!=fa[u]&&v!=hs[u])
		dfs2(v,v);
	}
	r[u]=tot;
}

int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
		y=fa[top[y]];
		else x=fa[top[x]];
	}
	if(dep[x]<dep[y]) return x;
	else return y; 
}

void change(int x,int y,int col){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			modify(1,l[top[x]],l[x],col);
			x=fa[top[x]];
		}else{
			modify(1,l[top[y]],l[y],col);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		modify(1,l[y],l[x],col);
	}else{
		// cout<<l[x]<<" "<<l[y]<<endl;
		modify(1,l[x],l[y],col);
	}
}

pair<int,int> ask(int x,int y){
	pair<int,int> ans{-inf,0};
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			auto tmp=query(1,l[top[x]],l[x]);
			ans.first=max(tmp.first,ans.first);
			ans.second+=tmp.second;
			x=fa[top[x]];
		}else{
			auto tmp=query(1,l[top[y]],l[y]);
			ans.first=max(tmp.first,ans.first);
			ans.second+=tmp.second;
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		auto tmp=query(1,l[y],l[x]);
		ans.first=max(tmp.first,ans.first);
		ans.second+=tmp.second;
	}else{
		auto tmp=query(1,l[x],l[y]);
		ans.first=max(tmp.first,ans.first);
		ans.second+=tmp.second;
	}
	return ans;
}