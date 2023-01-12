/*
一共T组数据，每组数据，给定n个方程，求x≡ai(mod mi)。
*/

int t;

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
} 

void merge(ll &a,ll &b,ll c,ll d){
	if(a==-1&&b==-1) return;
	//x=bt+a bt+a=c(mod d)
	ll x,y;
	ll g=exgcd(b,d,x,y);
	if((a-c)%g){
		a=b=-1;
		return;
	}
	d/=g;//d'
	ll t0=((c-a)/g)%d*x%d;
	if(t0<0) t0+=d;
	//t=t0(mod d')
	a=b*t0+a;
	b=b*d;
}

void solve(){
	int n;
	scanf("%d",&n);
	ll a=0,b=1;//x%b=a
	for(int i=1;i<=n;++i){
		ll c,d;
		scanf("%lld%lld",&c,&d);
		merge(a,b,c,d);
	}
	printf("%lld\n",a);
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	scanf("%d",&t);
	while(t--){
		solve();
	}
	return 0;
} 