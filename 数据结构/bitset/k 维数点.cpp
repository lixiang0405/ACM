/*
给你 n 个点，每个点有 k 维坐标 ai,1,ai,2,…,ai,k。
对于每一维，保证所有点的坐标是 1∼n 的排列。
对于每个点，输出一共有多少个点，每一维都比它小。
注意：内存为 128MB。
*/

int a[N][5],pos[5][N];
bitset<N> b[5][N/B+5],ans,s;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    scanf("%d%d",&n,&k);
    rep(i,1,1+n){
        rep(j,0,k) scanf("%d",&a[i][j]),pos[j][a[i][j]]=i;
    }
    rep(j,0,k){
        for(int i=B;i<=n;i+=B){
            b[j][i/B]=b[j][i/B-1];//分块
            rep(f,i-B+1,i+1) b[j][i/B][pos[j][f]]=1; 
        }
    }
    rep(i,1,1+n){
        ans.set();
        rep(j,0,k){
            int t=a[i][j]/B;
            s=b[j][t];
            rep(f,t*B+1,a[i][j]) s[pos[j][f]]=1;
            ans&=s; //O(B+n/w)
        }
        printf("%d\n",ans.count());
    }
    return 0;
}
