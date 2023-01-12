//给你两个正整数A和B,找到最小的X+Y使得B+Y是A+X的倍数
//1.如果B<=A那么只对B加最优
//2.X+Y最小值为(B+A+X-1)/(A+X)*(A+X)-B+X 将B进行上取整的根号分块
//(B+A+X-1)/(A+X)固定 X越小越优

int t;

void solve(){
    int a,b;
    cin>>a>>b;
    if(b<=a){
        cout<<a-b<<'\n';
    }else{
        int ans=1e9,r;
        for(int l=1;l<=b;l++){
            int d=(b+l-1)/l;
            int r;
            if(d-1){
                r=(b-1)/(d-1);
            }else r=l;
            if(l>=a)
                ans=min(ans,d*l-b+l-a);
            else if(r>=a) ans=min(ans,d*a-b); 
            l=r;
        }
        cout<<ans<<'\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>t;
    while(t--){
        solve();
    }
	return 0;
}