/*
比特山是一个旅游胜地，它一共有 n 个景点，按照海拔高度从低到高依次编号为 1 到 n。
为了更好地帮助游客们欣赏这里的风景，人们在上面搭建了 m 条缆车路线。
每条缆车路线只可能把游客们从某个海拔较低的景点运送到另一个海拔较高的景点。
在每个景点都有一家纪念品连锁商店，其中第 i 个景点的商店隶属第 ci 号公司，
两家连锁店 (i,j) 隶属同一公司当且仅当 ci=cj。每家公司都有新客优惠活动，
其中第 i 家公司对于新客的优惠红包为 wi 元，
一旦领取了隶属该公司的某家连锁店的一份红包，就不能再领取该公司所有分店的红包。
你正在 1 号景点，你将会搭乘缆车去往各个景点，每到一个景点，
你都可以领取该景点的连锁商店的新客优惠红包（包括 1 号景点）。
当然，同一家公司的红包最多只能领一次。请写一个程序，对于每个可能的终点 k，
找到一条从 1 号景点出发到达 k 号景点的游览路线，使得可以领取到总金额最多的优惠红包。

第一行包含两个正整数 n,m(2≤n≤36,1≤m≤n(n−1)/2)，分别表示景点的数量以及缆车路线的数量。
第二行包含 n 个正整数 c1,c2,…,cn(1≤ci≤n)，依次表示每个景点的商店所隶属的公司。
第三行包含 n 个正整数 w1,w2,…,wn(1≤wi≤106)，依次表示每家公司的新客优惠红包的金额。
接下来 m 行，每行两个正整数 ui,vi(1≤ui<vi≤n)，表示一条缆车路线，起点是景点 ui，
终点是景点 vi。输入数据保证任意两个景点之间最多只有一条缆车路线，
且从 1 号景点出发可以到达任意一个景点。
*/

int n,m;
int c[N],a[N],cnt[N],dp[N][M],ans[N],w[N],ww[N];
vector<int> e[N];

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    for(int i=1;i<=n;++i) scanf("%d",&ww[i]);
    for(int i=1;i<=n;++i) w[i]=ww[a[i]];
    //看得到的1w都是相同的，看不到的1（走过的地方）是不同的。
    int sz=0;
    for(int i=1;i<=n;++i){
        if(cnt[i]>=2) c[i]=sz++;
        else c[i]=-1; 
    }
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
    }
    for(int i=1;i<=n;++i){
        a[i]=c[a[i]];
    }
    dp[1][0]=0;
    for(int i=1;i<=n;++i){
        for(int j=0;j<(1<<sz);++j){
            if(dp[i][j]!=-1){
                if(a[i]==-1) dp[i][j]+=w[i];
                else{
                    if(!(j&(1<<a[i]))) dp[i][j+(1<<a[i])]=max(dp[i][j+(1<<a[i])],dp[i][j]+w[i]);
                }
                ans[i]=max(ans[i],dp[i][j]);
                for(auto v:e[i]) dp[v][j]=max(dp[v][j],dp[i][j]);
            }
        }
    }
    for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}