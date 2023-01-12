/*
输入T，一共T组数据，每组一个数n，输出它的欧拉函数φ(n)。
*/

int t;

ll phi(ll u){
	ll res=u;
	for(ll i=2;i<=u/i;++i){
		if(u%i==0){
			while(u%i==0) u/=i;
			res=res/i*(i-1);
		}
	}
	if(u>1) res=res/u*(u-1);
	return res;
}

void solve(){
	ll n;
	scanf("%lld",&n);
	printf("%lld\n",phi(n));
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