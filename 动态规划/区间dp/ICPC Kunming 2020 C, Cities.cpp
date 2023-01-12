/*
鲍勃生活在一个混乱的国家，一排有 n 个城市，编号从 1 到 n。
这些城市由不同的领主拥有，而第i个城市目前属于ai领主。
为了简单的问题，我们假设该国有 n 个领主，他们的编号也是从 1 到 n。
有些领主可能会控制多个城市，而有些新出生的领主还没有任何城市。
显然，贪婪的领主们对自己拥有的领土数量并不满意，所以国家一直处于战争状态。
Bob 想要改变这一点，让所有城市都属于同一个领主！
Bob 可以执行一些神奇的操作来支持他的宏伟计划。
在每种魔法的帮助下，鲍勃可以做到以下几点：
选择一些具有连续索引的城市，使其属于同一个领主，并将它们分配给任何其他领主。
由于魔法真的很累人，Bob 想知道他需要使用最少多少次这样的操作才能使所有城市都属于一个领主。
*/


int t,a[N],pos[N],nxt[N],dp[N][N];

void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(i!=1&&a[i]==a[i-1]){
			n--;
			i--;
		}
		pos[a[i]]=n+1;
	}
	for(int i=n;i>=1;--i){
		nxt[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	for(int l=1;l<=n;++l){
		for(int r=l;r<=n;++r) dp[l][r]=0;
	}
	for(int d=1;d<n;++d){
		for(int l=1;l+d<=n;++l){
			int r=l+d,m=nxt[l];
			dp[l][r]=dp[l+1][r];
			while(m<=r){
				dp[l][r]=max(dp[l][r],dp[l+1][m-1]+dp[m][r]+1);
				m=nxt[m];
			}
		}
	}
	printf("%d\n",n-1-dp[1][n]);
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