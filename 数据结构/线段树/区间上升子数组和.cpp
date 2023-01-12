struct Tree{
	int l,r;
	int L_len,R_len,L_val,R_val;
	ll ans;
}tre[4*N];

int n,q,a[N];

void update(Tree &a,Tree &b,Tree &c){
	a.ans=b.ans+c.ans;
	if(b.R_val<=c.L_val) a.ans=a.ans+(ll)b.R_len*c.L_len;
	a.L_len=b.L_len;
	if(b.L_len==(b.r-b.l+1)&&b.R_val<=c.L_val) a.L_len+=c.L_len;
	a.R_len=c.R_len;
	if(c.R_len==(c.r-c.l+1)&&b.R_val<=c.L_val) a.R_len+=b.R_len;
	a.L_val=b.L_val;
	a.R_val=c.R_val;
}

inline void update(int k){
	update(tre[k],tre[k<<1],tre[k<<1|1]);
}

inline void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,x,1,1,a[x],a[x],1};
	}else{
		int m=(x+y)>>1;
		tre[k]={x,y};
		build(k<<1,x,m);
		build(k<<1|1,m+1,y);
		update(k);
	}
}

inline void modify(int k,int x,int t){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==r){
		tre[k]={l,l,1,1,t,t,1};
	}else{
		if(x<=m) modify(k<<1,x,t);
		else modify(k<<1|1,x,t);
		update(k);
	}
}

inline Tree query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		return tre[k];
	}else{
		if(y<=m) return query(k<<1,x,y);
		else if(x>m) return query(k<<1|1,x,y);
		else{
			auto a=query(k<<1,x,m),b=query(k<<1|1,m+1,y);
			Tree c;
			update(c,a,b);
			return c;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	while(q--){
		int ty,x,y;
		cin>>ty>>x>>y;
		if(ty==1){
			modify(1,x,y);
		}else{
			cout<<query(1,x,y).ans<<endl;
		}
	}
    return 0;
}
