//请问 [l,r] 中有多少个数字满足数字中任意相邻两个数位的差的绝对值不超过 2。

ll l,r,dp[N][10][2];

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
    bool ok=true;
    for(int i=0;i<m&&ok;++i){
        for(int j=0;j<a[i];++j){
            if(i&&abs(a[i-1]-j)>2) continue;
            memset(dp,0,sizeof(dp));
            if(!i&&!j) dp[i][j][0]=1;
            else dp[i][j][1]=1;
            for(int k=i+1;k<m;++k){
                for(int x=0;x<10;++x){
                    for(int y=0;y<2;++y){
                        if(dp[k-1][x][y]){
                            for(int z=0;z<10;++z){
                                if(y&&abs(z-x)<=2) dp[k][z][y]+=dp[k-1][x][y];
                                if(!y){
                                    if(!z){
                                        dp[k][0][0]+=dp[k-1][0][0];
                                    }else{
                                        dp[k][z][1]+=dp[k-1][0][0];
                                    }
                                }
                            }
                        }
                    }
                }
            }  
            for(int k=0;k<10;++k)
            res+=dp[m-1][k][1];
        }
        if(i&&abs(a[i]-a[i-1])>2) ok=false;
    }
    if(ok)
    res++;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%lld%lld",&l,&r);
    printf("%lld",solve(r)-solve(l-1));
	return 0;
}