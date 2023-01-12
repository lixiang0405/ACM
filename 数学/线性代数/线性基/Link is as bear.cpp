/*
熊才学院著名的熊魔法师林克最近学习了新的魔法。
也就是说，给定一个包含 n 个元素 a1,...,an 的数组 a，Link 可以施展以下魔法：
Link 可以选择两个整数 l,r 使得 1≤l≤r≤n，使得所有 ai=xor(l,r) 
其中 l≤i≤r 和 xor(l,r) 表示按位异或 (⊕)[l,r] 中的所有元素。
更正式地说，xor(l,r)=al⊕al+1⊕...⊕ar。
林克可以随时施展这个魔法（可能为零），并且可以任意选择 l,r。
然而，由于林克有一种强迫症（OCD），他希望在手术后所有元素都变得相同。
现在，他想知道这个相同值的最大值。
更重要的是，Link 发现给定数组有一个奇怪的性质：总是存在至少一对 x,y(x≠y) 使得 ax=ay。
*/

//首先对于不需要的两个数或需要的两个数及以上可以将他们通过两次或多次操作都变成0
//但凡出现了0，因为总是多个一起出现，我们便可以将需要的数挪到0的一侧，把不需要的数字删掉
//如果没有出现0，只有可能是1010101010....这种情况，因为至少有一对x，y ax=ay 所以不可能两个都取
//如果一个取一个不取，交换两者位置可以保证出现00，如果两个都不取那么可以两个都取，保证有11，那么可以转化成0
//具体地101010101010 如果a2=a6 111011101010 -> 1000100001010.....

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

ll a[N];

void solve(){
	int n;
	cin>>n;
	b.init();
	rep(i,1,1+n){
		cin>>a[i];
		b.insert(a[i]);
	}
	cout<<b.querymax(0)<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
} 