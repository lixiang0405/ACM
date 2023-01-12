/*
给一个边权为非负整数的无向连通图，节点编号为 1 到 N，

试求出一条从 1 号节点到 N 号节点的路径，使得路径上经过的边的权值的 XOR 和最大。

路径可以重复经过某些点或边，当一条边在路径中出现了多次时，

其权值在计算 XOR 和时也要被计算相应多的次数，具体见样例。
*/

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

int vis[N];
ll dis[N];
vector<pair<int,ll>> e[N];

void dfs(int u){
	for(auto [v,w]:e[u]){
		if(!vis[v]){
			dis[v]=dis[u]^w;
			vis[v]=1;
			dfs(v);
		}else{
			b.insert(dis[v]^dis[u]^w);
		}
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,1+m){
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		e[u].pb({v,w});
		e[v].pb({u,w});
	}
	dfs(1);
	printf("%lld",b.querymax(dis[n]));
	return 0;
} 