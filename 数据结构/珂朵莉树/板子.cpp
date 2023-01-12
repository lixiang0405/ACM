区间加
区间赋值
求区间第k大值
求区间n次方和
 
struct node{
    ll l, r;
    mutable ll v;
    node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
    bool operator<(const node &o) const { return l < o.l; }
};

set<node> tre;

auto split(ll pos){
    auto it = tre.lower_bound(node(pos, 0, 0));
    if (it != tre.end() && it->l == pos)
        return it;
    it--;
    ll l = it->l, r = it->r, v = it->v;
    tre.erase(it);
    tre.insert(node(l, pos - 1, v));
    return tre.insert(node(pos, r, v)).first;
}

void assign(ll l, ll r, ll v){
    auto end = split(r + 1), begin = split(l);
    tre.erase(begin, end);
    tre.insert(node(l, r, v));
}

ll qpow(ll a, ll n, ll p){
    ll ans = 1;
    a %= p;
    while (n){
        if (n & 1)
            ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}

ll n, m, seed, vmax;

ll rnd(){
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}

void add(ll l, ll r, ll v){
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}

ll kth(ll l, ll r, ll k){
    auto end = split(r + 1);
    vector<pair<ll, ll>> v;
    for (auto it = split(l); it != end; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
    {
        k -= v[i].second;
        if (k <= 0)
            return v[i].first;
    }
}

ll sum_of_pow(ll l, ll r, ll x, ll y){
    ll tot = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        tot = (tot + qpow(it->v, x, y) * (it->r - it->l + 1)) % y;
    return tot;
}

int main(){

	cin>>n>>m>>seed>>vmax;
	
    for (int i = 1; i <= n; ++i){
        int r = rnd();
        tre.insert(node(i, i, r % vmax + 1));
    }

    for (int i = 1; i <= m; ++i){
        ll opr = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1, x, y;
        if (l > r)
            swap(l, r);
        if (opr == 3)
            x = rnd() % (r - l + 1) + 1;
        else
            x = rnd() % vmax + 1;
        if (opr == 4)
            y = rnd() % vmax + 1;
        if(opr==1)
            add(l, r, x);
        else if(opr==2)
            assign(l, r, x);
        else if(opr==3)
            cout<<kth(l, r, x)<<endl;
        else
			cout<<sum_of_pow(l, r, x, y)<<endl;
    }
    return 0;
}
