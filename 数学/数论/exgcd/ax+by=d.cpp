/*
输入T，一共T组数据，每组三个数a,b,d，

输出ax+by=d的非负整数解(x,y)。

如果无解，那么输出−1，否则输出x最小的解。
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

void solve(){
	ll a,b,c,x,y;
	scanf("%lld%lld%lld",&a,&b,&c);
	int d=exgcd(a,b,x,y);
	if(c%d!=0){
		printf("-1\n");
		return;
	}
	c/=d;
	a/=d;
	b/=d;
	// ax+by=c
	ll tmp=x*(c%b)%b; //c%b怕爆long long
	if(tmp<0) tmp+=b;
	y=(c-a*tmp)/b;
	if(y<0){
		printf("-1\n");
		return;
	}
	printf("%lld %lld\n",tmp,y);
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