/*现有 n 盏灯排成一排，从左到右依次编号为：1，2，……，n。然后依次执行 m 项操作。

操作分为两种：

指定一个区间 [a,b]，然后改变编号在这个区间内的灯的状态（把开着的灯关上，关着的灯打开）；

指定一个区间 [a,b]，要求你输出这个区间内有多少盏灯是打开的。

灯在初始时都是关着的。*/

struct Tree{
	int l,r,val;
}tre[4*N];
int n,m,v[4*N];

void pushdown(int u){
	auto &b=tre[u+u],&c=tre[u<<1|1];
	v[u<<1]^=1,v[u<<1|1]^=1;
	b.val=(b.r-b.l+1)-b.val,c.val=(c.r-c.l+1)-c.val;
	v[u]=0;
}

void build(int k,int x,int y){
	tre[k]={x,y,0};
	if(x==y)
	return;
	int m=x+y>>1;
	build(k<<1,x,m);
	build(k<<1|1,m+1,y);
}

void add(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=l+r>>1;
	if(l==x&&y==r){
		tre[k].val=(y-x+1)-tre[k].val;
		v[k]^=1;
		return;
	}else{	
		if(v[k])
		pushdown(k);
		if(y<=m) add(k<<1,x,y);
		else if(x>m) add(k<<1|1,x,y);
		else add(k<<1,x,m),add(k<<1|1,m+1,y);
		tre[k].val=tre[k+k].val+tre[k+k+1].val;
	}
}

int query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)>>1;
	if(l==x&&r==y){
		return tre[k].val;
	}else{
		if(v[k])
		pushdown(k);
		if(y<=m) return query(k<<1,x,y);
		else if(x>m) return query(k<<1|1,x,y);
		else return query(k<<1,x,m)+query(k<<1|1,m+1,y);
	}
}
int main()
{
	cin>>n>>m;
	build(1,1,n);
	while(m--){
		int a;
		cin>>a;
		if(a==0){
			int b,c;
			cin>>b>>c;
			add(1,b,c);
		}else{
			int b,c;
			cin>>b>>c;
			cout<<query(1,b,c)<<endl;
		}
	}
	return 0;
}