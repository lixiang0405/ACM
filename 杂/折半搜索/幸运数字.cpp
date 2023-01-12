/*
四是一个幸运的数字。
你有n个数，你想选择一个子集，然后将它们加起来，
统计十进制表示的数位里有多少个4。
但是这个太简单了，所以你想对所有2n种方案，
都统计一遍，然后求出它们的总和。
*/

int a[44];

void getsum(int l,int r,int sum,vector<pii> &x){
    if(l==r){
        x.pb({0,sum});
        return;
    }
    getsum(l+1,r,sum,x);
    getsum(l+1,r,sum+a[l],x);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d",&n);
    rep(i,0,n) scanf("%d",&a[i]);
	int m=n/2;
    vector<pii> l,r;
    getsum(0,m,0,l);
    getsum(m,n,0,r);
    ll ans=0;
    for(int i=0,pw=1;i<=8;++i,pw*=10){
        auto sort=[&](vector<pii> &pre){
            static int cnt[20];
            rep(j,0,10) cnt[j]=0;
            int m=SZ(pre);
            vector<pii> cur(m);
            for(auto &c:pre) cnt[c.se/pw%10]++;
            rep(j,1,10) cnt[j]+=cnt[j-1];
            per(j,0,m) cur[--cnt[pre[j].se/pw%10]]={pre[j].se%(10*pw),pre[j].se};
            pre=cur; 
        };
        sort(l);
        sort(r);
        auto calc=[&](ll x){
            int R=SZ(r)-1;
            ll res=0;
            rep(L,0,SZ(l)){
                while(R>=0&&r[R].fi+l[L].fi>x) R--;
                res+=R+1;
            }
            return res;
        };
        ans+=calc(5*pw-1)-calc(4*pw-1)+calc(15*pw-1)-calc(14*pw-1);//小于等于
    }
    printf("%lld",ans);
    return 0;
}