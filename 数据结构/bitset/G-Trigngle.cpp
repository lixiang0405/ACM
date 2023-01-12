/*
朗读
给你一个简单的无向图 G，有 N 个顶点。
G 以 N×N 邻接矩阵 A 的形式给出。
也就是说，如果 A{i,j}是 1， 在顶点 i 和 j 之间有一条边
如果 A{i,j}为 0 不存在

求满足 1 <= i < j < k <= N 的整数三元组 (i,j,k)的个数，
使得顶点 i和 j 之间有一条边，顶点 j 和 k 之间有边
，以及顶点 i 和 k 之间有边。
*/

bitset<3005> in[3005]; 
int g[3005][3005],n;

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		string s;
		cin>>s;
		for(int j=1;j<=n;++j){
			g[i][j]=s[j-1]-'0';
			if(g[i][j])
				in[i][j]=1;
		}
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){
			if(g[i][j])
				ans+=(ll)(in[i]&in[j]).count();
		}
	}
	cout<<ans/3<<endl;
	return 0;
}