/*链接：https://ac.nowcoder.com/acm/contest/11251/E
来源：牛客网

小红拿到了一个数组，她有以下一种操作：
将[l,r]区间所有数变成该区间所有数的lcm，并输出这个lcm。
区间lcm指区间内所有数的最小公倍数。
一共q次操作。

第一行输入两个正整数n,qn,q，代表数组长度和查询次数。
第二行输入nn个正整数，代表小红拿到的数组。
接下来的qq行，每行输入两个正整数l,r，用空格隔开。

1<= n,q,ai <=200000 
​1<= l <= r <=200000
保证数据随机生成。*/
   

//812ms
template <typename T> void inline read(T& x){
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}
  
int qpow(int a, int n, int p){
    int ans = 1;
    a %= p;
    while (n){
        if (n & 1)
            ans =1ll* ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}
 
struct node{
    int l, r;
    mutable vector<pii> v;
    node(int l, int r, vector<pii> &v) : l(l), r(r), v(v) {}
    bool operator<(const node &o) const { return l < o.l; }
};
  
set<node> tre;
vector<pii> a;
auto split(int pos){
    auto it = tre.lower_bound(node(pos, 0, a));
    if (it != tre.end() && it->l == pos)
        return it;
    it--;
    int l = it->l, r = it->r;
    vector<pii> v = it->v;
    tre.erase(it);
    tre.insert(node(l, pos - 1, v));
    return tre.insert(node(pos, r, v)).first;
}
  
int assign(int l, int r){
    auto end = split(r + 1), begin = split(l);
    vector<pii> v;
    for(auto it=begin;it!=end;it++){
        //v=(v*it->v/gcd(v,it->v))%mod;
		int l=0;
		vector<pii> tmp;
		for(auto &&[i,j]:it->v){
			while(l<(int)v.size()&&v[l].first<i) tmp.push_back(v[l]),l++;
            tmp.push_back({i,j});
			if(l<(int)v.size()&&v[l].first==i) tmp.back().second=max(tmp.back().second,v[l].second),l++;
        }
		while(l<(int)v.size()){
			tmp.push_back(v[l]);
			l++;
		}
		v=tmp;
    }
    int ans=1;
    tre.erase(begin, end);
    tre.insert(node(l, r, v));
	for(auto &&[i,j]:v){
		ans=1ll*ans*qpow(i,j,mod)%mod;
	}
    return ans;
}
  
int cnt = 0;
int primes[N + 5];
bool f[N + 5];
 
void get_primes(int x) {
    //线性筛质数
    for (int i = 2; i <= x ; ++i) {
        if (!f[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && primes[j] * i <= x; ++j) {
            f[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
 
int n,m;
  
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read(n),read(m);
    get_primes(sqrt(20000));
    vector<pii> vt,v;
    for(int i=1;i<=n;++i){
        int x;
        read(x);
        vt.push_back({x,i});
    }
    stable_sort(vt.begin(),vt.end());
    for(int i=0;i<n;++i){
        if(i==0||vt[i].first!=vt[i-1].first){
            v.clear();
            int x=vt[i].first;
            for(int i=0;i<cnt&&x>=primes[i];++i){
                if(x%primes[i]==0){
                    int c=0;
                    while(x%primes[i]==0){
                        x/=primes[i];
                        c++;
                    }
                    v.push_back({primes[i],c});
                }
            }
            if(x>2){
                v.push_back({x,1});
            }
        }
        tre.insert(node(vt[i].second,vt[i].second,v));
    }
    while(m--){
        int l,r;
        read(l),read(r);
        printf("%d\n",assign(l,r));
    }
    return 0;
}


//761ms
  
template <typename T> void inline read(T& x){
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}
 
int cnt = 0;
int primes[N + 5];
bool f[N + 5];

inline void get_primes(int x) {
	//线性筛质数
	for (int i = 2; i <= x ; ++i) {
		if (!f[i]) primes[cnt++] = i;
		for (int j = 0; j < cnt && primes[j] * i <= x; ++j) {
			f[i * primes[j]] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

int qpow(int a, int n, int p){
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


struct node{
    int l, r;
    mutable vector<pii> v;
    
    node(int l, int r, int x) : l(l), r(r){
        if(x==0) return;
        for(int i=0;i<cnt&&i*i<=x;++i){
            if(x%primes[i]==0){
                int c=0;
                while(x%primes[i]==0){
                    x/=primes[i];
                    c++;
                }
                v.push_back({primes[i],c});
            }
        }
        if(x>1){
            v.push_back({x,1});
        }
    }
    
    node(int l, int r, vector<pii> &v) : l(l), r(r) ,v(v){}

    bool operator<(const node &o) const { return l < o.l; }

    void merge(const node &o){
        int l=0;
        vector<pii> tmp;
		for(auto &&[i,j]:o.v){
			while(l<(int)v.size()&&v[l].first<i) tmp.push_back(v[l]),l++;
            tmp.push_back({i,j});
			if(l<(int)v.size()&&v[l].first==i) tmp.back().second=max(tmp.back().second,v[l].second),l++;
        }
		while(l<(int)v.size()){
			tmp.push_back(v[l]);
			l++;
		}
		v=tmp;
    }

    int ans(){
        ll res=1;
        for(auto &&[i,j]:v){
            res=res*qpow(i,j,mod)%mod;
        } 
        return res;
    }

};
 
set<node> tre;

inline auto split(int pos){
    auto it = tre.lower_bound(node(pos, 0, 0));
    if (it != tre.end() && it->l == pos)
        return it;
    it--;
    int l = it->l, r = it->r;
    vector<pii> v = it->v;
    tre.erase(it);
    tre.insert(node(l, pos - 1, v));
    return tre.insert(node(pos, r, v)).first;
}
 
inline int assign(int l, int r){
    auto end = split(r + 1), begin = split(l);
    node res(l,r,0);
    for(auto it=begin;it!=end;it++){
        //v=(v*it->v/gcd(v,it->v))%mod;
        res.merge(*it);
	}
    tre.erase(begin, end);
    tre.insert(res);
    return res.ans();
}

int n,m;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read(n),read(m);
    get_primes(sqrt(20000));
    for(int i=1;i<=n;++i){
        int x;
		read(x);
        tre.insert(node(i,i,x));
    }
    while(m--){
        int l,r;
        read(l),read(r);
        printf("%d\n",assign(l,r));
    }
    return 0;
}