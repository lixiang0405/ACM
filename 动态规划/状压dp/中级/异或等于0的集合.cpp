/*
jzzhu 有 n 个非负整数 a1, a2, …, an。
我们将索引序列称为 i1, i2, …, ik
(1 ≤ i1 < i2 < … < ik ≤ n)
大小 k。
Jzzhu 想知道，存在多少个集合使得 ai1&ai2&…&aik = 0(1 ≤ k ≤ n)
帮助他打印这个数字模 1000000007(1e9 + 7)。
运算 x&y 表示两个的按位与运算
*/

ll a[N+10],g[N+10];
int n;

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		g[a[i]]++;
	}
	for(int i=0;i<22;++i){
		for(int j=0;j<(1<<22);++j){
			if(!(j&(1<<i))) g[j]+=g[j+(1<<i)];
		}
	}
	for(int i=0;i<(1<<22);++i){
		g[i]%=mod;
		g[i]=qp(2,g[i],mod);
	}
	for(int i=0;i<22;++i){
		for(int j=0;j<(1<<22);++j){
			if(!(j&(1<<i))) g[j]-=g[j+(1<<i)];
		}
	}
	printf("%d",(g[0]%mod+mod)%mod);
	return 0;
}