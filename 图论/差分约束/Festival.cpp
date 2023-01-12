/*
现在，他要你答出：所有参赛者最多能达到多少种不同的成绩，

而不违背他给的条件。（他们中的一些人可能平局，

也就是同时到达终点，这种情况只算有一种成绩）。

Byteasar 告诉你，所有参赛者的成绩都是整数秒。

他还会为你提供了一些参赛者成绩的关系。

具体是：他会给你一些数对 (A,B)，表示 A 的成绩正好比 B 快 1 秒；

他还会给你一些数对 (C,D)，表示 C 的成绩不比 D 慢。

而你要回答的是：所有参赛者最多能达到多少种不同的成绩，

而不违背他给的条件。请你编程解决这个谜题。
*/

int g[N][N],vis[N];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    int n,m1,m2;
    scanf("%d%d%d",&n,&m1,&m2);
    rep(i,1,1+n) rep(j,1,1+n) g[i][j]=(i==j)?0:1<<29;
    rep(i,1,1+m1){
        int a,b;
        scanf("%d%d",&a,&b);
        //a=b-1 a<=b-1 b<=a+1
        g[b][a]=min(g[b][a],-1);
        g[a][b]=min(g[a][b],1);
    }
    rep(i,1,1+m2){
        int c,d;
        scanf("%d%d",&c,&d);
        //c<=d
        g[d][c]=min(g[d][c],0);
    }
    rep(k,1,1+n) rep(i,1,1+n) rep(j,1,1+n) g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    rep(i,1,1+n){
        //有负环说明无解
        if(g[i][i]<0){
            printf("NIE\n");
            return 0;
        }
    }
    int ans=0;
    rep(i,1,1+n){
        VI vt;//判断是否在一个强连通分量里面，一个强连通分量内最小距离为0，最大为maxx，并且值是连续的
        if(!vis[i]){
            rep(j,1,1+n){
                if(g[i][j]<=n&&g[j][i]<=n){
                    vt.pb(j);
                    vis[j]=1;
                }
            }
            int maxx=0;
            for(auto u:vt){
                for(auto v:vt){
                    maxx=max(maxx,g[u][v]);
                }
            }
            ans+=maxx+1;
        }
    }
    printf("%d\n",ans);
    return 0;
} 
