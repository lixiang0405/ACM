//给你 n 个数 a1,a2,…,an，任选一个子集（包括空集）求它们的异或和，输出其中第 k 小的数（从0开始计数）。

const int B = 60;
struct lb {
	ll num[B + 1];
	int zero = 0;
	void init() {
		memset(num, 0, sizeof(num));
		zero = 0;
	}

	bool insert(ll x) {
		for (int i = B - 1; i >= 0; --i){
			if(x & (1LL << i)) {
				if(num[i] == 0) { num[i] = x; return true; }
				x ^= num[i]; 
			}
		}
		zero++;
		return false;
	}

	ll querymin(ll x){//给一个x求a1-an子集异或最小值
		for (int i = B - 1; i >= 0; --i){
			x = min(x, x ^ num[i]);
		}
		return x;
	}

	ll querymax(ll x){
		for (int i = B - 1; i >= 0; --i){
			x = max(x, x ^ num[i]);
		}
		return x;
	}

	ll kthmax(ll k){
		ll x = 0;
		k >>= zero;
		vector<ll> p;
		for(int i = 0; i <= B - 1; ++i){
			if(num[i] != 0) p.push_back(num[i]);
		}
		int m = p.size();
		for(int i = m - 1; i >= 0; --i){
			if(k & (1LL << i)){
				x = max(x, x ^ p[i]);
			}else{
				x = min(x, x ^ p[i]);
			}
		}
		return x;
	} 
}b;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	int n;
	ll k;
	scanf("%d%lld",&n,&k);
	rep(i,1,1+n){
		ll x;
		scanf("%lld",&x);
		b.insert(x);
	}
	printf("%lld",b.kthmax(k));
	return 0;
} 