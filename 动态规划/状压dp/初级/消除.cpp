/*桌面上有 n 个方块，蜗蜗想把它们都消除掉。每个方块有个权值，第 i 个方块的权值等于 ai。每一次消除蜗蜗有两种选择：

1.选择一个还没有被消除的方块 i，付出 ai 的代价把它消除；

2.选择两个还没有被消除的方块 i,j(i≠j)，付出 ai xor aj 的代价把它们消除；

请问蜗蜗最少需要花费多少代价，能把 n 个方块都消除掉？*/

//O(n*2^n)
int dp[N],a[M],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<(1<<n);++i){
		int c=__builtin_ctz(i);//后导零因为最后面的1相对于前面的1更后出现
		dp[i]=dp[i-(1<<c)]+a[c];
		for(int j=0;j<n;++j){
			if((i&(1<<j))&&j!=c){
				int tmp=i-(1<<j)-(1<<c);
				dp[i]=min(dp[i],dp[tmp]+(a[c]^a[j]));
			}
		}
	}
	printf("%d",dp[(1<<n)-1]);
    return 0;
}


//O(n*n*2^n)
int dp[N],a[M],n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
	}
	memset(dp,0x3f3f3f3f,sizeof(dp));
	/*for(int i=1,j=0;i<(1<<n);i<<=1,j++){
		dp[i]=a[j];
	}
	for(int i=1,j=0;i<(1<<n);i<<=1,j++){
		for(int k=i<<1,p=j+1;k<(1<<n);k<<=1,p++){
			dp[i+k]=a[j]^a[p];
		}
	}*/
	dp[0]=0;
	for(int i=1;i<(1<<n);++i){
		int c=__builtin_popcount(i);//枚举取到第几个的作用
		for(int j=0;j<n;++j){
			if(i&(1<<j)){
				int tmp=i-(1<<j);
				dp[i]=min(dp[i],dp[tmp]+a[j]);
			}
		}
		if(c>=2)
		for(int j=0;j<n;++j){
			if(i&(1<<j))
			for(int k=j+1;k<n;++k)
			if(i&(1<<k))
			dp[i]=min(dp[i-(1<<j)-(1<<k)]+(a[j]^a[k]),dp[i]);
		}
	}
	printf("%d",dp[(1<<n)-1]);
    return 0;
}