//O(nlog(n))
给定一个长度为 n 的数组 a1,a2,…,an，问其中的最长上升子序列的长度。也就是说，我们要找到最大的 m 以及数组 p1,p2,…,pm，满足 1≤p1<p2<⋯<pm≤n 并且 ap1<ap2<⋯<apm。
int a[N],n;
vector<int> dp;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i){
        auto it=lower_bound(dp.begin(),dp.end(),a[i])-dp.begin();
        if(it==(int)dp.size()) dp.push_back(a[i]);
        else dp[it]=a[i];
    }
    printf("%d",(int)dp.size());
    return 0;
}

//O(n*n)
int a[N],n,dp[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) dp[i]=1;
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
    }
    printf("%d",*max_element(dp+1,dp+1+n));
    return 0;
}