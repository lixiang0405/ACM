//请问 [l,r] 中有多少个数字 a 满足数字中存在 3 个连续的数位 ai,ai+1,ai+2 

//使得 ai<ai+1<ai+2，其中 ai 表示 a 从左到右数第 i 位上的值。

ll l,r,dp[N][10][3],mi[N];

ll solve(ll n){
    if(!n) return 0;
    ll res=0;
    vector<int> a;
    while(n){
        a.push_back(n%10);
        n/=10;
    }
    reverse(a.begin(),a.end());
    int m=a.size();
    bool ok=false;
    for(int i=0;i<m;++i){
        if(ok) {res+=mi[m-i-1]*a[i];continue;}
        for(int j=0;j<a[i];++j){
            memset(dp,0,sizeof(dp));
            if(!i&&!j) dp[0][0][0]=1;
            else if(!i) dp[0][j][1]=1;
            else if(i==1) 
                if(j>a[i-1]) dp[1][j][2]=1;
                else dp[1][j][1]=1;
            else 
                if(j>a[i-1]&&a[i-1]>a[i-2]){
                    res+=mi[m-1-i];
                    continue;
                }else if(j>a[i-1]){
                    dp[i][j][2]=1;
                }else{
                    dp[i][j][1]=1;
                }
            for(int k=i+1;k<m;++k){
                for(int f=0;f<10;++f){
                    for(int p=0;p<3;++p){
                        if(dp[k-1][f][p]){
                            for(int x=0;x<10;++x){
                                if(p==1){
                                    if(x>f) dp[k][x][2]+=dp[k-1][f][p];
                                    else dp[k][x][1]+=dp[k-1][f][p];
                                }else if(p==2){
                                    if(x>f) res+=dp[k-1][f][p]*mi[m-1-k];
                                    else dp[k][x][1]+=dp[k-1][f][p];
                                }else{
                                    if(!x) dp[k][0][0]+=dp[k-1][f][p];
                                    else dp[k][x][1]+=dp[k-1][f][p];
                                }
                            }
                        }
                    }
                }
            }
        }
        if(i>=2&&a[i]>a[i-1]&&a[i-1]>a[i-2]) ok=true;
    }
    if(ok) res++;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    mi[0]=1;
    for(int i=1;i<=N;++i)
    mi[i]=mi[i-1]*10;
    scanf("%lld%lld",&l,&r);
    printf("%lld",solve(r)-solve(l-1));
	return 0;
}