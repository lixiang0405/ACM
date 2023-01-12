//https://atcoder.jp/contests/abc232/tasks/abc232_f

/*给你两个数组A和B,你可以对A的元素执行
1.增加1或减少1,花费X的费用
2.交换两个相邻的元素,花费Y的费用
问将A数组变得完全和B数组一样的最小费用*/

ll dp[1<<18];
int a[N],b[N];
int n;
ll x,y;

ll f(int id,ll x){
	ll ans=0;
	rep(i,id,n) if(x&(1<<i)) ans+=y;
	return ans; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>x>>y;
	rep(i,1,1+n) cin>>a[i];
	rep(i,1,1+n) cin>>b[i];
	rep(i,1,1<<n) dp[i]=inf;
	rep(i,1,1<<n){
		int cnt=__builtin_popcount(i);//放A中的第cnt个元素
		rep(j,0,n){
			if(i&(1<<j)){//只能放在有1的位置,放完之后后面的元素就是其增加的逆序对的个数
				dp[i]=min(dp[i],dp[i-(1<<j)]+x*abs(a[cnt]-b[j+1])+f(j+1,i));
			}
		}
	}
	cout<<dp[(1<<n)-1]<<'\n';
	return 0;
}