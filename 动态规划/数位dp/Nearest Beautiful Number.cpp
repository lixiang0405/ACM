/*给你一个整数n。求最小整数x，使x≥n而数字x是k-美丽的。
如果没有前导零的十进制表示包含
不超过k个不同的数字。如果k=2，则数字34344435555777和21是k-美丽的
而数字120445435和998244353不是.*/

int t,k,vis[10],sz;
ll n,ans;
vector<int> a;

bool dfs(int s,int lag,int cnt,ll res){
    if(s==sz){
        ans=res;
        return true;
    }
    for(int i=lag?0:a[s];i<10;++i){
        int ncnt=cnt;
        vis[i]++;
        if(vis[i]==1) ncnt++;
        if(ncnt<=k&&dfs(s+1,lag|i>a[s],ncnt,res*10+i))
            return true;
        vis[i]--;
    }
    return false;
}

void solve(){
    memset(vis,0,sizeof(vis));
    scanf("%lld%d",&n,&k);
    a.clear();
    while(n){
        a.push_back(n%10);
        n/=10;
    }
    reverse(a.begin(),a.end());
    sz=a.size();
    dfs(0,0,0,0);
    printf("%lld\n",ans);
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