/*你决定设计你自己的软件包管理器。不可避免地，你要解决软件包之间的依赖问题。

如果软件包 A 依赖软件包 B，那么安装软件包 A 以前，必须先安装软件包 B。

同时，如果想要卸载软件包 B，则必须卸载软件包 A。现在你已经获得了所有的软件包之间的依赖关系。

而且，由于你之前的工作，除 0 号软件包以外，在你的管理器当中的软件包都会依赖一个且仅一个软件包，

而 0 号软件包不依赖任何一个软件包。依赖关系不存在环（若有 m (m≥2) 个软件包 A1,A2,A3,…,Am，

其中 A1 依赖 A2，A2 依赖 A3，A3 依赖 A4，……，Am−1 依赖 Am，而 Am 依赖 A1，则称这 m 个软件包的依赖关系构成环），

当然也不会有一个软件包依赖自己。

现在你要为你的软件包管理器写一个依赖解决程序。

根据反馈，用户希望在安装和卸载某个软件包时，快速地知道这个操作实际上会改变多少个软件包的安装状态

（即安装操作会安装多少个未安装的软件包，或卸载操作会卸载多少个已安装的软件包），

你的任务就是实现这个部分。注意，安装一个已安装的软件包，或卸载一个未安装的软件包，

都不会改变任何软件包的安装状态，即在此情况下，改变安装状态的软件包数为 0。*/

struct tag{
	int d;
};

struct Tree{
	int l,r;
	int val;
	tag t;
}tre[4*N];

int fa[N],l[N],r[N],sz[N],dep[N];
int hs[N],top[N],id[N],a[N];
int tot,n,m,pre=0;
vector<int> e[N];

void pushdown(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	int d=a.t.d;
	c.val=d*(c.r-c.l+1),b.val=d*(b.r-b.l+1);
	b.t.d=d;
	c.t.d=d;
	a.t.d=-1;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.val=b.val+c.val;
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,0,{-1}};
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
		tre[k].val=(r-l+1)*d;
		tre[k].t.d=d;
	}else{
		if(tre[k].t.d!=-1)
		pushdown(k);
		int m=(l+r)/2;
		if(y<=m) modify(k+k,x,y,d);
		else if(x>m) modify(k+k+1,x,y,d);
		else modify(k+k,x,m,d),modify(k+k+1,m+1,y,d);
		update(k);
	}
}

int query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r;
	if(l==x&&y==r){
		return tre[k].val;
	}else{
		if(tre[k].t.d!=-1)
		pushdown(k);
		int m=(l+r)/2;
		int tmp;
		if(y<=m) {tmp=query(k+k,x,y);}
		else if(x>m) {tmp=query(k+k+1,x,y);}
		else{
			int tmp=query(k+k,x,m)+query(k+k+1,m+1,y);
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

void change(int x){
	while(top[x]!=0){
		//printf("%d\n",l[top[x]]);
		modify(1,l[top[x]],l[x],1);
		x=fa[top[x]];
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		int x;
		scanf("%d",&x);
		x++;
		e[x].push_back(i);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		int x,y;
		char s[10];
		scanf("%s%d",s,&x);
		x++;
		if(s[0]=='i'){
			change(x);
		}else{
			modify(1,l[x],r[x],0);
		}
		printf("%d\n",abs(tre[1].val-pre));
		pre=tre[1].val;
	}
	return 0;
}