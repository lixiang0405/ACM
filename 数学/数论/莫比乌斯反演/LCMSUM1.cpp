/*
T组询问，每次给一个n，输出(∑n i=1 [i,n])mod 2^60。
*/

int cnt = 0;
int pr[N],p[N],pe[N];//p[i]最小素数因子 pe[i]最小素数因子的多少次2^5=32
ull f[N];

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

//∑n i=1 [i,n]->∑n i=1 i*n/(i,n) f(x)=1/x -> n ∑(d|n)g(d)∑(1-n)i
//-> n ∑(d|n)g(d)∑d*(n/d)*(n/d+1)/2 -> n^2/2 ∑(d|n)g(d)∑(n/d+1)
//f(d)=∑(d|n)g(d) -> n/2+n^2/2 ∑(d|n)g(d)∑n/d
//n^2/2 ∑(d|n)g(d)∑n/d g(p^e)=(1/(p^e)-1/(p^(e-1))/p^e=1/(p^2e)-1/(p^(2e-1)
//->n^3/2 * [1/(p^2e) - 1/(p^(2e-1) + 1/(p^2e-2) - 1/(p^(2e-3) + ... + 1/p^2 - 1/p^1 + 1](p^0 ?)
//->n/2 *[1 - p + p^2 - p^3 +....+ p^(2*e-2) - p^(2*e-1) + p^2e] -> n/2(1+h(n))

void solve(){
	ull n;
	scanf("%llu",&n);
	printf("%llu\n",(n*(f[n]+1)/2)%(1LL<<60));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
	scanf("%d",&t);
	getp((int)1e7);
	F((int)1e7,[&](ull x){
		f[x]=f[x/p[x]]+x*x/p[x]*(p[x]-1);
	});
	while(t--){
		solve();
	}
    return 0;
} 