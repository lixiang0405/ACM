/*
给出一组包含 m 个不等式，有 n 个未知数的形如：
Xu-Xv<=Y的不等式组，
求满足这个不等式组的非负解，并且每个变量尽量小。
*/

int n,m;
vector<array<int,3>> e; 
int dis[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v,x;
		scanf("%d%d%d",&u,&v,&x);
		//u<=v+x求出来是最大值
		//e.push_back({u,v,x})
		//v>=u-x求出来是最小值
		e.push_back({u,v,x});
	}
	/*
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e.push_back({v,u,w});//连一条反边
	}
	for(int i=1;i<=n;i++){
		e.push_back({i,0,0});//反边
		x[i] = (1<<30);
	}
	for(int i=1;i<=n;i++){
		for(auto pi : e){
			int u = pi.x,v = pi.y,w = pi.w;
			x[u] = min(x[u],x[v]+w);
		}
	}
	......
	for(int i=1;i<=n;i++){
		printf("%d ",x[0]-x[i]);//0-i
	}
	*/
	for(int i=1;i<=n;++i) dis[i]=-(1<<30);
	//非负解xi>=0:令它减去一个数xi-x0>=0
	for(int i=1;i<=n;++i)
		e.push_back({0,i,0});
	for(int i=0;i<=n;++i){
		for(auto [u,v,w]:e){
			//u<=v+x求出来是最大值
			//e.push_back({u,v,x})
			//v>=u-x求出来是最小值
			dis[v]=max(dis[v],dis[u]-w);
		}
	}
	for(auto [u,v,w]:e){
		if(dis[u]-dis[v]>w){
			printf("-1");
			return 0;
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d ",dis[i]-dis[0]);
	}
	return 0;
} 