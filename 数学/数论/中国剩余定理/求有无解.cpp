/*
一共T组数据，每组数据，给定n个方程，x≡ai(mod mi)。判断方程是不是有解。
*/

int t;

void solve(){
	int n;
	scanf("%d",&n);
	map<int,vector<pii>> eqns;
	for(int i=1;i<=n;++i){
		int a,m;
		scanf("%d%d",&a,&m);
		for(int j=2;j*j<=m;++j){
			if(m%j==0){
				int f=1;
				while(m%j==0) m/=j,f*=j;
				eqns[j].push_back({f,a%f}); //x%f=a%f
			}
		}
		if(m>1) eqns[m].push_back({m,a%m});
	}
	for(auto [i,j]:eqns){
		int f=max_element(j.begin(),j.end())->second;
		for(auto cur:j){
			if(f%cur.first!=cur.second){
				printf("No\n");
				return;
			}
		}
	}
	printf("Yes\n");
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