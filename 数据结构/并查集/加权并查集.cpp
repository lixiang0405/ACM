/*给你n个变量a1,a2,…,an，一开始不知道这些数是多少。

你要执行q次操作。

1 l r x，给你一条线索，表示al−ar=x，如果与已知条件矛盾，那么忽略这次操作。

2 l r回答al−ar，如果现在的线索无法推出答案，那么忽略这次操作。*/

int fa[N],n,q;
ll w[N];
int find(int u){
	if(u==fa[u]) return u;
	int p=fa[u];
	find(fa[u]);
	//w[u]=a[u]-a[p] w[p]=a[p]-a[fa[p]] w[u]=a[u]-a[fa[u]]=w[u]+w[p]
	w[u]=w[u]+w[p];
	return fa[u]=fa[p];
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i){
		fa[i]=i;
		w[i]=0;
	}
	ll t=0;
	for(int i=0;i<q;++i){
		int ty;
		scanf("%d",&ty);
		if(ty==1){
			ll l,r,x;
			scanf("%lld%lld%lld",&l,&r,&x);
			l=(t+l)%n+1,r=(t+r)%n+1;
			if(find(l)==find(r)) continue;
			//a[l]-a[r]=x a[l]-w[l]=a[fa[l]] a[r]-w[r]=a[fa[r]] a[fa[l]]-a[fa[r]]
			w[fa[l]]=x-w[l]+w[r];
			fa[fa[l]]=fa[r];
		}else{
			ll l,r;
			scanf("%lld%lld",&l,&r);
			l=(t+l)%n+1,r=(t+r)%n+1;
			if(find(l)!=find(r)) continue;
			t=abs(w[l]-w[r]);
			printf("%lld\n",w[l]-w[r]);//a[l]-a[fa[l]]-(a[r]-a[fa[r]]) fa[l]=fa[r]
		}
	}
	return 0;
}
