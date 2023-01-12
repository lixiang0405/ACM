/*给定一棵 n 个节点的无根树，共有 m 个操作，操作分为两种：

将节点 a 到节点 b 的路径上的所有点（包括 a 和 b）都染成颜色 c。

询问节点 a 到节点 b 的路径上的颜色段数量。

颜色段的定义是极长的连续相同颜色被认为是一段。例如 112221 由三段组成：11、222、1。*/

struct tag{
	int d;
};

struct Tree{
	int l,r;
	int lc,rc,seg;
	tag t;
}tre[4*N];

int fa[N],l[N],r[N],sz[N],dep[N];
int hs[N],top[N],id[N],a[N];
int tot,n,m;
vector<int> e[N];

void pushdown(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	int d=a.t.d;
	c.seg=0,b.seg=0;
	c.lc=d,c.rc=d,b.lc=d,b.rc=d;
	b.t.d=d;
	c.t.d=d;
	a.t.d=0;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.lc=b.lc,a.rc=c.rc;
	a.seg=b.seg+c.seg+(b.rc!=c.lc);
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,a[id[x]],a[id[x]],0,{0}};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r;
	if(x==l&&y==r){
		tre[k].seg=0;
		tre[k].lc=d,tre[k].rc=d;
		tre[k].t.d=d;
	}else{
		if(tre[k].t.d)
		pushdown(k);
		int m=(l+r)/2;
		if(y<=m) modify(k+k,x,y,d);
		else if(x>m) modify(k+k+1,x,y,d);
		else modify(k+k,x,m,d),modify(k+k+1,m+1,y,d);
		update(k);
	}
}

array<int,3> query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r;
	if(l==x&&y==r){
		return {tre[k].lc,tre[k].rc,tre[k].seg};
	}else{
		if(tre[k].t.d)
		pushdown(k);
		int m=(l+r)/2;
		array<int,3> tmp;
		if(y<=m) {tmp=query(k+k,x,y);}
		else if(x>m) {tmp=query(k+k+1,x,y);}
		else{
			auto [a1,a2,a3]=query(k+k,x,m);
			auto [b1,b2,b3]=query(k+k+1,m+1,y);
			tmp={a1,b2,a3+b3+(a2!=b1)};
		}
		update(k);
		return tmp;
	}
}

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
		modify(1,l[x],l[y],col);
	}
}

int ask(int x,int y){
	pair<int,int> ansx{0,-1},ansy{0,-1};
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			auto tmp=query(1,l[top[x]],l[x]);
			ansx.second+=tmp[2]+(ansx.first!=tmp[1]);
			ansx.first=tmp[0];
			x=fa[top[x]];
		}else{
			auto tmp=query(1,l[top[y]],l[y]);
			ansy.second+=tmp[2]+(ansy.first!=tmp[1]);
			ansy.first=tmp[0];
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		auto tmp=query(1,l[y],l[x]);
		ansx.second+=tmp[2]+(ansx.first!=tmp[1]);
		ansx.first=tmp[0];
	}else{
		auto tmp=query(1,l[x],l[y]);
		ansy.second+=tmp[2]+(ansy.first!=tmp[1]);
		ansy.first=tmp[0];
	}
	return ansx.second+ansy.second+1+(ansx.first!=ansy.first);
	//为什么要判(ansx.first!=ansy.first):ansx 的信息是 x的儿子端点的信息而不是x点的信息
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;++i){
		int x,y;
		char ch;
		scanf(" %c%d%d",&ch,&x,&y);
		if(ch=='C'){
			int z;
			scanf("%d",&z);
			change(x,y,z);
		}else{
			printf("%d\n",ask(x,y));
		}
	}
	return 0;
}