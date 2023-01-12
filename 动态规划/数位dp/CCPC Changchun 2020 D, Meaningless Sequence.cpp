/*从前有一位数学家，他痴迷于无意义的数列。这是其中之一。
当n=0时，an=1，否则，an=c⋅(最大值0≤i<n a(n&i))。
作为一名数学家，他可以很容易地判断出an代表任何n，但他想测试你。你必须告诉他
(∑i=（0-n）ai）mod（109+7）
让他相信你对这个（尽管毫无意义）序列有深刻的理解。*/


int c;
ll ans=0,pw[3005];
char s[3005];

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%s%d",s,&c);
	int n=strlen(s);
	pw[0]=1;
	/*多一位
	0
	10 11
	100 101 110 111
	1100 1110 1000 1010 1101 1111 1001 1011
	多一个0贡献是pw[i-1]，多一个1贡献是c*pw[i-1]
	所以pw[i]总贡献是(1+c)pw[i-1]
	*/
	for(int i=1;i<=n;++i)
	pw[i]=(pw[i-1]*(c+1))%mod;
	ll pre=1;
	for(int i=0;i<n;++i){
		if(s[i]=='1'){
			ans=(ans+pre*pw[n-i-1])%mod;//pw[n-i-1] (....0)00000-(.....0)11111 （固定）因为前面全取1，每个1对pw[n-i-1]的贡献是C  
			pre=(pre*c)%mod;
		}
	}
	//加上本身
	ans=(ans+pre)%mod;
	printf("%lld",ans);
	return 0;
}