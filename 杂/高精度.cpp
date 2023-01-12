#include <bits/stdc++.h>

using i64 = long long;

std::string operator^(std::string a, std::string b) {
	std::string c;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int p = 0;
	for (int i = 0; i < int(a.size()) || i < int(b.size()); i++) {
		if (i < int(a.size())) p += a[i] - '0';
		if (i < int(b.size())) p += b[i] - '0';
		c += p % 10 + '0', p /= 10;
	}
	if (p) c += p + '0';
	reverse(c.begin(), c.end());
	return c;
}
bool relat(std::string &a, std::string &b) {
	if (a.size() != b.size()) return a.size() > b.size();
	for (int i = 0; i < int(a.size()); i++) {
		if (a[i] != b[i]) return a[i] > b[i];
	}
	return true;
}
std::string operator-(std::string a, std::string b) {
	std::string c;
	bool ok = true;
	if (!relat(a, b)) std::swap(a, b), ok = false, c += '-';
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int p = 0;
	for (int i = 0; i < int(a.size()); i++) {
		p = a[i] - '0' - p;
		if (i < int(b.size())) p -= b[i] - '0';
		c += ((p + 10) % 10) + '0';
		if (p < 0) p = 1;
		else p = 0;
	}
	while (c.size() > 1 && c.back() == '0') c.pop_back();
	if (ok) reverse(c.begin(), c.end());
	else reverse(c.begin() + 1, c.end());
	return c;
}
std::string operator*(std::string a, i64 b) {
	std::string c;
	reverse(a.begin(), a.end());
	i64 p = 0;
	for (int i = 0; i < int(a.size()) || p; i++) {
		if (i < int(a.size())) p += (a[i] - '0') * b;
		c += p % 10 + '0', p /= 10;
	}
	while (c.size() > 1 && c.back() == '0') c.pop_back();
	reverse(c.begin(), c.end());
	return c;
}
std::string operator/(std::string a, i64 b) {
	std::string c;
	i64 r = 0;
	for (int i = 0; i < int(a.size()); i++) {
		r = r * 10 + a[i] - '0';
		c += r / b + '0', r %= b;
	}
	reverse(c.begin(), c.end());
	while (c.size() > 1 && c.back() == '0') c.pop_back();
	reverse(c.begin(), c.end());
	return c;
}

std::string operator%(std::string a, i64 b) {
	std::string c;
	i64 r = 0;
	for (int i = 0; i < int(a.size()); i++) {
		r = r * 10 + a[i] - '0';
		c += r / b + '0', r %= b;
	}
	reverse(c.begin(), c.end());
	while (c.size() > 1 && c.back() == '0') c.pop_back();
	reverse(c.begin(), c.end());
	return std::to_string(r);
}