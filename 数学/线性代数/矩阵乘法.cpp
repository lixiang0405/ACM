vector<vector<int>> mul(vector<vector<int>> &a,vector<vector<int>> &b){
	vector<vector<int>> ans(a.size(),vector<int>(b[0].size(),0));
	for(int i=0;i<a.size();++i){
		for(int j=0;j<b[0].size();++j){
			for(int k=0;k<a[0].size();++k){
				ans[i][j]=(ans[i][j]+a[i][k]*b[k][j]%mod)%mod;
			}
		}
	}
	return ans;
}

/*
在斐波那契数列中，Fib0=0,Fib1=1,Fibn=Fibn−1+Fibn−2(n>1)。

给定整数 n，求 Fibn mod 10000。

输入格式

0≤n≤2×e9
*/

vector<vector<int>> grid(2,vector<int>(2)),t(1,vector<int>(2));

void init(){
	grid[0][0]=0,grid[0][1]=1,grid[1][1]=1,grid[1][0]=1;
	t[0][0]=0,t[0][1]=1;
}

vector<vector<int>> mul(vector<vector<int>> &a,vector<vector<int>> &b){
	vector<vector<int>> ans(a.size(),vector<int>(b[0].size(),0));
	for(int i=0;i<a.size();++i){
		for(int j=0;j<b[0].size();++j){
			for(int k=0;k<a[0].size();++k){
				ans[i][j]=(ans[i][j]+a[i][k]*b[k][j]%mod)%mod;
			}
		}
	}
	return ans;
}

int main()
{
	int n;
	while(cin>>n,n!=-1){
		init();
		while(n){
			if(n&1) t=mul(t,grid);
			grid=mul(grid,grid);
			n>>=1;
		}
		cout<<t[0][0]<<endl;
	}	
	return 0;
}