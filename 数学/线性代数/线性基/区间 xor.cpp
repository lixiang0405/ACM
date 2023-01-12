/*给你 n 个数 a1,a2,…,an。q 个询问，每次询问，
问 al,al+1,…,ar 选一个子集，最大的异或和是多少。*/

const int B = 60;
struct lb {
	ll num[B + 1];
	int t[B + 1];
	void insert(ll x, int t_) {
		for (int i = B - 1; i >= 0; --i){
			if(x & (1LL << i)) {
				if(num[i] == 0) { 
					num[i] = x; 
					t[i] = t_;
					return;
				}else {
					if(t[i] < t_){
						swap(t[i], t_);
						swap(num[i], x);
					}
					x ^= num[i]; 
				}
			}
		}
	}

	ll querymax(int t_, ll x = 0){
		for (int i = B - 1; i >= 0; --i){
			if(t[i] >= t_) x = max(x, x ^ num[i]);
		}
		return x;
	}
}b;

ll ans[N],a[N];
vector<pii> que[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	int n,q;
	scanf("%d%d",&n,&q);
	rep(i,1,1+n) scanf("%lld",&a[i]);
	rep(i,1,1+q){
		int l,r;
		scanf("%d%d",&l,&r);
		que[r].pb({l,i});
	}
	rep(i,1,1+n){
		b.insert(a[i],i);
		for(auto [l,id]:que[i]){
			ans[id]=b.querymax(l);
		}
	}
	rep(i,1,1+q) printf("%lld\n",ans[i]);
	return 0;
} 