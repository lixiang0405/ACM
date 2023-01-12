/*给n个数a1,a2,a3,…,an。

支持q个操作：

1 x d，修改ax=d。

2 l r d， 查询al,al+1,al+2,…,ar中大于等于d的第一个数的下标，如果不存在，输出−1。也就是说，

求最小的i(l≤i≤r)满足ai≥d。*/

struct Tree{
	int l,r;
	int maxx;
}tre[4*N];

int a[N],n,q;

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.maxx=max(b.maxx,c.maxx);
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,a[x]};
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
		tre[k]={x,x,d};
	}else{
		int m=(l+r)/2;
		if(x<=m) modify(k+k,x,d);
		else modify(k+k+1,x,d);
		update(k);
	}
}
//大于等于d的第一个数的下标
int query(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		if(tre[k].maxx<d)
		return -1;
		if(l==r)
		return l;
		else if(tre[k+k].maxx>=d)
		return query(k+k,x,m,d);
		else return query(k+k+1,m+1,y,d); 
	}else{
		if(y<=m) return query(k+k,x,y,d);
		else if(x>m) return query(k+k+1,x,y,d);
		else{
			int pos=query(k+k,x,m,d);
			if(pos==-1) return query(k+k+1,m+1,y,d);
			else return pos;
		}
	}
}

//区间最后一个大于d的坐标
/*int query(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		if(tre[k].maxx<=d)
		return -1;
		if(l==r)
		return l;
		else if(tre[k+k+1].maxx>d)
		return query(k+k+1,m+1,y,d); 
		else return query(k+k,x,m,d);
	}else{
		if(y<=m) return query(k+k,x,y,d);
		else if(x>m) return query(k+k+1,x,y,d);
		else{
			int pos=query(k+k+1,m+1,y,d);
			if(pos==-1) return query(k+k,x,m,d);
			else return pos;
		}
	}
}*/

/*小于d的最后一个数的下标
int query(int k,int x,int y,ll d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		if(tre[k].minn>=d)
		return -1;
		if(l==r)
		return l;
		else if(tre[k+k+1].minn<d)
		return query(k+k+1,m+1,y,d);
		else return query(k+k,x,m,d); 
	}else{
		if(y<=m) return query(k+k,x,y,d);
		else if(x>m) return query(k+k+1,x,y,d);
		else{
			int pos=query(k+k+1,m+1,y,d);
			if(pos==-1) return query(k+k,x,m,d); 
			else return pos;
		}
	}
}*/

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
			int l,r,d;
			read(l),read(r),read(d);
			auto tmp=query(1,l,r,d);
			printf("%d\n",tmp);
		}
	}
    return 0;
}
