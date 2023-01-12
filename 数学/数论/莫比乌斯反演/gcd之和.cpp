/*
T组询问，每次给两个数n,m，求∑(ni=1)∑m(j=1) (i,j)。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 pe[i]最小素数因子的多少次2^5=32
int f[N];
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
//id*u=φ f(x)*u=g(x)
void solve(){
	int n,m;
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	ll ans=0;
	for(int l=1;l<=n;++l){
		int d1=n/l,d2=m/l;
		int r=min(n/d1,m/d2);//d1和d2再l到r之间都不会变
		ans+=(sum[r]-sum[l-1])*d1*d2;
		l=r;
	}
	printf("%lld\n",ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	scanf("%d",&t);
	getp((int)1e7);
	F((int)1e7,[&](int x){
		f[x]=x/p[x]*(p[x]-1);
	});
	for(int i=1;i<=(int)1e7;++i) sum[i]=sum[i-1]+f[i];
	while(t--){
		solve();
	}
    return 0;
} 