//O(n^(1/4)logn)
namespace prime_fac {
    const int S = 8; // 随机算法判定次数，8~10 就够了

    // 龟速乘
    long long mult_mod(long long a, long long b, long long c) {
        a %= c, b %= c;
        long long ret = 0;
        long long tmp = a;
        while (b) {
            if (b & 1) {
                ret += tmp;
                if (ret > c) ret -= c;
            }
            tmp <<= 1;
            if (tmp > c) tmp -= c;
            b >>= 1;
        }
        return ret;
    }

    // 快速幂
    long long qow_mod(long long a, long long n, long long _mod) {
        long long ret = 1;
        long long temp = a % _mod;
        while (n) {
            if (n & 1) ret = mult_mod(ret, temp, _mod);
            temp = mult_mod(temp, temp, _mod);
            n >>= 1;
        }
        return ret;
    }

    // 是合数返回true，不一定是合数返回false
    bool check(long long a, long long n, long long x, long long t) {
        long long ret = qow_mod(a, x, n);
        long long last = ret;
        for (int i = 1; i <= t; i++) {
            ret = mult_mod(ret, ret, n);
            if (ret == 1 && last != 1 && last != n - 1) return true;
            last = ret;
        }
        if (ret != 1) return true;
        return false;
    }

    // 是素数返回true，不是返回false
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    bool Miller_Rabin(long long n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if ((n & 1) == 0) return false;
        long long x = n - 1;
        long long t = 0;
        while ((x & 1) == 0) { x >>= 1; t++; }

        for (int i = 0; i < S; i++) {
            long long a = rng() % (n - 1) + 1;
            if (check(a, n, x, t))
                return false;
        }

        return true;
    }

    long long factor[100];// 存质因数
    int tol; // 质因数的个数，0~tol-1

    long long gcd(long long a, long long b) {
        long long t;
        while (b) {
            t = a;
            a = b;
            b = t % b;
        }
        if (a >= 0) return a;
        return -a;
    }

    long long pollard_rho(long long x, long long c) {
        long long i = 1, k = 2;
        long long x0 = rng() % (x - 1) + 1;
        long long y = x0;
        while (1) {
            i++;
            x0 = (mult_mod(x0, x0, x) + c) % x;
            long long d = gcd(y - x0, x);
            if (d != 1 && d != x) return d;
            if (y == x0) return x;
            if (i == k) { y = x0; k += k; }
        }
    }
    // 对n质因数分解，存入factor，k一般设置为107左右
    void findfac(long long n, int k) {
        if (n == 1) return;
        if (Miller_Rabin(n)) {
            factor[tol++] = n;
            return;
        }
        long long p = n;
        int c = k;
        while (p >= n) p = pollard_rho(p, c--);
        findfac(p, k);
        findfac(n / p, k);
    }
    vector<ll> fac(long long n) {
        tol = 0;
        vector<ll> ret;
        findfac(n, 107);
        for (int i = 0; i < tol; i++) ret.push_back(factor[i]);
        return ret;
    }
}