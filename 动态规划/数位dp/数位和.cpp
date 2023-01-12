/*请问 0...9 这些数字在 [l,r] 的数位中分别出现了多少次。*/

ll l,r,mi[N],ans1[10],ans2[10];

void solve(ll n,ll *ans){
    vector<int> a;
    while(n){
        a.push_back(n%10);
        n/=10;
    }
    reverse(a.begin(),a.end());
    int m=a.size();
    for(int i=0;i<m;++i){
        for(int j=0;j<i;++j){
            ans[a[j]]+=mi[m-i-1]*a[i];
        }
        for(int j=1;j<a[i];++j){
            ans[j]+=mi[m-i-1];
        }
        if(i&&a[i])
        ans[0]+=mi[m-i-1];
        if(i!=m-1){
            for(int j=1;j<=9;++j){
                ans[j]+=mi[m-i-2]*a[i]*(m-i-1);
            }
            if(i)
            ans[0]+=mi[m-i-2]*a[i]*(m-i-1);
        }
        if(!i){
            if(m>=2) ans[0]+=mi[m-2]*(a[0]-1)*(m-1);
            for(int j=1;j<m-1;++j){
                ans[0]+=mi[m-j-2]*9*(m-1-j);
            }
        }
    }
    for(int i=0;i<m;++i)
    ans[a[i]]++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%lld%lld",&l,&r);
    mi[0]=1;
    for(int i=1;i<=16;++i){
        mi[i]=mi[i-1]*10;
    }
    solve(l-1,ans1);
    solve(r,ans2);
    for(int i=0;i<10;++i)
    printf("%lld ",ans2[i]-ans1[i]);
	return 0;
}