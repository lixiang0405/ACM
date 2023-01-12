/*
给定一个由 N 个整数组成的数组 A。
找到长度为 M 的子序列 S 的数量，使得：
1.M > 1;
2.对于子序列 S 中的任何一对索引 
(i,j)，(lcm(M, Si) - Si) = (lcm(M, Sj) - Sj)
这里 lcm(a,b)表示整数 a 和 b 的 lcm。
由于答案可能很大，因此以 10^9+7为模打印
*/

int a[N],t,c[N];

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

unordered_map<int,int> mp,pm;

int C(int x,int y){
	if(x==y) return 1;
	else if(y==0) return 1;
	return (ll)c[x]*qp((ll)c[y]*c[x-y]%mod,mod-2,mod)%mod;
}

void get(int x){
	for(int i=2;i*i<=x;++i){
		if(x%i==0){
			pm[i]++;
			if(i!=x/i)
			pm[x/i]++;
		}
	}
	//cout<<endl;
}

int reduce(int x,int y){
	int ans=0;
	for(int i=2;i*i<=x;++i){
		if(x%i==0){
			int a=i,b=x/i;
			if(a<=y)
			ans=(ans+C(y,a))%mod;
			if(b<=y&&a!=b)
			ans=(ans+C(y,b))%mod;
			ans%=mod;
		}
	}
	if(x<=y){
		ans+=C(y,x);
		ans%=mod;
	}
	return ans;
}

void solve(){
	int n;
	cin>>n;
	mp.clear();
	pm.clear();
	for(int i=1;i<=n;++i) cin>>a[i],mp[a[i]]++,get(a[i]),pm[a[i]]++;
	int ans=0;
	for(auto [i,j]:mp){
		if(j>=2){
			//cout<<i<<" "<<j<<endl;
			ans=ans+(qp(2,j,mod)-1-j+mod)%mod;
			ans%=mod;
			if(i>1)
			ans=(ans-reduce(i,j)+mod)%mod;
		}
		ans%=mod;
	}     
	//cout<<ans<<endl; 
	for(auto [i,j]:pm){
		//cout<<i<<" "<<j<<endl;
		if(j>=i&&i>1){
			ans=ans+C(j,i);
			ans%=mod;
		}
	}
	cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>t;
	c[0]=1;
	for(int i=1;i<=100000;++i){
		c[i]=(ll)c[i-1]*i%mod;
	}
	while(t--){
		solve();
	}
    return 0;
}