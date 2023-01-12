/*
T组询问，每次给一个数n，问{1,2,…,n}中有多少个非空子集，满足这些数的最大公约数是1。输出答案对 109+7 取模的结果。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 pe[i]最小素数因子的多少次2^5=32
int f[N],pw[N];
ll sum[N];

void getp(int x) {
	p[1]=1;
	for (int i = 2; i <= x ; ++i) {
		if (!p[i]) pr[cnt++] = i, pe[i] = i, p[i] = i;
		for (int j = 0; j < cnt && pr[j] * i <= x; ++j) {
			p[i * pr[j]] = pr[j];
			if(p[i] == pr[j]){
				pe[i * pr[j]] = pe[i] * pr[j];
				break;
			}else{
				pe[i * pr[j]] = pr[j];
			}
		}
	}
}

void F(int n,function<void(int)> upd){
	f[1]=1;
	for(int i=2;i<=n;++i){
		if(pe[i]==i) upd(i);
		else f[i]=f[i/pe[i]]*f[pe[i]];
	}
}

void solve(){
	int n;
	scanf("%d",&n);
	ll ans=0;
	for(int l=1;l<=n;++l){
		int d=n/l,r=n/d;
		ans+=(sum[r]-sum[l-1])*(pw[d]-1);
		ans%=mod;
		l=r;
	}
	if(ans<0) ans+=mod;
	printf("%lld\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	scanf("%d",&t);
	getp((int)1e7);
	F((int)1e7,[&](int x){
		f[x]=x==p[x]?-1:0;
	});
	pw[0]=1;
	for(int i=1;i<=(int)1e7;++i){
		pw[i]=pw[i-1]*2%mod;
	}
	// n/d 2^(n/d)-1
	for(int i=1;i<=(int)1e7;++i) sum[i]=sum[i-1]+f[i];
	while(t--){
		solve();
	}
    return 0;
} 