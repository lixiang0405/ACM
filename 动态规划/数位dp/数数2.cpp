//请问 [l,r] 中有多少个数字满足数字的各个数位的和是质数。

ll l,r,dp[N][201];
gp_hash_table<int,int> mp;
int cnt = 0;
ll primes[200 + 5];
bool f[200 + 5];

void get_primes(ll x) {
	//线性筛质数
	for (ll i = 2; i <= x; ++i) {
		if (!f[i]) primes[cnt++] = i;
		for (int j = 0; j < cnt && primes[j] * i <= x; ++j) {
			f[i * primes[j]] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

ll solve(ll n){
    if(!n) return 0;
    ll res=0;
    vector<int> a;
    while(n){
        a.push_back(n%10);
        n/=10;
    }
    reverse(a.begin(),a.end());
    int m=a.size(),sum=0;
    for(int i=0;i<m;++i){
        for(int j=0;j<a[i];++j){
            memset(dp,0,sizeof(dp));
            dp[i][sum+j]=1;
            for(int k=i+1;k<m;++k){
                for(int x=0;x<10;++x){
                    for(int y=x;y<=144;++y)
                    dp[k][y]+=dp[k-1][y-x];
                }
            }
            for(int k=0;k<=144;++k){
                if(mp.find(k)!=mp.end())
                res+=dp[m-1][k];
            }
        }
        sum+=a[i];
    }
    if(mp.find(sum)!=mp.end())
    res++;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    get_primes(200);
    for(int i=0;i<cnt;++i){
    mp[primes[i]]=1;}
    scanf("%lld%lld",&l,&r);
    printf("%lld",solve(r)-solve(l-1));
	return 0;
}