/*
小 E 与小 W 进行一项名为 E&D 游戏。
游戏的规则如下：桌子上有 2n 堆石子，编号为 1∼2n。
其中，为了方便起见，我们将第 2k−1 堆与第 2k 堆（1≤k≤n）视为同一组。
第 i 堆的石子个数用一个正整数 Si 表示。
一次分割操作指的是，从桌子上任取一堆石子，将其移走。
然后分割它同一组的另一堆石子，从中取出若干个石子放在被移走的位置，
组成新的一堆。操作完成后，所有堆的石子数必须保证大于 0。
显然，被分割的一堆的石子数至少要为 2。两个人轮流进行分割操作。
如果轮到某人进行操作时，所有堆的石子数均为 1，则此时没有石子可以操作，判此人输掉比赛。
小 E 进行第一次分割。他想知道，是否存在某种策略使得他一定能战胜小 W。
因此，他求助于小 F，也就是你，请你告诉他是否存在必胜策略。
例如，假设初始时桌子上有 4 堆石子，数量分别为 1,2,3,1。
小 E 可以选择移走第 1 堆，然后将第 2 堆分割（只能分出 1 个石子）。
接下来，小 W 只能选择移走第 4 堆，然后将第 3 堆分割为 1 和 2。
最后轮到小 E，他只能移走后两堆中数量为 1 的一堆，将另一堆分割为 1 和 1。
这样，轮到小 W 时，所有堆的数量均为 1，则他输掉了比赛。故小 E 存在必胜策略。
*/

int a[N],sg[N][N];

int calc(int l,int r){
	if(sg[l][r]!=-1) return sg[l][r];
	set<int> s;
	sg[l][r]=0;
	rep(k,1,l) s.insert(calc(l-k,k));
	rep(k,1,r) s.insert(calc(k,r-k));
	while(s.count(sg[l][r])) sg[l][r]++;
	return sg[l][r];
}

int calc2(int l,int r,int d){
	if(d==-1) return 0;
	if((l&(1<<d))||(r&(1<<d))){
		int ans=calc2(l&((1<<d)-1),r&((1<<d)-1),d-1);
		if(ans==d) ans++;
		return ans;
	}else return calc2(l,r,d-1);
}

void solve(){
	int n;
	scanf("%d",&n);
	rep(i,1,1+n) scanf("%d",&a[i]);
	int ans=0;
	for(int i=1;i<=n;i+=2) ans^=calc2(a[i]-1,a[i+1]-1,30);
	if(ans==0){
		puts("NO");
	}else puts("YES");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	// memset(sg,-1,sizeof(sg));
	// rep(i,1,1+32) {
	// 	rep(j,1,1+32){
	// 		set<int> s;
	// 		assert(calc(i,j)==calc2(i-1,j-1,30));
	// 		cout<<calc(i,j)<<" ";
	// 	}
	// 	cout<<'\n';
	// }
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
	return 0;
} 