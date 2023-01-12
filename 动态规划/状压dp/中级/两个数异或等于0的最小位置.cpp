/*
给你 n 个数a1,a2,…,an。对于每个数i(1≤i≤n)，
找到另外一个数j(j≠i)，满足ai&aj=0，或者说不存在。
第一行一个整数n(1≤n≤1e6)。
接下来一行n个整数a1,…,an(1≤ai≤4e6)。
*/

int n,a[N+10],pos[N+10];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
    for(int i=0;i<(1<<22);++i) pos[i]=n+1;
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        pos[a[i]]=min(i,pos[a[i]]);
    }
    for(int i=0;i<22;++i){
        for(int j=0;j<(1<<22);++j){
            if(j&(1<<i)) pos[j]=min(pos[j],pos[j-(1<<i)]);
        }
    }
    for(int i=1;i<=n;++i){
        int y=(1<<22)-a[i]-1;
        if(pos[y]>n) printf("-1 ");
        else printf("%d ",pos[y]);
    }
    return 0;
}