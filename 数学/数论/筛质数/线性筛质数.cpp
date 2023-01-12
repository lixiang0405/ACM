int cnt = 0;
int pr[N + 5];
bool f[N + 5];

void getp(int x) {
	//线性筛质数
	for (int i = 2; i <= x ; ++i) {
		if (!f[i]) pr[cnt++] = i;
		for (int j = 0; j < cnt && pr[j] * i <= x; ++j) {
			f[i * pr[j]] = true;
			if (i % pr[j] == 0)
				break;
		}
	}
}