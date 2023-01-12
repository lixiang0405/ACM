/*
输入T，一共T组数据，每组三个数a,b,d,l1,r1,l2,r2，输出ax+by=d有多少个解(x,y)满足l1 ≤x≤ r1,l2 ≤y≤ r2。
*/

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

//一般解 x=x1+b/(a,b)*t y=y1-a/(a,b)*t t为任意整数

ll floordiv(ll a,ll b){
	if(a%b==0) return a/b;
	else if(a>0) return a/b;
	else return a/b-1;
}

ll ceildiv(ll a,ll b){
	if(a%b==0) return a/b;
	else if(a>0) return a/b+1;
	else return a/b;
}

int t;

void solve(){
	ll a,b,d,l1,r1,l2,r2;
	scanf("%lld%lld%lld%lld%lld%lld%lld",&a,&b,&d,&l1,&r1,&l2,&r2);
	ll x,y;
	ll p=exgcd(a,b,x,y);
	if(d%p){
		printf("0\n");
		return;
	}
	d/=p;
	a/=p;
	b/=p;
	x=d%b*x%b;
	if(x<0) x+=b;
	y=(d-x*a)/b;
	ll o=min(floordiv(y-l2,a),floordiv(r1-x,b));
	ll r=max(ceildiv(l1-x,b),ceildiv(y-r2,a));
	printf("%lld\n",max(o-r+1,0LL));
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