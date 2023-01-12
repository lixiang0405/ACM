//https://atcoder.jp/contests/abc248/tasks/abc248_f?lang=en
/*
给定一个大于或等于 2 的整数 N 和一个素数 P。
考虑下图所示的具有 2N 个顶点和 (3N-2) 条边的图 G。

更具体地说，边连接顶点如下，其中顶点标记为 Vertex 1, Vertex 2, ..., Vertex 2N，
边标记为 Edge 1, Edge 2, ..., Edge (3N-2)。
对于每个 1 ≤ i ≤ N−1，边 i 连接顶点 i 和顶点 i+1。
对于每个 1 ≤ i ≤ N−1，边 (N-1+i) 连接顶点 N+i 和顶点 N+i+1.
对于每个 1 ≤ i ≤ N，边 (2N-2+i) 连接顶点 i 和顶点 N+i。
对于每个 i=1,2,..... ,N-1，解决以下问题。
找出方法数，以 P 为模，准确地删除 G 的 3N-2 条边中的 i，以使结果图仍然是连通的。
N <= 3000
*/

int n,p;
ll dp[N][N*3][2];//前i个点删了j条边,0/1前面所有边是否联通

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>p;
	dp[1][0][0]=1;
	dp[1][1][1]=1;
	for(int i=2;i<=n;++i){
		for(int j=1;j<=3*n-2;++j){
			if(j-3>=0)//加三条边
				dp[i][j][1]=(dp[i][j][1]+dp[i-1][j-3][0]+dp[i-1][j-3][1])%p;
			if(j>=2) dp[i][j][1]=(dp[i][j][1]+dp[i-1][j-2][1]*3)%p;//加两条边
			if(j>=2)
				dp[i][j][0]=(dp[i-1][j-2][0]+dp[i][j][0])%p;
			dp[i][j][0]=(dp[i][j][0]+dp[i-1][j-1][1]*2)%p;//加一条边
		}
	}
	for(int i=1;i<=n-1;++i){
		cout<<dp[n][3*n-2-i][1]%p<<" ";
	}
	return 0;
}