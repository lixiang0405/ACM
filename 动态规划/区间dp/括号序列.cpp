/*给定一个长度为 n 的字符串 s，字符串由 (, ), [, ]组成，问其中最长的合法子序列有多长？也就是说，我们要找到最大的m，使得存在i1,i2,…,im 满足 1≤i1<i2<⋯<im≤n 并且 si1si2…sim 是一个合法的括号序列。

合法的括号序列的定义是：

空串是一个合法的括号序列。

若 A 是一个合法的括号序列，则 (A), [A] 也是合法的括号序列。

若 A, B 都是合法的括号序列，则 AB 也是合法的括号序列。*/

int dp[N][N],n,ans=0;
char s[N];

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%s",&n,s);
	for(int l=1;l<n;++l){
		for(int i=0;i<n-l;++i){
			if((s[i]=='('&&s[i+l]==')')||(s[i]=='['&&s[i+l]==']'))
			dp[i][i+l]=dp[i+1][i+l-1]+2;
			for(int j=i;j<i+l;++j){
				dp[i][i+l]=max(dp[i][i+l],dp[i][j]+dp[j+1][i+l]);
			}
		}
	}
	printf("%d",dp[0][n-1]);
	return 0;
}