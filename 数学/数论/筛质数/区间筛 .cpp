/*
给两个数字l,r，求l∼r中的所有素数p。

为了防止输出过大和防止打表，给定a,b，输出这些素数(a⋅p+b) mod 2^32的异或和。
*/

int cnt = 0;
int primes[N / 5 + 5],vis[N+5];
bool f[N + 5];

void get_primes(int x) {
	//线性筛质数
	for (int i = 2; i <= x ; ++i) {
		if (!f[i]) primes[cnt++] = i;
		for (int j = 0; j < cnt && primes[j] * i <= x; ++j) {
			f[i * primes[j]] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

unsigned int a,b,ans=0;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	get_primes(N);
	ll l,r;
	scanf("%lld%lld%u%u",&l,&r,&a,&b);
	for(int i=0;i<cnt;++i){
		for(ll j=r/primes[i]*primes[i];j>=l&&j>primes[i];j-=primes[i]){
			vis[j-l]=1;
		}
	}
	//1 不是素数
	for(ll i=max(l,2LL);i<=r;++i) {
		if(!vis[i-l]){
			ans^=a*(unsigned int)i+b;
		}
	}
	printf("%u",ans);
	return 0;
} 