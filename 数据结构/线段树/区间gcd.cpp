//1. gcd(a,b)=gcd(a,b−a) 2. gcd(a,b)=gcd(a,−b)
/*给定一个长度为 N 的数列 A，以及 M 条指令，每条指令可能是以下两种之一：

C l r d，表示把 A[l],A[l+1],…,A[r] 都加上 d。
Q l r，表示询问 A[l],A[l+1],…,A[r] 的最大公约数(GCD)。
对于每个询问，输出一个整数表示答案。*/

struct Tree{
	int l,r;
	ll val,g;
}tre[4*N];

int n,m;
ll a[N],b[N];

ll gcd(ll x,ll y){
	if(x<0) x=abs(x);
	if(y<0) y=abs(y);
	if(x<y) swap(x,y);
    return y==0?x:gcd(y,x%y);
}

void update(int u){
	auto &a=tre[u],&b=tre[u+u],&c=tre[u+u+1];
	a.val=b.val+c.val;
    a.g=gcd(b.g,c.g);
}

void build(int k,int x,int y){
	tre[k]={x,y,0,0};
	if(x==y){
		tre[k]={x,y,b[x],b[x]};
		return;
	}
	int m=(x+y)/2;
	build(k<<1,x,m);
	build(k<<1|1,m+1,y);
	update(k);
}

void modify(int k,int x,ll d){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&r==x){
		tre[k].val+=d;
		tre[k].g+=d;
		return;
	}else{	
		if(x<=m) modify(k<<1,x,d);
		else modify(k<<1|1,x,d);
		update(k);
	}
}

ll query(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&r==y){
		return tre[k].val;
	}else{
		if(y<=m) return query(k+k,x,y);
		else if(x>m) return query(k<<1|1,x,y);
		else{
            return query(k<<1,x,m)+query(k<<1|1,m+1,y);
        }
	}
}

ll ask(int k,int x,int y){
	int l=tre[k].l,r=tre[k].r,m=(l+r)/2;
	if(l==x&&r==y){
		return tre[k].g;
	}else{
		if(y<=m) return ask(k+k,x,y);
		else if(x>m) return ask(k<<1|1,x,y);
		else{
            return gcd(ask(k<<1,x,m),ask(k<<1|1,m+1,y));
        }
	}
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
    	cin>>a[i];
		b[i]=a[i]-a[i-1];
	}
    build(1,1,n);
    for(int i=1;i<=m;++i){
        char ty;
        cin>>ty;
        if(ty=='Q'){
            int l,r;
            cin>>l>>r;
			if(l==r) cout<<query(1,1,l)<<endl;
			else
            cout<<gcd(query(1,1,l),ask(1,l+1,r))<<endl;
        }else{
            int l,r;
            ll d;
            cin>>l>>r>>d;
            modify(1,l,d);
			if(r+1<=n)
			modify(1,r+1,-d);
        }
    }
    return 0;
}


/*F - Rectangle GCD

题意：

给定两个长度为 n(n<=2*1e5)  数组 A B ，这里有一个 n*n 的格子，第 i 行第 j 列的格子上的数为 A[i]+B[j] 。

现在给出 Q 次询问，每次询问给出一个矩形范围 (h1,h2,w1,w2)(h1<=i<=h2,w1<=j<=w2) ，求矩形范围内的所有数的 gcd*/

int n,q,a[N],b[N],c[N][2];
 
struct Tree{
	int l,r;
	ll val,g;
}tre[4*N][2];

ll gcd(ll x,ll y){
	if(x<0) x=abs(x);
	if(y<0) y=abs(y);
	if(x<y) swap(x,y);
    return y==0?x:gcd(y,x%y);
}

void update(int u,int g){
	auto &a=tre[u][g],&b=tre[u+u][g],&c=tre[u+u+1][g];
	a.val=b.val+c.val;
    a.g=gcd(b.g,c.g);
}

void build(int k,int x,int y,int g){
	tre[k][g]={x,y,0,0};
	if(x==y){
		tre[k][g]={x,y,c[x][g],c[x][g]};
		return;
	}
	int m=(x+y)/2;
	build(k<<1,x,m,g);
	build(k<<1|1,m+1,y,g);
	update(k,g);
}

void modify(int k,int x,ll d,int g){
	int l=tre[k][g].l,r=tre[k][g].r,m=(l+r)/2;
	if(l==x&&r==x){
		tre[k][g].val+=d;
		tre[k][g].g+=d;
		return;
	}else{	
		if(x<=m) modify(k<<1,x,d,g);
		else modify(k<<1|1,x,d,g);
		update(k,g);
	}
}

ll query(int k,int x,int y,int g){
	int l=tre[k][g].l,r=tre[k][g].r,m=(l+r)/2;
	if(l==x&&r==y){
		return tre[k][g].val;
	}else{
		if(y<=m) return query(k+k,x,y,g);
		else if(x>m) return query(k<<1|1,x,y,g);
		else{
            return query(k<<1,x,m,g)+query(k<<1|1,m+1,y,g);
        }
	}
}

ll ask(int k,int x,int y,int g){
	int l=tre[k][g].l,r=tre[k][g].r,m=(l+r)/2;
	if(l==x&&r==y){
		return tre[k][g].g;
	}else{
		if(y<=m) return ask(k+k,x,y,g);
		else if(x>m) return ask(k<<1|1,x,y,g);
		else{
            return gcd(ask(k<<1,x,m,g),ask(k<<1|1,m+1,y,g));
        }
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
   	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i],c[i][0]=a[i]-a[i-1];
	for(int i=1;i<=n;++i) cin>>b[i],c[i][1]=b[i]-b[i-1];
	build(1,1,n,0);
	build(1,1,n,1);
	while(q--){
		int x,y,z,k;
		cin>>x>>y>>z>>k;
		ll ans=a[x]+b[z];
		if(y!=x) ans=gcd(ans,ask(1,x+1,y,0));
		if(k!=z) ans=gcd(ans,ask(1,z+1,k,1));
		cout<<ans<<endl;
	}
    return 0;
}