/*
令 f(x)表示 x 的二进制表示中 1 的个数。
现在 MianKing 有一个序列 a0,a1,…,am−1并且他想知道整数 x∈[0,L]的个数满足：
∀i∈[0,m−1],f(x+i)mod2=ai
你需要帮助他计算答案。
*/

//a[2*i]=a[i] a[2*i+1]=1-a[i]
//a[k] a[k+1] a[k+2] a[k+3] a[k+4] a[k+5]...a[k+n-1]
//k为偶数 a[k/2] 1-a[k/2] a[k/2+1] 1-a[k/2+1] 易知{1，2}，{3，4}两个数不同
//k为奇数 1-a[k/2] a[(k+1)/2] 1-a[k/2+1] a[(k+1)/2+1] 易知{2，3}不同
//a[2*k+1] a[2*k+2] a[2*k+3]...1-a[k] a[k+1] 1-a[k+1] a[k+2] 1-a[k+2]
//1->10 0->01
//dp[{L,{a[k],a[k+1],a[k+2]...a[k+n'-1]}}]0--L中满足条件的k值 对于每个满足条件的k值，都有偶数和奇数满足上式子
//不满足则没有k值 
//k'=k/2    k为偶数则偶数项相等a[i]=a[i*2]，k为奇数则奇数项相等a[i]=a[i*2]
int t,a[N];
map<pair<ll,vector<int>>,ll> mp;

vector<int> reduce(vector<int> a){
	vector<int> res;
	for(int i=0;i<a.size();i+=2){
		res.push_back(a[i]);
		if(i+1<a.size()&&a[i]==a[i+1]) return {};
	}
	return res;
}

ll dfs(ll L,vector<int> a){
	if(a.empty()) return 0;
	if(mp.count({L,a})) return mp[{L,a}];
	if(L==0){
		ll ans=1;
		for(int i=0;i<a.size();++i){
			if(__builtin_parity(i)!=a[i]){
				ans=0;
				break;
			}
		}
		return mp[{L,a}]=ans;
	}
	ll ans=0;
	ans+=dfs(L/2,reduce(a));
	auto b=a;
	b.insert(b.begin(),a[0]^1);
	ans+=dfs((L-1)/2,reduce(b));
	return mp[{L,a}]=ans;
}

void solve(){
	int n;
	ll L;
	scanf("%d%lld",&n,&L);
	mp.clear();
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	printf("%lld\n",dfs(L,vector<int>(a+1,a+1+n)));
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