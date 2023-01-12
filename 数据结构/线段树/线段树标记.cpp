/*
给n个数a1,a2,a3,…,an。
支持q个操作：
1 l r d，令所有的ai(l≤i≤r)加上d。
2 l r d，令所有的ai(l≤i≤r)乘上d。
3 l r d，令所有的ai(l≤i≤r)等于d。
4 l r，查询(∑ri=lai)mod(109+7)。
*/

struct tag{
	ll x,y;
};

struct Tree{
	int l,r;
	ll val;
	tag t;
}tre[4*N];

int n,q;
ll a[N];

void update(int u){
	auto &a=tre[u],&b=tre[u+u],&c=tre[u<<1|1];
	a.val=(b.val+c.val)%mod;
}

void pushdown(int u){
	auto &a=tre[u],&b=tre[u+u],&c=tre[u<<1|1];
	b.t={(a.t.x*b.t.x)%mod,(a.t.y+b.t.y*a.t.x)%mod},
	c.t={(a.t.x*c.t.x)%mod,(a.t.y+c.t.y*a.t.x)%mod};
	b.val=(b.val*a.t.x+a.t.y*(b.r-b.l+1))%mod,c.val=(c.val*a.t.x+a.t.y*(c.r-c.l+1))%mod;
	a.t={1,0};
}

void build(int k,int x,int y){
	tre[k]={x,y,0,{1,0}};
	if(x==y){
	tre[k]={x,y,a[x],{1,0}};
	return;}
	int m=(x+y)/2;
	build(k<<1,x,m);
	build(k<<1|1,m+1,y);
	update(k);
}

void modify(int k,int x,int y,ll u,ll v){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		tre[k].val=(tre[k].val*u+v*(r-l+1))%mod;
		tre[k].t={(u*tre[k].t.x)%mod,(u*tre[k].t.y+v)%mod};
		return;
	}else{	
		if(!(tre[k].t.x==1&&tre[k].t.y==0))
		pushdown(k);
		if(y<=m) modify(k<<1,x,y,u,v);
		else if(x>m) modify(k<<1|1,x,y,u,v);
		else modify(k<<1,x,m,u,v),modify(k<<1|1,m+1,y,u,v);
		update(k);
	}
}

ll query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		return tre[k].val;
	}else{
		if(!(tre[k].t.x==1&&tre[k].t.y==0))
			pushdown(k);
		if(y<=m) return query(k+k,x,y);
		else if(x>m) return query(k<<1|1,x,y);
		else return (query(k<<1,x,m)+query(k<<1|1,m+1,y))%mod;
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	build(1,1,n);
	while(q--){
		int ty;
		scanf("%d",&ty);
		if(ty==4){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,l,r));
		}else{
			int l,r;
			ll d;
			scanf("%d%d%lld\n",&l,&r,&d);
			if(ty==1){
				modify(1,l,r,1,d);
			}else if(ty==2){
				modify(1,l,r,d,0);
			}else{
				modify(1,l,r,0,d);
			}
		}
	}
    return 0;
}