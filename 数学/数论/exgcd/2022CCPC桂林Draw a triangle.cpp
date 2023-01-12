/*
Little Desprado2 是 Springfield Flowers 幼儿园的学生。
这一天，他刚刚学会了在网格坐标纸上画三角形。
不过很快他就觉得很枯燥，于是想出了一个更有趣的问题：
他在方格纸上画了三角形的两个整数点，分别表示它们（x1，y1）（x1，y1）和（x2，y2）（x2，y2）。
现在，他想知道以下问题的答案：他在哪里可以画出第三个整数点 (x3,y3)(x3,y3) 以使三角形的面积为正但最小化？
显然，他解决不了这个问题，因为他太年轻太单纯了。你能告诉他答案吗？
请注意，您的答案的坐标必须由整数组成，因为他是在网格纸上绘制的，
并且三角形不应该是退化三角形以保持面积为正。
*/

/*
题解 假设三个点分别为 𝐴, 𝐵, 𝐶，其中 𝐴 和 𝐵 坐标已知。则面积可以用叉积表示：
𝑆 =1/2|𝐴𝐵 × 𝐴𝐶|。设已知的 𝐴𝐵 = (𝑥, 𝑦), 未知的 𝐴𝐶 = (𝑢, 𝑣)，
则 𝑆 =1/2|𝑥𝑣 −𝑦𝑢|。不难发现绝对值符号内是一个经典的 exgcd 的式子，
其能取得的最小值为 gcd(𝑥, 𝑦)。
直接套用 exgcd 求出 𝑥𝑣 −𝑦𝑢 = gcd(𝑥, 𝑦) 的任意一组解即可。
注意对符号和 0 的情况稍作讨论。
*/

int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
} 
//S=1/2*|x*v-y*u|
pii get(int x,int y,int v,int u){
	int d=exgcd(x,y,v,u);
	u=-u;
    return {u,v};
}

int t;

void solve(){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    int y=d-b,x=c-a;
    pii ans=get(x,y,0,0);
    cout<<ans.fi+a<<" "<<ans.se+b<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>t;
    while(t--){
        solve();
    }
	return 0;
}