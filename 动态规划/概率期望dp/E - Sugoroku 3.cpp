/*Square N 有 N 个正方形，称为 Square 1 到 Square N。
你从 Square 1 开始。从方格 1 到方格 N-1 的每个方格上都有一个骰子。
Square i 上的骰子标有从 0 到 Ai 的整数，每个都以相等的概率发生。
（掷骰子是相互独立的。）
直到您到达 Square N，您将在您所在的方格上重复掷骰子。
在这里，如果方块 x 上的骰子掷出整数 y，则您转到方块 x+y。
求掷骰子次数的期望值，以 998244353 为模。*/

int t,a[N],b[N];
ll suf[N];

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

void solve(){
    int n;
	cin>>n;
	rep(i,1,n) cin>>a[i],b[i]=qp(a[i],mod-2,mod);
	ll ans=0;
    // ∑(i=0 —— +∞) i/x^i = x/(1-x)^2
    //dp[i] 表示从i到N的期望
    //dp[i]=∑(j=1——A[i])*dp[j+i]/A[i] + X (X:∑(i=0 —— +∞)j*A[i]/(A[i]+1)^(j+1)) + 1
	per(i,1,n){
		ans=((suf[i+1]-suf[i+a[i]+1]+mod)%mod*b[i]%mod+1+b[i])%mod;
		suf[i]=(ans+suf[i+1])%mod;
	}
	cout<<ans<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	t=1;
    while(t--){
        solve();
    }
	return 0;
} 