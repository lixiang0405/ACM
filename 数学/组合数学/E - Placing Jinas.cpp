//https://codeforces.com/contest/1696/problem/E
/*
我们说无限序列 a0,a1,a2,... 是非递增的当且仅当对于所有 i≥0，ai≥ai+1。
有一个无限的右下网格。
左上角的单元格具有坐标 (0,0)。
行从上到下编号为 0 到无穷大，列从左到右编号从 0 到无穷大。
还有一个非递增无限序列 a0,a1,a2,...。
给你 a0, a1, ……, an;
对于所有 i>n，ai=0。
对于每对 x, y，坐标为 (x,y)（位于第 x 行和第 y 列的交点）如果 y<ax,单元格是白色的，否则是黑色。
最初在 (0,0)上有一个名叫 Jina 的娃娃。
您可以进行以下操作。
在 (x,y)上选择一个玩偶。
取下它，在 (x,y+1)上放置一个玩偶，然后在 (x+1,y)上放置一个玩偶。
请注意，多个娃娃可以同时出现在一个单元格中；
在一次操作中，您只删除一个。
你的目标是让所有的白细胞都包含 0 娃娃。
实现目标所需的最少操作数是多少？
以 109+7 为模打印答案。
*/
ll ans=0;
int n,a[N],b[N],c[500010];

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

int C(int x,int y){
	if(x==y) return 1;
	else if(y==0) return 1;
	return (ll)c[x]*qp((ll)c[y]*c[x-y]%mod,mod-2,mod)%mod;
}

int Q(int y,int u,int d){
	u--;
	return (C(d+y,d)-C(u+y,u)+mod)%mod;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n;
	c[0]=1;
	for(int i=1;i<=500000;++i){
		c[i]=(ll)c[i-1]*i%mod;
	}
	map<int,vector<int>> mp;
	for(int i=1;i<=n+1;++i) cin>>a[i],mp[a[i]].push_back(i);
	int ans=0;
	for(auto &cur:mp){
		ans=ans+Q(cur.first,cur.second.front(),cur.second.back());
		ans%=mod;
	}
	cout<<ans<<endl;
 	return 0;
}