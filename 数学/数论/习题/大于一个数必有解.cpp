/*
给定a，b，输出使得ax+by=k没有非负整数解的最大k，其中a，b互质
*/

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll a,b;
	cin>>a>>b;
	cout<<a*b-a-b<<endl;
	return 0;
} 