/*蜗蜗一共有 n 天假期，在假期的第 i 天摸鱼他会得到 ai 的快乐值。

如果蜗蜗每天都摸鱼的话，他会有愧疚感，所以蜗蜗制定了这么个计划：

对于每一天，蜗蜗都有一个列表，如果蜗蜗在列表中的每一天都在摸鱼的话，这一天蜗蜗就不能摸鱼。

现在请问蜗蜗如何摸鱼，使得他能获得的快乐值总和最大？请求出快乐值总和最大是多少。*/

int dp[N],a[M],n,b[M],ans=0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",&a[i]);
	for(int i=0;i<n;++i){
		int d,cnt=0;
		scanf("%d",&d);
		for(int j=0;j<d;++j){
			int tmp;
			scanf("%d",&tmp);
			tmp--;
			cnt+=1<<tmp;
		}
		b[i]=cnt;
	}
	for(int i=1;i<(1<<n);++i){
		bool flag=false;
		for(int j=0;j<n;++j){
			if((i&(1<<j))&&b[j]&&(b[j]&i)==b[j]) flag=true;
		}
		if(flag) continue;
		for(int j=0;j<n;++j){
			if(i&(1<<j)){
				int tmp=i-(1<<j);
				dp[i]=max(dp[i],dp[tmp]+a[j]);
				ans=max(ans,dp[i]);
			}
		}
	}
	printf("%d",ans);
    return 0;
}