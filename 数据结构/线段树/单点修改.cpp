struct Tree{
	int l,r;
	int minn,cnt;
}tre[4*N];

int a[N],n,q;

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	if(b.minn<c.minn){
		a.minn=b.minn;
		a.cnt=b.cnt;
	}else if(c.minn<b.minn){
		a.minn=c.minn;
		a.cnt=c.cnt;
	}else{
		a.minn=c.minn;
		a.cnt=b.cnt+c.cnt;
	}
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,a[x],1};
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
		tre[k].minn=d;
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
		return {tre[k].minn,tre[k].cnt};
	}else{
		int m=(l+r)/2;
		if(y<=m) return query(k+k,x,y);
		else if(x>m) return query(k+k+1,x,y);
		else{
			auto [a,b]=query(k+k,x,m);
			auto [c,d]=query(k+k+1,m+1,y);
			if(a<c){
				return {a,b};
			}else if(a>c) return {c,d};
			else return {a,b+d};
		}
	}
}

int main() {
	/*ios::sync_with_stdio(false);
    cin.tie(nullptr);*/
    read(n),read(q);
	for(int i=1;i<=n;++i){
		read(a[i]);
	}
	build(1,1,n);
	while(q--){
		int ty;
		read(ty);
		if(ty==1){
			int x,d;
			read(x),read(d);
			modify(1,x,d);
		}else{
			int l,r;
			read(l),read(r);
			auto tmp=query(1,l,r);
			printf("%d %d\n",tmp.first,tmp.second);
		}
	}
    return 0;
}
