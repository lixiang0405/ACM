/*
有n种物品要放到一个袋子里，袋子的总容量为m，
第i种物品的体积为vi，把它放进袋子里会获得wi的收益，
每种物品能用无限多次，问如何选择物品，
使得在物品的总体积不超过m的情况下，获得最大的收益？请求出最大收益。
*/

//裸题

int n,m,val[N],w[N],dp[N],ans=0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&w[i],&val[i]);
	for(int i=1;i<=n;++i){
		for(int j=0;j<=m;++j){
			if(j>=w[i]) dp[j]=max(dp[j-w[i]]+val[i],dp[j]);
			ans=max(ans,dp[j]);
		}
	}
	printf("%d",ans);
    return 0;
}


//1673C - Palindrome Basis
/*You are given a positive integer n. 

Let's call some positive integer a without leading zeroes palindromic if it remains the same after reversing the order of its digits. 

Find the number of distinct ways to express n as a sum of positive palindromic integers. 

Two ways are considered different if the frequency of at least one palindromic integer is different in them. 

For example, 5=4+1 and 5=3+1+1 are considered different but 5=3+1+1 and 5=1+3+1 are considered the same.

Formally, you need to find the number of distinct multisets of positive palindromic integers the sum of which is equal to n.

Since the answer can be quite large, print it modulo 10^9+7.*/

int t,c[N],cnt=0,n;
ll dp[N];

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	for(int i=1;i<=40000;++i){
		string a=to_string(i);
		reverse(a.begin(),a.end());
		int x=stoi(a);
		if(x==i) c[++cnt]=i; 
	}
	dp[0]=1;
	for(int i=1;i<=cnt;++i){
		for(int j=c[i];j<=4e4;++j){
			dp[j]=(dp[j-c[i]]+dp[j])%mod;
		}
	}
	
	cin>>t;
	while(t--){
		cin>>n;
		cout<<dp[n]<<endl;
	}
	return 0;
}