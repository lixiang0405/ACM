/*
一个数组可以删掉两个x变成x+1，问最大值是什么
将b[k]改为l，每修改一次就询问一次上面的问题
*/
struct Tree{
	int l,r;
	int cnt,nct,val;
	int t;
}tre[4*N];

int a[N];
int n,q;

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
	//printf("%d %d",x,y);
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

int t,b[N];

void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		a[x]++;
		b[i]=x;
	}
	for(int i=1;i<=4e5;++i){
		if(a[i]/2) a[i+1]+=a[i]/2;
		a[i]=a[i]%2;
	}
	build(1,1,4e5);
	while(q--){
		int k,l;
		cin>>k>>l;
		int cnt=Q(1,b[k],b[k]);
		if(cnt==1){
			modify(1,b[k],b[k],0);
		}else{
			int pos=query(1,b[k]+1,4e5,0);
			modify(1,pos,pos,0);
			modify(1,b[k],pos-1,1);
		}
		cnt=Q(1,l,l);
		if(cnt==0){
			modify(1,l,l,1);
		}else{
			int pos=ask(1,l+1,4e5,1);
			//cout<<"!!! "<<pos<<" "<<Q(1,pos-3,pos-3)<<endl;
			modify(1,pos,pos,1);
			modify(1,l,pos-1,0);
		}
		b[k]=l;
		cout<<tre[1].val<<endl;
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	t=1;
	while(t--){
		solve();
	}
    return 0;
}