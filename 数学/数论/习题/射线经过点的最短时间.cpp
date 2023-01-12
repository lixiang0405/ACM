/*
在大小为 n × m 米的矩形房间内有 k 个传感器。
第 i 个传感器位于点 (xi, yi)。
所有传感器都严格位于矩形内的不同点。
房间的对角位于点 (0, 0) 和 (n, m)。
房间的墙壁平行于坐标轴。
在时刻 0，从点 (0, 0) 向点 (1, 1) 的方向释放激光。
射线以每秒 sqrt(2) 米的速度传播。
因此，光线将在开始后恰好一秒内到达点 (1, 1)。
当光线遇到墙壁时，按照入射角等于反射角的规则进行反射。
如果光线到达四个角中的任何一个，它会立即停止。
对于每个传感器，您必须确定光线穿过该传感器所在点的第一个时刻。
如果光线永远不会通过该点，则为此类传感器打印 −1。
*/

ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
} 

ll merge(ll a,ll b,ll c,ll d){
	//x=bt+a bt+a=c(mod d)
	ll x,y;
	ll g=exgcd(b,d,x,y);
	if((a-c)%g){
		return inf;
	}
	d/=g;//d'
	ll t0=((c-a)/g)%d*x%d;
	if(t0<0) t0+=d;
	//t=t0(mod d')
	a=b*t0+a;
	return a;
}

ll t,n,m,k;

//x%2*n=a y%2*m=b x=y

ll solve(ll a,ll b){
	a=(a+2*n)%(2*n);
	b=(b+2*m)%(2*m);
	return merge(a,2*n,b,2*m);
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	scanf("%lld%lld%lld",&n,&m,&k);
	t=n*m/gcd(n,m);
	while(k--){
		int x,y;
		scanf("%d%d",&x,&y);
		//向四个方向翻转
		ll ans=min({solve(x,y),solve(-x,y),solve(x,-y),solve(-x,-y)});
		if(ans>t) printf("-1\n");
		else printf("%lld\n",ans);
	}
	return 0;
} 