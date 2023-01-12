/*
Alice 和 Bob 现在在玩的游戏，主角是依次编号为 1 到 n 的 n 枚硬币。
每一枚硬币都有两面，我们分别称之为正面和反面。一开始的时候，
有些硬币是正面向上的，有些是反面朝上的。
Alice 和 Bob 将轮流对这些硬币进行翻转操作，且 Alice 总是先手。
具体来说每次玩家可以选择一枚编号为 x，要求这枚硬币此刻是反面朝上的。
对于编号 x 来说，我们总可以将 x 写成 c⋅2a⋅3b ，其中 a 和 b 是非负整数，
c 是与 2,3 都互质的非负整数，然后有两种选择：
选择整数 p,q 满足 a≥pq,p≥1 且 1≤q≤MAXQ，
然后同时翻转所有编号为 c⋅2a−pj⋅3b 的硬币，其中 j=0,1,2,…q。
选择整数 p,q 满足 b≥pq,p≥1 且 1≤q≤MAXQ，
然后同时翻转所有编号为 c⋅2a⋅3b−pj 的硬币，其中 j=0,1,2,…q。
可以发现这个游戏不能无限进行下去，当某位玩家无法继续操作上述操作时，
便输掉了游戏。作为先手的 Alice，总是希望可以在比赛开始之前就知道自己能否获胜。
她知道自己和 Bob 都是充分聪明的，所以在游戏过程中，
两人都会最优化自己的策略并尽量保证自己处于不败的情形中。
*/

int t,sg[N][N];

void solve(){
	int n,maxq;
	scanf("%d%d",&n,&maxq);
	rep(a,0,16) rep(b,0,11){
		set<int> s;
		sg[a][b]=0;
		rep(p,1,1+a){
			int cur=0;
			for(int q=1;q*p<=a&&q<=maxq;q++){
				cur^=sg[a-p*q][b];
				s.insert(cur);
			}
		}
		rep(p,1,1+b){
			int cur=0;
			for(int q=1;q*p<=b&&q<=maxq;q++){
				cur^=sg[a][b-p*q];
				s.insert(cur);
			}
		}
		while(s.count(sg[a][b])) sg[a][b]++;
	}
	int ans=0;
	rep(i,1,1+n){
		int x;
		scanf("%d",&x);
		if(!x){
			int a=0,b=0,c=i;
			while(c%2==0) c/=2,a++;
			while(c%3==0) c/=3,b++;
			ans^=sg[a][b];
		}
	}
	puts(ans?"win":"lose");
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