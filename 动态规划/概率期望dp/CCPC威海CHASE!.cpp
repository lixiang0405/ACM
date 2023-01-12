/*
题意:有 n 个数,每次系统随机选出两个数 ai, aj,
你可以接受或重选,但总共只有 k 次重选机会。
问期望最大和。还有 q 个子情况需要回答最优决策。
*/

/*
如果 k = 0,那么没有重选的机会,期望得分 E0 为任选两
个数字的和的期望;
如果 k > 0,假设当前选出来的和为 s,那么 s ≥ Ek−1 时不
需要重选,否则需要重选。
dp,用 two pointers 算这两种贡献来转移。
dp[i]=sum(i=[1,n],j=[i+1,n])max(dp[i-1],a[i]+a[j])/((n-1)*n/2)
*/

db dp[N];
int a[N],b[N];
ll pre[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,q,k;
	cin>>n>>k>>q;
	rep(i,1,1+n){
		cin>>a[i];
		b[i]=a[i];
		dp[0]+=(ll)a[i]*(n-1);
	}
	dp[0]/=(db)n*(n-1)/2;
	sort(a+1,a+1+n);
	rep(i,1,1+n) pre[i]=pre[i-1]+a[i];
	rep(i,1,2+k){
		int l=1;
		rep(j,2,1+n){
			while(l<j&&a[l]+a[j]<dp[i-1]) l++;
			while(l>1&&a[l-1]+a[j]>=dp[i-1]) l--;
			dp[i]+=(db)(pre[j-1]-pre[l-1]+(ll)a[j]*(j-l))+(db)(l-1)*dp[i-1];
		}
		dp[i]/=(db)n*(n-1)/2;
	}
	cout<<fixed<<setprecision(10)<<dp[k]<<'\n';
	while(q--){
		int x,y,c;
		cin>>x>>y>>c;
		if(c==0){
			cout<<"accept"<<'\n';
		}else if(abs(dp[c-1]-b[x]-b[y])<esp){
			cout<<"both\n";
		}else if(dp[c-1]<b[x]+b[y]){
			cout<<"accept"<<'\n';
		}else{
			cout<<"reselect\n";
		}
	}
	return 0;
}