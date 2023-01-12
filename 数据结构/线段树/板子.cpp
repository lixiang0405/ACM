struct Tree{
	int l,r;
	int cnt,nct,val;
	int t;
}tre[4*N];

void pushdown(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	if(a.t){
		b.val=b.r,b.cnt=1;
		c.val=c.r,c.cnt=1;
		b.nct=1,c.nct=1;
	}
	else{
		b.val=0,b.cnt=0;
		c.val=0,c.cnt=0;
		b.nct=0,c.nct=0;
	}
	b.t=c.t=a.t;
	a.t=-1;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	if(c.cnt)
		a.val=c.val,a.cnt=c.cnt;
	else if(b.cnt)
		a.val=b.val,a.cnt=b.cnt;
	else a.val=0,a.cnt=0;
	
	if(b.nct==0||c.nct==0) a.nct=0;
	else a.nct=1;
	a.t=-1;
}

void build(int k,int x,int y){
	if(x==y){
		tre[k]={x,y,a[x],a[x],x,-1};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int y,ll d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		if(d)
			tre[k].val=tre[k].r,tre[k].cnt=1,tre[k].nct=1;
		else tre[k].val=0,tre[k].cnt=0,tre[k].nct=0;
		tre[k].t=d;
		return;
	}else{	
		if(tre[k].t!=-1)
			pushdown(k);
		if(y<=m) modify(k<<1,x,y,d);
		else if(x>m) modify(k<<1|1,x,y,d);
		else modify(k<<1,x,m,d),modify(k<<1|1,m+1,y,d);
		update(k);
	}
}

int Q(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		return tre[k].cnt;
	}else{
		if(tre[k].t!=-1)
			pushdown(k);
		if(y<=m) return Q(k+k,x,y);
		else if(x>m) return Q(k<<1|1,x,y);
		else return (Q(k<<1,x,m)+Q(k<<1|1,m+1,y))%mod;
	}
}

//最前面一个大于d的坐标
int query(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&y==r){
		if(tre[k].t!=-1)
			pushdown(k);
		if(tre[k].cnt<=d)
		return -1;
		if(l==r)
		return l;
		else if(tre[k+k].cnt>d)
		return query(k+k,x,m,d); 
		else return query(k+k+1,m+1,y,d);
	}else{
		if(tre[k].t!=-1)
			pushdown(k);
		if(y<=m) return query(k+k,x,y,d);
		else if(x>m) return query(k+k+1,x,y,d);
		else{
			int pos=query(k+k,x,m,d);
			if(pos==-1) return query(k+k+1,m+1,y,d);
			else return pos;
		}
	}
}

//最前面一个小于d的坐标
int ask(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	//cout<<l<<" "<<r<<endl;
	if(l==x&&y==r){
		if(tre[k].t!=-1)
			pushdown(k);
		if(tre[k].nct>=d)
		return -1;
		if(l==r)
		return l;
		else if(tre[k+k].nct<d)
		return ask(k+k,x,m,d);
		else return ask(k+k+1,m+1,y,d);
	}else{
		if(tre[k].t!=-1)
			pushdown(k);
		if(y<=m) return ask(k+k,x,y,d);
		else if(x>m) return ask(k+k+1,x,y,d);
		else{
			int pos=ask(k+k,x,m,d);
			if(pos==-1) return ask(k+k+1,m+1,y,d);
			else return pos;
		}
	}
}