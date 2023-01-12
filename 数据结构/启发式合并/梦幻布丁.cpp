/*n个布丁摆成一行，进行m次操作。
每次将某个颜色的布丁全部变成另一种颜色的，
然后再询问当前一共有多少段颜色。
例如颜色分别为1,2,2,1的四个布丁一共有3段颜色。*/

int a[N],n,m,ans=0;
vector<int> pos[M];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        pos[a[i]].push_back(i);
    }
    for(int i=1;i<=n+1;++i){
        ans+=a[i]!=a[i-1];
    }
    for(int i=0;i<m;++i){
        int ty;
        scanf("%d",&ty);
        if(ty==2){
            printf("%d\n",ans-1);
        }else{
            int x,y;
            scanf("%d%d",&x,&y);
            if(x==y) continue;
            if(pos[x].size()>pos[y].size()){
                pos[x].swap(pos[y]);
            }
            if(pos[y].empty()) continue;
            int col=a[pos[y][0]];
            auto modify=[&](int &p){
                ans-=(a[p]!=a[p+1])+(a[p]!=a[p-1]);
                a[p]=col;
                ans+=(a[p]!=a[p+1])+(a[p]!=a[p-1]);
            };
            for(auto &p:pos[x]){
                modify(p);
                pos[y].push_back(p);
            }
            pos[x].clear();
        }
    }
    return 0;
}

