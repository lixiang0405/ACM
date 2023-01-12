/*
给一个字符串，然后问他是否将字符串的第i个字符修改为#，
新字符串的句号数量。（注意不会真正执行修改）
整数 T 是字符串 s 的一个句点当且仅当 1≤T<|s|
并且 s[i]=s[i−T] 对于每个 i∈(T,|s|]。
*/

/*
题意:给定一个只包含小写字母的字符串,每次询问将某个
位置修改为 #,问周期数量(修改独立)。
因为串长-周期长度= border 长度,所以周期数量等价于求
border 数量,又因为修改的字符是之前完全没出现过的,所
以修改完之后的 border 只能原串的border。
先使用 kmp/hash 求出原串的 border,然后预处理/每次询
问二分有多少个 border 不包含某个位置即可(注意到这等
价于有多少个 border 小于等于某个长度)
*/

int nxt[N],pre[N];

void get_next(const string& s) {
	int j = -1;
	nxt[0] = j;
	for(int i = 1; i < s.size(); i++) { // 注意i从1开始
		while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
			j = nxt[j]; // 向前回退
		}
		if (s[i] == s[j + 1]) { // 找到相同的前后缀
			j++;
		}
		nxt[i] = j; // 将j（前缀的长度）赋给next[i]
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	string s;
	cin>>s;
	get_next(s);
	n=SZ(s);
	int p=n-1,len;
	while(1){
		len=nxt[p]+1;
		if(!len) break;
		pre[len]=1;
		p=nxt[p];
	}
	rep(i,1,1+n) pre[i]+=pre[i-1];	
	int m;
	cin>>m;
	while(m--){
		int x;
		cin>>x;
		x=min(x-1,n-x);
		cout<<pre[x]<<'\n';
	}
	return 0;
}