/*一棵树上有n个节点，编号分别为1到n，每个节点都有一个权值w。我们将以下面的形式来要求你对这棵树完成一些操作：

CHANGE u t，把结点u的权值改为t。
QMAX u v，询问从点u到点v的路径上的节点的最大权值
QSUM u v， 询问从点u到点v的路径上的节点的权值和。注意：从点u到点v的路径上的节点包括u和v本身。*/

struct Tree{
	int l,r;
	int maxx,cnt;
}tre[4*N];

int fa[N],l[N],r[N],sz[N],dep[N];
int hs[N],top[N],id[N],a[N];
int tot,n,m;
vector<int> e[N];

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.maxx=max(b.maxx,c.maxx);
	a.cnt=b.cnt+c.cnt;
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,a[id[x]],a[id[x]]};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int d){
	int l=tre[k].l,r=tre[k].r;
	if(l==r){
		tre[k].maxx=d;
		tre[k].cnt=d;
	}else{
		int m=(l+r)/2;
		if(x<=m) modify(k+k,x,d);
		else modify(k+k+1,x,d);
		update(k);
	}
}

pair<int,int> query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r;
	if(l==x&&y==r){
		return {tre[k].maxx,tre[k].cnt};
	}else{
		int m=(l+r)/2;
		if(y<=m) return query(k+k,x,y);
		else if(x>m) return query(k+k+1,x,y);
		else{
			auto [a,b]=query(k+k,x,m);
			auto [c,d]=query(k+k+1,m+1,y);
			return {max(a,c),b+d};
		}
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		int x,y;
		char str[10];
		scanf("%s%d%d",str,&x,&y);
		if(str[0]=='C'){
			modify(1,l[x],y);
		}else{
			auto [a,b]=ask(x,y);
			if(str[1]=='M'){
				printf("%d\n",a);
			}else{
				printf("%d\n",b);
			}
		}
	}
	return 0;
}