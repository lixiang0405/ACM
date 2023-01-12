/*
给 n 个数 a1,a2,…,an，从中任意选出一些数（非空子集），
使这些数字能分成和相等的两组。求有多少种选数的方案。
第一行一个整数 n(2≤n≤20)。
第 2 至 n+1 行，每行一个数 ai(1≤ai≤108)。
*/
 
int a[N],vis[(1<<20)+10];

void dfs(int s,int t,int sum,int mask,vector<pii> &ans){
	if(s==t){
		ans.pb({sum,mask});
		return;
	}
	dfs(s+1,t,sum+a[s],mask|(1<<s),ans);
	dfs(s+1,t,sum-a[s],mask|(1<<s),ans);
	dfs(s+1,t,sum,mask,ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	rep(i,0,n) cin>>a[i];
	vector<pii> ans1,ans2;
	dfs(0,n/2,0,0,ans1);
	dfs(n/2,n,0,0,ans2);
	sort(all(ans1));
	ans1.erase(unique(all(ans1)),ans1.end());
	sort(all(ans2));
	ans2.erase(unique(all(ans2)),ans2.end());
	for(auto [sum,mask]:ans1){
		for(auto it=lower_bound(all(ans2),pii{-sum,0});it!=ans2.end()&&it->fi==-sum;it++){
			vis[mask|it->se]=1;
		}
	}
	int ans=0;
	rep(i,1,1<<n){
		ans+=vis[i];
	}
	cout<<ans<<'\n';
	return 0;
}