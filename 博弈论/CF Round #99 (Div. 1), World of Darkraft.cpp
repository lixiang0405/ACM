/*
H×W 的棋盘中每个点都是L, R, X三者之一。
两人轮流选一个点，若为 L 则向左下和右上发射激光，R 右下和左上发射，
X则相当于LR的组合，同时向四个方向发射。激光所至的点会被摧毁，
已摧毁的点或棋盘边界才会挡住激光。
若在某回合开始时所有点都被摧毁，则该人失败。
问先手是否有必胜策略？输出整个局面的SG值。
*/

char g[N][N];
int sg[N][N][N][N][2];
int h,w;
//x+y,x-y+w

int calc(int x1,int x2,int y1,int y2,int d){
	if(x1>x2||y1>y2) return 0;
	int &v=sg[x1][x2][y1][y2][d];
	if(v!=-1) return v;
	v=0;
	set<int> s;
	rep(i,1,1+h) rep(j,1,1+w){
		if(i+j>=x1&&i+j<=x2&&i-j+w>=y1&&i-j+w<=y2&&(i+j)%2==d){
			//cout<<i<<" "<<j<<'\n';
			int x=i+j,y=i-j+w;
			if(g[i][j]=='L'){
				s.insert(calc(x1,x-1,y1,y2,d)^calc(x+1,x2,y1,y2,d));
			}else if(g[i][j]=='R'){
				s.insert(calc(x1,x2,y1,y-1,d)^calc(x1,x2,y+1,y2,d));
			}else{
				s.insert(calc(x1,x-1,y1,y-1,d)^calc(x1,x-1,y+1,y2,d)^calc(x+1,x2,y1,y-1,d)^calc(x+1,x2,y+1,y2,d));
			}
		}
	}
	while(s.count(v)) v++;
	return v;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	memset(sg,-1,sizeof(sg));
	cin>>h>>w;
	rep(i,1,1+h){
		string s;
		cin>>s;
		rep(j,1,1+w){
			g[i][j]=s[j-1];
		}
	}
	cout<<(calc(2,h+w,1,h+w-1,0)^calc(2,h+w,1,h+w-1,1))<<'\n';
	return 0;
}