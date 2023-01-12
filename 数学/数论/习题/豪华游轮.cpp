/*
Kayzin 计划购买一艘豪华游轮，花费 N 个硬币。
但是 Kayzin 没有足够的硬币，所以 Kayzin 决定开始储蓄硬币。
Kayzin 每天会将 7 或 31 或 365 个硬币放入他的存钱罐中。
现在 Kayzin 想知道他至少需要多少天才能“准确地”（不多也不少）凑齐购买豪华游轮的钱。
如果 Kayzin 不能“完全”凑齐购买豪华游轮的钱，请打印 -1。
*/

int t;
int p=7*31-7-31;

void solve(){
	ll n;
	cin>>n;
	ll x=n/365;
	n%=365;
	while(n<p&&x) n+=365,x--;
	ll ans=inf;
	for(int i=0;7*i<=n;++i){
		for(int j=0;31*j+7*i<=n;++j){
			for(int k=0;31*j+7*i+k*365<=n;++k){
				if(31*j+7*i+k*365==n){
					ans=min(ans,x+i+j+k);
				}
			}
		}
	}
	if(ans==inf) cout<<-1<<endl;
	else cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
} 