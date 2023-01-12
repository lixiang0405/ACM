/*
https://atcoder.jp/contests/arc151/tasks/arc151_c
有 N 个正方形，称为正方形1、正方形2、…、正方形N，其中正方形i和正方形i+1相邻,
每个 i=1,2,...,N-1。
最初，方格中的 M 个位置上写有 0 或 1。
具体来说，对于每个i=1,2,…,M, Yi写在正方形Xi上.
其他N-M个方格上没有任何文字。
高桥和青木将进行一场比赛。两人将交替行动，高桥先行。
选择一个还没有写任何东西的方格，然后在那个方格上写上 0 或 1。
在这里，禁止让两个相邻的方格上写相同的数字。
第一个无法行动的玩家输掉；另一个玩家获胜。
当双方都为自己的胜利采取最优策略时，确定获胜者。
*/

ll x[N],y[N];
int sg[100][2],sg2[100],sg3[100];
//sg:sg[i][0] 取i个数左右两边相同 sg[i][1] 取i个数左右两边不同
//sg2:sg[i] 取i个数左右只有一边有数字
//sg3:sg[i] 取i个数左右都没有数字

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=10;
    sg[1][0]=1,sg[1][1]=0;
    rep(i,2,1+n){
        set<int> st;
        rep(j,1,i)//两边不同
            st.insert(sg[j][0]^sg[i-j-1][1]);
        while(st.count(sg[i][1])) sg[i][1]++;
        st.clear();
        rep(j,1,i-1)//两边相同
            st.insert(sg[j][0]^sg[i-j-1][0]);
        rep(j,0,i)
            st.insert(sg[j][1]^sg[i-j-1][1]);
        while(st.count(sg[i][0])) sg[i][0]++;
        //cout<<i<<" "<<sg[i][0]<<" "<<sg[i][1]<<'\n';
    }
    rep(i,1,1+n){
        set<int> st;
        rep(j,0,i-1) st.insert(sg2[j]^sg[i-j-1][1]);
        rep(j,0,i) st.insert(sg2[j]^sg[i-j-1][0]);
        while(st.count(sg2[i])) sg2[i]++;
        st.clear();
        rep(j,0,i) st.insert(sg2[j]^sg2[i-j-1]);
        while(st.count(sg3[i])) sg3[i]++;
        //cout<<i<<" "<<sg2[i]<<" "<<sg3[i]<<'\n';
    }
    ll f,m;
    cin>>f>>m;
    if(!m){
        cout<<((f%2)?"Takahashi":"Aoki")<<'\n';
    }else{
        int ans=0;
        rep(i,1,1+m){
            cin>>x[i]>>y[i];
            if(i!=1){
                ans^=y[i]^y[i-1]^1;
            }
        }
        ans^=x[1]-1;
        ans^=f-x[m];
        cout<<(ans?"Takahashi":"Aoki")<<'\n';
    }
	return 0;
}